//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "b2WorldEx.hpp"

#ifdef VAS_HAS_B2D
#include "b2Pointer.hpp"
#include "util/AdaptedContactListener.hpp"
#include "util/AdaptedDestructionListener.hpp"

namespace vas::physics::b2extentions
{
	b2WorldEx::b2WorldEx(const b2Vec2 & gravity):
		b2World(gravity)
	{
		adaptContactor = std::make_unique<AdaptedContactListener>();
		adaptContactor->world = this;
		b2World::SetContactListener(adaptContactor.get());

		adaptDestructor = std::make_unique<AdaptedDestructionListener>();
		adaptDestructor->world = this;
		b2World::SetDestructionListener(adaptDestructor.get());
	}

	b2WorldEx::~b2WorldEx()
	{
		WorldDestructed();
	}

	b2Pointer<b2Body> b2WorldEx::CreateBody(const b2BodyDef * def)
	{
		auto ptr = MakePointer(b2World::CreateBody(def));
		auto data = userDataEx.insert({ ptr.getObject(), std::any{} });
		ptr->SetUserData(&data.first->second);
		return ptr;
	}

	void b2WorldEx::DestroyBody(b2Pointer<b2Body>& body)
	{
		objects.erase(reinterpret_cast<void*>(body.object));
		userDataEx.erase(body.object);
		b2World::DestroyBody(body.object);
	}

	b2Pointer<b2Joint> b2WorldEx::CreateJoint(const b2JointDef * def)
	{
		return MakePointer<b2Joint>(b2World::CreateJoint(def));
	}

	void b2WorldEx::DestroyJoint(b2Pointer<b2Joint>& joint)
	{
		objects.erase(joint.object);
		b2World::DestroyJoint(joint.object);
	}

	void b2WorldEx::SetDestructionListener(b2DestructionListener * listener)
	{
		adaptDestructor->customListener = listener;
	}

	void b2WorldEx::SetContactListener(b2ContactListener * listener)
	{
		adaptContactor->customListener = listener;
	}

	bool b2WorldEx::IsObjectAlive(void * object) const
	{
		return objects.find(object) != objects.end();
	}
	
	void b2WorldEx::MarkObjectDeath(void * object)
	{
		objects.erase(object);
	}
}
#endif // VAS_HAS_B2D
