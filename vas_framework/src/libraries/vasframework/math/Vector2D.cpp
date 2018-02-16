#include <cmath>
#include "Vector2D.hpp"

namespace vas
{
	Vector2D::Vector2D()
	{
	}

	Vector2D::Vector2D(float x, float y):
		x(x), y(y)
	{
	}

	Vector2D::~Vector2D()
	{
	}

	float Vector2D::distance(const Vector2D & rhs) const
	{
		return std::hypotf((this->x - rhs.x), (this->y - rhs.y));
	}

	bool Vector2D::operator==(const Vector2D & rhs) const
	{
		return (x == rhs.x) && (y == rhs.y);
	}

	bool Vector2D::operator!=(const Vector2D & rhs) const
	{
		return (x != rhs.x) || (y != rhs.y);
	}

	Vector2D Vector2D::operator+(const Vector2D & rhs) const
	{
		Vector2D result(this->x + rhs.x, this->y + rhs.y);
		return result;
	}

	Vector2D Vector2D::operator-(const Vector2D & rhs) const
	{
		Vector2D result(this->x - rhs.x, this->y - rhs.y);
		return result;
	}

	Vector2D Vector2D::operator*(const Vector2D & rhs) const
	{
		Vector2D result(this->x * rhs.x, this->y * rhs.y);
		return result;
	}

	Vector2D Vector2D::operator*(float rhs) const
	{
		Vector2D result(this->x * rhs, this->y * rhs);
		return result;
	}

	Vector2D Vector2D::operator/(const Vector2D & rhs) const
	{
		Vector2D result(this->x / rhs.x, this->y / rhs.y);
		return result;
	}

	Vector2D Vector2D::operator/(float rhs) const
	{
		Vector2D result(this->x / rhs, this->y / rhs);
		return result;
	}

	const Vector2D & Vector2D::operator+=(const Vector2D & rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}

	const Vector2D & Vector2D::operator-=(const Vector2D & rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		return *this;
	}

	const Vector2D & Vector2D::operator*=(const Vector2D & rhs)
	{
		this->x *= rhs.x;
		this->y *= rhs.y;
		return *this;
	}

	const Vector2D & Vector2D::operator*=(float rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		return *this;
	}

	const Vector2D & Vector2D::operator/=(const Vector2D & rhs)
	{
		this->x /= rhs.x;
		this->y /= rhs.y;
		return *this;
	}

	const Vector2D & Vector2D::operator/=(float rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
		return *this;
	}
}