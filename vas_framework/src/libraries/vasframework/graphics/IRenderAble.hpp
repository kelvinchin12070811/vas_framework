#pragma once
#include "Camera.hpp"
#include "../sdlcore/video/Renderer.hpp"

namespace vas
{
	class IRenderAble
	{
	public:
		virtual ~IRenderAble() {}

		virtual void tick() = 0;
		virtual void draw(sdl::Renderer* renderer = nullptr, Camera* camera = nullptr) = 0;
	};
}