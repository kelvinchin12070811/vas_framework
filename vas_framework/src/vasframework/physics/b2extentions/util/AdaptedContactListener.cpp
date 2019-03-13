#include "AdaptedContactListener.hpp"

#ifdef VAS_HAS_B2D
#include <array>
#include "../../CollideAble.hpp"

void vas::physics::b2extentions::AdaptedContactListener::BeginContact(b2Contact * contact)
{
	if (customListener) customListener->BeginContact(contact);
	std::array<std::any*, 2> obj = {
		reinterpret_cast<std::any*>(contact->GetFixtureA()->GetBody()->GetUserData()),
		reinterpret_cast<std::any*>(contact->GetFixtureB()->GetBody()->GetUserData())
	};

	for (auto itr : obj)
	{
		if (itr->type() == typeid(CollideAble*) && itr->has_value())
		{
			(*std::any_cast<CollideAble*>(itr))->beginContact(contact);
		}
	}
}

void vas::physics::b2extentions::AdaptedContactListener::EndContact(b2Contact * contact)
{
	if (customListener) customListener->EndContact(contact);
	std::array<std::any*, 2> obj = {
		reinterpret_cast<std::any*>(contact->GetFixtureA()->GetBody()->GetUserData()),
		reinterpret_cast<std::any*>(contact->GetFixtureB()->GetBody()->GetUserData())
	};

	for (auto itr : obj)
	{
		if (itr->type() == typeid(CollideAble*) && itr->has_value())
		{
			(*std::any_cast<CollideAble*>(itr))->endContact(contact);
		}
	}
}

void vas::physics::b2extentions::AdaptedContactListener::PreSolve(b2Contact * contact, const b2Manifold * oldManifold)
{
	if (customListener) customListener->PreSolve(contact, oldManifold);
	std::array<std::any*, 2> obj = {
		reinterpret_cast<std::any*>(contact->GetFixtureA()->GetBody()->GetUserData()),
		reinterpret_cast<std::any*>(contact->GetFixtureB()->GetBody()->GetUserData())
	};

	for (auto itr : obj)
	{
		if (itr->type() == typeid(CollideAble*) && itr->has_value())
		{
			(*std::any_cast<CollideAble*>(itr))->preSolve(contact, oldManifold);
		}
	}
}

void vas::physics::b2extentions::AdaptedContactListener::PostSolve(b2Contact * contact, const b2ContactImpulse * impulse)
{
	if (customListener) customListener->PostSolve(contact, impulse);
	std::array<std::any*, 2> obj = {
		reinterpret_cast<std::any*>(contact->GetFixtureA()->GetBody()->GetUserData()),
		reinterpret_cast<std::any*>(contact->GetFixtureB()->GetBody()->GetUserData())
	};

	for (auto itr : obj)
	{
		if (itr->type() == typeid(CollideAble*) && itr->has_value())
		{
			(*std::any_cast<CollideAble*>(itr))->postSolve(contact, impulse);
		}
	}
}
#endif // VAS_HAS_B2D