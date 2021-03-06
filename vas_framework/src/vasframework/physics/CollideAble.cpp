//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "CollideAble.hpp"

#ifdef VAS_HAS_B2D
namespace vas::physics
{
	CollideAble::CollideAble(b2extentions::b2WorldEx & world, const b2BodyDef * bodyDef, const b2FixtureDef * fixtureDef):
		world(&world), body(this->world->CreateBody(bodyDef))
	{
		body->CreateFixture(fixtureDef);
	}

	CollideAble::CollideAble(b2extentions::b2WorldEx & world, const b2BodyDef * bodyDef, const b2Shape * shape, float density):
		world(&world), body(this->world->CreateBody(bodyDef))
	{
		body->CreateFixture(shape, density);
	}

	void CollideAble::beginContact(b2Contact * contact)
	{
		static_cast<void>(contact);
	}
	
	void CollideAble::endContact(b2Contact * contact)
	{
		static_cast<void>(contact);
	}
	
	void CollideAble::preSolve(b2Contact * contact, const b2Manifold * oldManifold)
	{
		static_cast<void>(contact);
		static_cast<void>(oldManifold);
	}
	
	void CollideAble::postSolve(b2Contact * contact, const b2ContactImpulse * impulse)
	{
		static_cast<void>(contact);
		static_cast<void>(impulse);
	}
	
	const b2extentions::b2Pointer<b2Body> & CollideAble::getBody() const
	{
		return body;
	}
	
	b2extentions::b2WorldEx * CollideAble::getWorld()
	{
		return world;
	}
}
#endif // VAS_HAS_B2D