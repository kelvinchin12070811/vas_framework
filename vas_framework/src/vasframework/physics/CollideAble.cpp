#include "CollideAble.hpp"

#ifdef VAS_HAS_B2D
namespace vas::physics
{
	CollideAble::CollideAble(b2extentions::b2WorldEx & world, const b2BodyDef * bodyDef, const b2FixtureDef * fixtureDef)
	{
		body = world.CreateBody(bodyDef);
		body->CreateFixture(fixtureDef);
	}

	CollideAble::CollideAble(b2extentions::b2WorldEx & world, const b2BodyDef * bodyDef, const b2Shape * shape, float density)
	{
		body = world.CreateBody(bodyDef);
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
}
#endif // VAS_HAS_B2D