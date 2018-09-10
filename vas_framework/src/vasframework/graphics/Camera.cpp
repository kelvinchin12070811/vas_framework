#include "../sdlcore/SDLCore.hpp"
#include "../base/Base.hpp"
#include "Camera.hpp"

namespace vas
{
	Camera & Camera::getInstance()
	{
		return Base::getInstance().getCamera();
	}

	bool Camera::canSee(const sdl::Rect & other)
	{
		sdl::Rect cameraRect(0, 0, size.w(), size.h());
		
		return ((other.x < cameraRect.x + cameraRect.w) && (other.x + other.w > cameraRect.x) &&
			(other.y < cameraRect.y + cameraRect.h) && (other.y + other.h > cameraRect.y));
	}

	bool Camera::canSee(const Vector2 & other, const sdl::Point & size)
	{
		auto pos = getPosOnCamera(other);
		sdl::Point otherPos = static_cast<sdl::Point>(other);
		sdl::Rect otherHolder(otherPos.x, otherPos.y, size.x, size.y);
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
		return sdl::Rect(static_cast<int>(rect.x * multiplyer), static_cast<int>(rect.y * multiplyer),
			static_cast<int>(rect.w * multiplyer), static_cast<int>(rect.h * multiplyer));
	}

	void Camera::move(const Vector2 & movement)
	{
		if (movement == zerovector) return;
		position += movement;
	}

	void Camera::focusOn(const Vector2 & position)
	{
		this->position = position - (position / 2.0f);
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