#pragma once
#include <SDL.h>
#include "../../VASConfig.hpp"

namespace sdl
{
	class VAS_DECLSPEC Point
	{
	public:
		Point();
		Point(int x, int y);
		explicit Point(const SDL_Point& point);
		~Point();

		int x = 0;
		int y = 0;

		explicit operator SDL_Point();
		explicit operator const SDL_Point() const;

		Point operator+(const Point& rhs) const;
		Point operator-(const Point& rhs) const;
		Point operator*(const Point& rhs) const;
		Point operator/(const Point& rhs) const;

		const Point& operator+=(const Point& rhs);
		const Point& operator-=(const Point& rhs);
		const Point& operator*=(const Point& rhs);
		const Point& operator/=(const Point& rhs);
	};
}