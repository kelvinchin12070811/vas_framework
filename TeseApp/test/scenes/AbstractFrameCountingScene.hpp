#pragma once
#include <vasframework/graphics/scene/AbstractScene.hpp>

namespace scene
{
	class AbstractFrameCountingScene : public vas::AbstractScene
	{
	public:
		AbstractFrameCountingScene();
		~AbstractFrameCountingScene();

		void tick() = 0;
		void draw() = 0;
	};
}