//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include "../../VASConfig.hpp"

#ifdef VAS_HAS_B2D
#include "b2WorldEx.hpp"

namespace vas::physics::b2extentions
{
	/**
	 * @ingroup physics
	 * @{
	 */
	/**
	 * @brief Smart pointer that try to track Box2D objects.
	 * The b2Pointer is a smart pointer that designed to track object created by b2WorldEx.
	 */
	template <typename B2Object>
	class b2Pointer
	{ /** @} */
	public:
		b2Pointer() = default;

		/** Get raw Box2D object. */
		const B2Object* getObject() const
		{
			return object;
		}

		/** Get raw Box2D object. */
		B2Object* getObject()
		{
			return const_cast<B2Object*>(const_cast<const b2Pointer*>(this)->getObject());
		}

		/** Get b2WorldEx instance that relied on. */
		const b2WorldEx* getWorld() const
		{
			return world;
		}

		/** Get b2WorldEx instance that relied on. */
		b2WorldEx* getWorld()
		{
			return const_cast<b2World*>(const_cast<const b2Pointer*>(this)->getWorld());
		}

		/** Check if Box2D object is still valid. */
		bool expired() const
		{
			if (world == nullptr) return true;
			auto& objects = world->GetObjects();
			return objects.find(reinterpret_cast<void*>(object)) == objects.end();
		}

		/**
		 * @name Overloaded operators
		 * @{
		 */
		/** Access Box2D object via '->'. */
		const B2Object* operator->() const
		{
			if (world == nullptr) throw std::runtime_error("World object destroyed");
			return object;
		}
		/** Access Box2D object via '->'. */
		B2Object* operator->()
		{
			return const_cast<B2Object*>(const_cast<const b2Pointer*>(this)->operator->());
		}
		/** Check if Box2D object is still valid. */
		operator bool() const
		{
			return !expired();
		}
		/** Compare two smart pointer if equal. */
		bool operator==(const b2Pointer& rhs) const
		{
			return object == rhs.object && world == rhs.world;
		}
		/** Check if pointer is pointing to nullptr object (object invalidated, world destructed, etc). */
		bool operator==(std::nullptr_t) const
		{
			return expired();
		}
		/** Compare two smart pointer if not equal. */
		bool operator!=(const b2Pointer& rhs) const
		{
			return !operator==(rhs);
		}
		/** Check if pointer is not pointing to nullptr object. */
		bool operator!=(nullptr_t) const
		{
			return !operator==(nullptr);
		}
		/** Make pointer point to nullptr object. */
		b2Pointer& operator=(nullptr_t)
		{
			object = nullptr;
			world = nullptr;
			return *this;
		}
		/** @} */

		/** Slot, called when world relied is destructed. */
		void onWorldDestructed()
		{
			world = nullptr;
		}
	private:
		B2Object* object{ nullptr };
		b2WorldEx* world{ nullptr };
		boost::signals2::scoped_connection connection;
	private:
		friend b2WorldEx;
	};
}
#endif // VAS_HAS_B2D