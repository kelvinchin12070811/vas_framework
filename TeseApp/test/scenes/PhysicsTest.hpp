#pragma once
#include "AbstractFrameCountingScene.hpp"
#include <vasframework/physics/b2extentions/b2Extention.hpp>
#include <memory>
#include <vector>

using namespace vas::physics::b2extentions;

namespace scene
{
	class PhysicsTest : public AbstractFrameCountingScene
	{
	public:
		PhysicsTest();
		void tick() override;
		void draw() override;
	private:
		std::unique_ptr<b2WorldEx> world;
		std::vector<b2Pointer<b2Body>> bodies;
		b2Pointer<b2Body> ground;

		static const vas::sreflex::ReflectAbleAutoRegistrar<PhysicsTest> __registra;
	};
}