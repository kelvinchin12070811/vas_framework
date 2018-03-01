#pragma once

namespace vas
{
	class Vector2
	{
	public:
		Vector2();
		Vector2(float x, float y);
		~Vector2();

		float distance(const Vector2& rhs) const;

		bool operator==(const Vector2& rhs) const;
		bool operator!=(const Vector2& rhs) const;

		Vector2 operator+(const Vector2& rhs) const;
		Vector2 operator-(const Vector2& rhs) const;
		Vector2 operator*(const Vector2& rhs) const;
		Vector2 operator*(float rhs) const;
		Vector2 operator/(const Vector2& rhs) const;
		Vector2 operator/(float rhs) const;

		const Vector2& operator+=(const Vector2& rhs);
		const Vector2& operator-=(const Vector2& rhs);
		const Vector2& operator*=(const Vector2& rhs);
		const Vector2& operator*=(float rhs);
		const Vector2& operator/=(const Vector2& rhs);
		const Vector2& operator/=(float rhs);

		float x{ 0 };
		float y{ 0 };
	};
}