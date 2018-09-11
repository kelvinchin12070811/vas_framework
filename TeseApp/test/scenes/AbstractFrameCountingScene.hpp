#pragma once
#include <vasframework/graphics/scene/Scene.hpp>

namespace scene
{
	class AbstractFrameCountingScene : public vas::Scene
	{
	public:
		AbstractFrameCountingScene();
		~AbstractFrameCountingScene();

		void tick() = 0;
		void draw() = 0;
	};
}