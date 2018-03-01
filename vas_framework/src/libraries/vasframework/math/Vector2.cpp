#include <cmath>
#include "Vector2.hpp"

namespace vas
{
	Vector2::Vector2()
	{
	}

	Vector2::Vector2(float x, float y):
		x(x), y(y)
	{
	}

	Vector2::~Vector2()
	{
	}

	float Vector2::distance(const Vector2 & rhs) const
	{
		return std::hypotf((this->x - rhs.x), (this->y - rhs.y));
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
		Vector2 result(this->x * rhs.x, this->y * rhs.y);
		return result;
	}

	Vector2 Vector2::operator*(float rhs) const
	{
		Vector2 result(this->x * rhs, this->y * rhs);
		return result;
	}

	Vector2 Vector2::operator/(const Vector2 & rhs) const
	{
		Vector2 result(this->x / rhs.x, this->y / rhs.y);
		return result;
	}

	Vector2 Vector2::operator/(float rhs) const
	{
		Vector2 result(this->x / rhs, this->y / rhs);
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
}