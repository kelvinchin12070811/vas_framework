#include "../sdlcore/SDLCore.hpp"
#include "../base/Base.hpp"
#include "Camera.hpp"

namespace vas
{
	Camera & Camera::getInstance()
	{
		static Camera instance;
		return instance;
	}

	bool Camera::canSee(const sdl::Rect & other)
	{
		sdl::Rect cameraRect = { static_cast<int>(position.x), static_cast<int>(position.y), size.x, size.y };

		if (other.x + other.w < cameraRect.x && other.x > cameraRect.x + cameraRect.w &&
			other.y + other.h < cameraRect.y && other.y > cameraRect.y + cameraRect.h)
		{
			return false;
		}
		return true;
	}

	bool Camera::canSee(const Vector2 & other, const sdl::Point & size)
	{
		sdl::Rect otherHolder(static_cast<int>(other.x), static_cast<int>(other.y), size.x, size.y);
		return canSee(otherHolder);
	}

	Vector2 Camera::getPosOnCamera(const Vector2 & position, bool staticOnCamera)
	{
		if (staticOnCamera) return position;
		return position - this->position;
	}

	sdl::Rect Camera::getRectOnCamera(const sdl::Rect & rect, bool staticOnCamera)
	{
		if (staticOnCamera) return rect;
		Vector2 position = getPosOnCamera(Vector2(static_cast<float>(rect.x), static_cast<float>(rect.y)));
		return sdl::Rect(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(rect.w * multiplyer), static_cast<int>(rect.h * multiplyer));
	}

	void Camera::move(const Vector2 & movement)
	{
		if (movement == zerovector) return;
		position += movement;
	}

	void Camera::focusOn(const Vector2 & position)
	{
		this->position = position - Vector2(size.x / 2, size.y / 2);
	}

	void Camera::zoom(double value)
	{
		this->multiplyer *= value;
	}

	void Camera::setPosition(const Vector2 & value)
	{
		if (position != value)
			position = value;
	}

	void Camera::setSize(const sdl::Point & value)
	{
		if (size != value)
			size = value;
	}

	void Camera::setMultiplyer(double value)
	{
		multiplyer = value;
	}

	Vector2 Camera::getPosition()
	{
		return position;
	}

	sdl::Point Camera::getSize()
	{
		return size;
	}

	double Camera::getMultiplyer()
	{
		return multiplyer;
	}

	Camera::Camera()
	{
	}

	Camera::~Camera()
	{
	}
}