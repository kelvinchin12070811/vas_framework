//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include "../../VASConfig.hpp"

#ifdef VAS_HAS_B2D
#include <any>
#include <boost/signals2.hpp>
#include <Box2D/Box2D.h>
#include <unordered_map>
#include <unordered_set>

namespace vas::physics::b2extentions
{
	template <typename B2Object> class b2Pointer;
	class AdaptedDestructionListener;
	class AdaptedContactListener;

	/**
	 * @ingroup physics
	 * @{
	 */
	/**
	 * @brief The physic world that simulate all the entire entities.
	 * 
	 * b2WorldEx is an extention to Box2D's b2World and provide more function such as smart pointer support. The
	 * b2WorldEx also keep tracking all Box2D objects and notifiy if they are been destroyed.
	 * 
	 * The b2WorldEx instance wrap all Box2D objects in smart pointer therefore it can be tracked easily.
	 */
	class VAS_DECLSPEC b2WorldEx : public b2World
	{ /** @} */
	public:
		b2WorldEx(const b2Vec2& gravity); /**< Create world with gravity. */
		~b2WorldEx();

		b2WorldEx(const b2WorldEx&) = default;
		b2WorldEx(b2WorldEx&&) = default;
		b2WorldEx& operator=(const b2WorldEx&) = default;
		b2WorldEx& operator=(b2WorldEx&&) = default;

		b2Pointer<b2Body> CreateBody(const b2BodyDef* def); /**< Create new b2Body.
														* @note All b2Body created by b2WorldEx has an empty std::any as it's user data.
														* Cast to  std::any when calling GetUserData function.
														*
														* @warning Do not set custom user data via SetUserData function. It will override
														* default std::any data type. */
		void DestroyBody(b2Pointer<b2Body>& body); /**< Destroy a b2Body. */

		b2Pointer<b2Joint> CreateJoint(const b2JointDef* def); /**< Create new b2Joint. */
		void DestroyJoint(b2Pointer<b2Joint>& joint); /**< Destroy a b2Joint. */

		void SetDestructionListener(b2DestructionListener* listener); /**< Set custom destruction listener. */
		void SetContactListener(b2ContactListener* listener); /**< Set custom contact listener. */

		bool IsObjectAlive(void* object) const; /**< Check if a Box2D object is still alive. */
		void MarkObjectDeath(void* object); /**< Mark a Box2D object as death, this function will be called automatically
											if an object death. */

		/**
		 * Make a smart pointer of Box2D object.
		 * @tparam B2Object Box2D object that relied on a b2World (b2Body, b2Joint, etc.)
		 * @param[in] object Instance of Box2D object.
		 */
		template <typename B2Object>
		b2Pointer<B2Object> MakePointer(B2Object* object)
		{
			objects.insert(reinterpret_cast<void*>(object));
			b2Pointer<B2Object> instance;
			instance.object = object;
			instance.world = this;
			instance.connection = WorldDestructed.connect([&]() { instance.onWorldDestructed(); });
			return instance;
		}
	private:
		std::unordered_set<void*> objects;
		std::unordered_map<b2Body*, std::any> userDataEx;
		std::unique_ptr<AdaptedContactListener> adaptContactor;
		std::unique_ptr<AdaptedDestructionListener> adaptDestructor;
		boost::signals2::signal<void()> WorldDestructed;
	};
}
#endif // VAS_HAS_B2D
