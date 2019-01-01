//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include <cmath>
#include "Vector2.hpp"
#include "Angle.hpp"

namespace vas
{
	Vector2::Vector2(const sdl::Point & point):
		x(static_cast<float>(point.x)), y(static_cast<float>(point.y))
	{
	}

	Vector2::Vector2(float x, float y):
		x(x), y(y)
	{
	}

	Vector2::Vector2(float magnitude, const Angle & value)
	{
		Angle value_;
		uint8_t quaterId = 0;
		if (value <= 90)
			quaterId = 1;
		else if (value <= 180)
			quaterId = 2;
		else if (value <= 270)
			quaterId = 3;
		else if (value <= 360)
			quaterId = 4;

		switch (quaterId)
		{
		case 1:
			value_ = value.toRadian();
			break;
		case 2:
			value_ = (value - 90.0).toRadian();
			break;
		case 3:
			value_ = (value - 180.0).toRadian();
			break;
		case 4:
			value_ = (value - 270.0).toRadian();
			break;
		}
		this->x = static_cast<float>(magnitude * std::sin(value_));
		this->y = static_cast<float>(magnitude * std::cos(value_));
		switch (quaterId)
		{
		case 1:
			this->y = -this->y;
			break;
		case 3:
			this->x = -this->x;
			break;
		case 4:
			this->x = -this->x;
			this->y = -this->y;
			break;
		}
	}

	float Vector2::magnitude() const
	{
		return magnitude({ 0, 0 });
	}

	float Vector2::magnitude(const Vector2 & rhs) const
	{
		return std::hypotf((this->x - rhs.x), (this->y - rhs.y));
	}

	float Vector2::gradient(const Vector2 & rhs) const
	{
		return (rhs.y - this->y) / (rhs.x - this->x);
	}

	Angle Vector2::angle() const
	{
		Vector2 temp{ *this };
		temp.x = std::fabsf(temp.x);
		temp.y = std::fabsf(temp.y);

		if (temp == zerovector) return 0.0f;

		auto quater = getQuaterId();
		switch (quater)
		{
		case 1:
			return Angle{ atan(temp.x / temp.y), Angle::AngleType::rad }.toDegree();
			break;
		case 2:
			return Angle{ atan(temp.y / temp.x), Angle::AngleType::rad }.toDegree() + Angle(90.0);
			break;
		case 3:
			return Angle{ atan(temp.x / temp.y), Angle::AngleType::rad }.toDegree() + Angle(180.0);
			break;
		case 4:
			return Angle{ atan(temp.y / temp.x), Angle::AngleType::rad }.toDegree() + Angle(270.0);
			break;
		}
		return 0.0f;
	}

	bool Vector2::operator==(const Vector2 & rhs) const
	{
		return (x == rhs.x) && (y == rhs.y);
	}

	bool Vector2::operator!=(const Vector2 & rhs) const
	{
		return (x != rhs.x) || (y != rhs.y);
	}

	Vector2 Vector2::operator+(const Vector2 & rhs) const
	{
		Vector2 result(this->x + rhs.x, this->y + rhs.y);
		return result;
	}

	Vector2 Vector2::operator-(const Vector2 & rhs) const
	{
		Vector2 result(this->x - rhs.x, this->y - rhs.y);
		return result;
	}

	Vector2 Vector2::operator*(const Vector2 & rhs) const
	{
		Vector2 result{ this->x * rhs.x, this->y * rhs.y };
		return result;
	}

	Vector2 Vector2::operator*(float rhs) const
	{
		Vector2 result{ this->x * rhs, this->y * rhs };
		return result;
	}

	Vector2 Vector2::operator/(const Vector2 & rhs) const
	{
		Vector2 result{ this->x / rhs.x, this->y / rhs.y };
		return result;
	}

	Vector2 Vector2::operator/(float rhs) const
	{
		Vector2 result{ this->x / rhs, this->y / rhs };
		return result;
	}

	const Vector2 & Vector2::operator+=(const Vector2 & rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}

	const Vector2 & Vector2::operator-=(const Vector2 & rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		return *this;
	}

	const Vector2 & Vector2::operator*=(const Vector2 & rhs)
	{
		this->x *= rhs.x;
		this->y *= rhs.y;
		return *this;
	}

	const Vector2 & Vector2::operator*=(float rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		return *this;
	}

	const Vector2 & Vector2::operator/=(const Vector2 & rhs)
	{
		this->x /= rhs.x;
		this->y /= rhs.y;
		return *this;
	}

	const Vector2 & Vector2::operator/=(float rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
		return *this;
	}

	Vector2::operator sdl::Point() const
	{
		return sdl::Point{ static_cast<int>(x), static_cast<int>(y) };
	}

	uint8_t Vector2::getQuaterId() const
	{
		if (*this == zerovector)
			return 1;
		else if (this->x >= 0 && this->y >= 0)
			return 2;
		else if (this->x < 0 && this->y >= 0)
			return 3;
		else if (this->x < 0 && this->y < 0)
			return 4;
		else if (this->x >= 0 && this->y < 0)
			return 1;
		else
			return 0;
	}
}