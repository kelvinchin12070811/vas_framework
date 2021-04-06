#include "PhysicsTest.hpp"
#include <vasframework/base/Base.hpp>
#include <vasframework/physics/PhysicsUtil.hpp>

using namespace vas::physics;

namespace scene
{
	const vas::sreflex::ReflectAbleAutoRegistrar<PhysicsTest> PhysicsTest::__registra{};

	PhysicsTest::PhysicsTest()
	{
		world = std::make_unique<b2WorldEx>(b2Vec2(0, -10.0f));
		b2BodyDef bodyDef;
		bodyDef.position = CoordinateTools::pxToReal(vas::Vector2{ 320.0f, 470.0f });
		bodyDef.type = b2BodyType::b2_staticBody;
		ground = world->CreateBody(&bodyDef);
		std::any* test = reinterpret_cast<std::any*>(ground->GetUserData().pointer);
		vas::Cout() << "test has value?: " << std::boolalpha << test->has_value() << std::endl;
		vas::Cout() << "test type: " << test->type().name() << std::endl;
		
		b2PolygonShape polygon;
		polygon.SetAsBox(CoordinateTools::pxToReal(320.0f), CoordinateTools::pxToReal(16.0f));
		ground->CreateFixture(&polygon, 1.0f);

		bodyDef.type = b2BodyType::b2_dynamicBody;
		polygon.SetAsBox(0.5f, 0.5f);
		for (int x{ 1 }; x <= 11; x++)
		{
			bodyDef.position.Set(x * 1.5f, -CoordinateTools::pxToReal(10.0f));
			auto body = world->CreateBody(&bodyDef);
			body->CreateFixture(&polygon, 1.0f);
			bodies.push_back(std::move(body));
		}

		world->DestroyBody(bodies[10]);
		bodies.pop_back();
	}

	void PhysicsTest::tick()
	{
		world->Step(1.0f / 60.0f, 8, 3);
		AbstractFrameCountingScene::tick();
	}

	void PhysicsTest::draw()
	{
		auto renderer = vas::Base::getInstance().getRenderer();
		renderer.setRenderDrawColor(0xff, 0xff, 0xff, 0xff);
		for (auto& itr : bodies)
		{
			auto pos = CoordinateTools::realToPx(itr->GetPosition());
			vas::sdl::Rect rect{ static_cast<int>(pos.x - 16), static_cast<int>(pos.y - 16), 32, 32 };
			renderer.fillRect(&rect);
		}
		vas::sdl::Rect groundRect{ static_cast<int>(ground->GetPosition().x * 32.0f - 320.0f),
			static_cast<int>(-ground->GetPosition().y * 32.0f - 16.0f),  640, 32 };
		renderer.fillRect(&groundRect);
		AbstractFrameCountingScene::draw();
		renderer.setRenderDrawColor(0, 0, 0, 0xff);
	}
}