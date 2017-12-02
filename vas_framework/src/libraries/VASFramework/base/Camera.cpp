#include "Camera.hpp"
#include "Base.hpp"

namespace vas
{
	Camera & Camera::getInstance()
	{
		static Camera instance;
		return instance;
	}

	void Camera::targetOn(const Vector2 & position)
	{
		this->position = position;
	}

	void Camera::setPosition(const Vector2 & position)
	{
		this->position = position;
	}

	void Camera::move(const Vector2 & position)
	{
		this->position += position;
	}

	void Camera::zoom(float scale)
	{
		SDL_Point currentSize = Base::getInstance().getRenderLogicSize();
		currentSize.x = static_cast<int>(currentSize.x * scale);
		currentSize.y = static_cast<int>(currentSize.y * scale);
		if (static_cast<float>(currentSize.x) / static_cast<float>(currentSize.y) != static_cast<float>(constantWindowSize.x) / static_cast<float>(constantWindowSize.y))
			return;

		cameraRect.w = currentSize.x;
		cameraRect.h = currentSize.y;
		Base::getInstance().setRenderLogicSize(currentSize);
	}

	void Camera::resetZoom()
	{
		cameraRect.w = constantWindowSize.x;
		cameraRect.h = constantWindowSize.y;
		Base::getInstance().setRenderLogicSize(constantWindowSize);
	}

	const Vector2 & Camera::getPosition()
	{
		return position;
	}

	int Camera::getXOffset()
	{
		return static_cast<int>(position.x) - Base::getInstance().getRenderLogicSize().x / 2;
	}

	int Camera::getYOffset()
	{
		return static_cast<int>(position.y) - Base::getInstance().getRenderLogicSize().y / 2;
	}

	bool Camera::canSee(const SDL_Rect & destination)
	{
		//SDL_Rect cameraRect = {0 , 0, Base::getInstance().getRenderLogicSize().x, Base::getInstance().getRenderLogicSize().y };
		return SDL_HasIntersection(&destination, &cameraRect) == SDL_TRUE ? true : false;
	}

	Camera::Camera() :
		position(Vector2(Base::getInstance().getRenderLogicSize().x / 2.0f, Base::getInstance().getRenderLogicSize().y / 2.0f)),
		constantWindowSize(BaseAPI().getRenderLogicSize()),
		cameraRect(SDLFunctionBridge::newSDLRect(0, 0, constantWindowSize.x, constantWindowSize.y))
	{
	}

	Camera::~Camera()
	{
	}
}