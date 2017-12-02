#pragma once
#include <SDL.h>
#include "../irender_able/iRenderAble.hpp"
#include "../../base/Camera.hpp"
#include "../../math/Angle.hpp"

namespace vas
{
	class RenderAbleBase : public iRenderAble
	{
	public:
		RenderAbleBase();
		virtual ~RenderAbleBase();
		void setStaticOnCamera(bool value);
		bool isStaticOnCamera();

		void setCenter(SDL_Point point);
		void setFlip(SDL_RendererFlip flip);
		void setRotation(const Angle& rotation);
		void rotate(const Angle& rotation);

		SDL_Point getPoint();
		SDL_RendererFlip getFlip();
		const Angle& getRotation();
		int getWidth();
		int getHeight();
	protected:
		bool staticOnCamera = false;
		Angle rotation;
		SDL_Rect source = { 0 }, destination = { 0 };
		SDL_Point center = { 0 };

		SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;
	};
}