#include "RenderAbleBase.hpp"

namespace vas
{
	RenderAbleBase::RenderAbleBase()
	{
	}


	RenderAbleBase::~RenderAbleBase()
	{
	}

	void RenderAbleBase::setStaticOnCamera(bool value)
	{
		staticOnCamera = value;
	}

	bool RenderAbleBase::isStaticOnCamera()
	{
		return staticOnCamera;
	}

	void RenderAbleBase::setCenter(SDL_Point point)
	{
		center = point;
	}

	void RenderAbleBase::setFlip(SDL_RendererFlip flip)
	{
		this->flip = flip;
	}

	void RenderAbleBase::setRotation(const Angle & rotation)
	{
		this->rotation = rotation;
	}

	void RenderAbleBase::rotate(const Angle & rotation)
	{
		this->rotation += rotation;
	}

	SDL_Point RenderAbleBase::getPoint()
	{
		return center;
	}

	SDL_RendererFlip RenderAbleBase::getFlip()
	{
		return flip;
	}

	const Angle & RenderAbleBase::getRotation()
	{
		return rotation;
	}

	int RenderAbleBase::getWidth()
	{
		return destination.w;
	}

	int RenderAbleBase::getHeight()
	{
		return destination.h;
	}
}