//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include "../VASConfig.hpp"

#ifdef VAS_HAS_B2D
#include <Box2D/Box2D.h>
#include "b2extentions/b2Pointer.hpp"

namespace vas::physics
{
	/**
	 * @ingroup physics
	 * @{
	 */
	/**
	 * @brief All entities or objects that collide able with each other.
	 * The CollideAble is an interface of all objects that will be collide with each other and fire event to the corresponding
	 * objects.
	 */
	class VAS_DECLSPEC CollideAble
	{ /** @} */
	public:
		/**
		 * Initialize CollideAble and create body of object.
		 * @param[in] world World relied.
		 * @param[in] bodyDef Box2D body definitions.
		 * @param[in] fixtureDef Box2D fixtrue definitions.
		 */
		CollideAble(b2extentions::b2WorldEx& world, const b2BodyDef* bodyDef, const b2FixtureDef* fixtureDef);
		/**
		 * Initialize CollideAble and create body of object.
		 * @param[in] world World relied.
		 * @param[in] bodyDef Box2D body definitions.
		 * @param[in] shape Shape of Box2D object.
		 * @param[in] density Density of Box2D object.
		 */
		CollideAble(b2extentions::b2WorldEx& world, const b2BodyDef* bodyDef, const b2Shape* shape, float density);
		/** Called when two objects start to contact. */
		virtual void beginContact(b2Contact* contact);
		/** Called when two objects end to contact. */
		virtual void endContact(b2Contact* contact);
		/** Called when physics engine start to slove collision. */
		virtual void preSolve(b2Contact* contact, const b2Manifold* oldManifold);
		/** Called when physics engine end to slove collision. */
		virtual void postSolve(b2Contact* contact, const b2ContactImpulse* impulse);
		virtual ~CollideAble() = 0;

		const b2extentions::b2Pointer<b2Body>& getBody() const;
		b2extentions::b2WorldEx* getWorld();
	protected:
		/**
		 * Word of the object relie on.
		 * ####Accessors
		 * -# b2extentions::b2WorldEx* getWorld()
		 */
		b2extentions::b2WorldEx* world;
		/**
		 * Body of the object.
		 * ####Accessors
		 * -# const b2extentions::b2Pointer<b2Body>& getBody() const
		 */
		b2extentions::b2Pointer<b2Body> body;
	};
}
#endif // VAS_HAS_B2D