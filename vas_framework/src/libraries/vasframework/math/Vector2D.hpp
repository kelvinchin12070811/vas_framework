#pragma once

namespace vas
{
	class Vector2D
	{
	public:
		Vector2D();
		Vector2D(float x, float y);
		~Vector2D();

		float distance(const Vector2D& rhs) const;

		bool operator==(const Vector2D& rhs) const;
		bool operator!=(const Vector2D& rhs) const;

		Vector2D operator+(const Vector2D& rhs) const;
		Vector2D operator-(const Vector2D& rhs) const;
		Vector2D operator*(const Vector2D& rhs) const;
		Vector2D operator*(float rhs) const;
		Vector2D operator/(const Vector2D& rhs) const;
		Vector2D operator/(float rhs) const;

		const Vector2D& operator+=(const Vector2D& rhs);
		const Vector2D& operator-=(const Vector2D& rhs);
		const Vector2D& operator*=(const Vector2D& rhs);
		const Vector2D& operator*=(float rhs);
		const Vector2D& operator/=(const Vector2D& rhs);
		const Vector2D& operator/=(float rhs);

		float x{ 0 };
		float y{ 0 };
	};
}