#pragma once

namespace vas
{
	class Vector2
	{
	public:
		Vector2();
		Vector2(float x, float y);
		~Vector2();

		Vector2 operator+(const Vector2& rhs) const;
		Vector2 operator-(const Vector2& rhs) const;
		Vector2 operator*(const Vector2& rhs) const;
		Vector2 operator/(const Vector2& rhs) const;
		Vector2 operator*(float rhs) const;
		Vector2 operator/(float rhs) const;

		const Vector2& operator+=(const Vector2& rhs);
		const Vector2& operator-=(const Vector2& rhs);
		const Vector2& operator*=(const Vector2& rhs);
		const Vector2& operator/=(const Vector2& rhs);
		const Vector2& operator*=(float rhs);
		const Vector2& operator/=(float rhs);

		bool operator==(const Vector2& rhs);
		bool operator!=(const Vector2& rhs);

		float x = 0;
		float y = 0;

		static Vector2 lerp(const Vector2& from, const Vector2& to, float speed);
	};

	inline namespace vector2_functor
	{
		struct less
		{
			bool operator()(const Vector2& lhs, const Vector2& rhs);
		};

		struct more
		{
			bool operator()(const Vector2& lhs, const Vector2& rhs);
		};
	}
}