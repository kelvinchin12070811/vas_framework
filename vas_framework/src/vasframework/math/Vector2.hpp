#pragma once
#include <cstdint>
#include "../sdlcore/math/Point.hpp"
#include "../VASConfig.hpp"

namespace vas
{
	class Angle;
	class VAS_DECLSPEC Vector2
	{
	public:
		Vector2();
		explicit Vector2(const sdl::Point& point);
		Vector2(float x, float y);
		Vector2(float magnitude, const Angle& value);
		Vector2(const Vector2&) = default;
		Vector2(Vector2&&) = default;
		~Vector2();

		//from (0, 0)
		float magnitude() const;
		//from specified position
		float magnitude(const Vector2& rhs) const;
		float gradient(const Vector2& rhs = Vector2()) const;
		Angle angle() const;

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

		Vector2& operator=(const Vector2&) = default;
		Vector2& operator=(Vector2&&) = default;

		explicit operator sdl::Point() const;
	public:
		float x{ 0 };
		float y{ 0 };
	private:
		uint8_t getQuaterId() const;
	};

	const Vector2 zerovector{};
}