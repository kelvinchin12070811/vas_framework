#pragma once
#include <vasframework/graphics/scene/Scene.hpp>

namespace scene
{
	class EmptyScene : public vas::Scene
	{
	public:
		EmptyScene() = default;
		void tick() override {}
		void draw() override {}
	};
}