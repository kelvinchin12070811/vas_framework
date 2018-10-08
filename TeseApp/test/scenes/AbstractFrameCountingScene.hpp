#pragma once
#include <vasframework/graphics/scene/Scene.hpp>

namespace scene
{
	class AbstractFrameCountingScene : public vas::Scene
	{
	public:
		AbstractFrameCountingScene();
		~AbstractFrameCountingScene();

		void tick();
		void draw();
	};
}