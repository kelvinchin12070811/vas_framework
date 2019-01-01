//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
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
		sdl::Rect cameraRect{ 0, 0, size.w(), size.h() };
		
		return ((other.x < cameraRect.x + cameraRect.w) && (other.x + other.w > cameraRect.x) &&
			(other.y < cameraRect.y + cameraRect.h) && (other.y + other.h > cameraRect.y));
	}

	bool Camera::canSee(const Vector2 & other, const sdl::Point & size)
	{
		sdl::Rect otherHolder{ static_cast<int>(other.x), static_cast<int>(other.y), size.x, size.y };
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
		return sdl::Rect{ static_cast<int>((rect.x * multiplier) - this->position.x), static_cast<int>((rect.y * multiplier) - this->position.y),
			static_cast<int>(rect.w * multiplier), static_cast<int>(rect.h * multiplier) };
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
		this->multiplier *= value;
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

	void Camera::setMultiplier(double value)
	{
		multiplier = value;
	}

	Vector2 Camera::getPosition()
	{
		return position;
	}

	sdl::Point Camera::getSize()
	{
		return size;
	}

	double Camera::getMultiplier()
	{
		return multiplier;
	}
}