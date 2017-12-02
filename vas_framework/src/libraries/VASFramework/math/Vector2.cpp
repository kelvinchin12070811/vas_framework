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

	Vector2 Vector2::operator+(const Vector2& rhs) const
	{
		Vector2 temp = *this;
		temp.x += rhs.x;
		temp.y += rhs.y;
		return temp;
	}

	Vector2 Vector2::operator-(const Vector2& rhs) const
	{
		Vector2 temp = *this;
		temp.x -= rhs.x;
		temp.y -= rhs.y;
		return temp;
	}

	Vector2 Vector2::operator*(const Vector2& rhs) const
	{
		Vector2 temp = *this;
		temp.x *= rhs.x;
		temp.y *= rhs.y;
		return temp;
	}

	Vector2 Vector2::operator/(const Vector2& rhs) const
	{
		Vector2 temp = *this;
		temp.x /= rhs.x;
		temp.y /= rhs.y;
		return temp;
	}

	Vector2 Vector2::operator*(float rhs) const
	{
		Vector2 temp = *this;
		temp.x *= rhs;
		temp.y *= rhs;
		return temp;
	}

	Vector2 Vector2::operator/(float rhs) const
	{
		Vector2 temp = *this;
		temp.x /= rhs;
		temp.y /= rhs;
		return temp;
	}

	const Vector2& Vector2::operator+=(const Vector2& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}

	const Vector2& Vector2::operator-=(const Vector2& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		return *this;
	}

	const Vector2& Vector2::operator*=(const Vector2& rhs)
	{
		this->x *= rhs.x;
		this->y *= rhs.y;
		return *this;
	}

	const Vector2& Vector2::operator/=(const Vector2& rhs)
	{
		this->x /= rhs.x;
		this->y /= rhs.y;
		return *this;
	}

	const Vector2& Vector2::operator*=(float rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		return *this;
	}

	const Vector2& Vector2::operator/=(float rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
		return *this;
	}

	bool Vector2::operator==(const Vector2 & rhs)
	{
		return (x == rhs.x) && (y == rhs.y);
	}

	bool Vector2::operator!=(const Vector2 & rhs)
	{
		return (x != rhs.x) || (y != rhs.y);
	}

	Vector2 Vector2::lerp(const Vector2 & from, const Vector2 & to, float speed)
	{
		if (speed > 1.0f) speed = 1.0f;
		if (speed < 0) speed = 0;
		Vector2 result;
		result.x = ((1 - speed) * from.x) + (to.x * speed);
		result.y = ((1 - speed) * from.y) + (to.y * speed);
		return result;
	}

	namespace vector2_functor
	{
		bool less::operator()(const Vector2 & lhs, const Vector2 & rhs)
		{
			if (lhs.x < rhs.x) return true;
			else return lhs.y < rhs.y;
		}

		bool more::operator()(const Vector2 & lhs, const Vector2 & rhs)
		{
			if (lhs.x > rhs.x) return true;
			else return lhs.y > rhs.y;
		}
	}
}