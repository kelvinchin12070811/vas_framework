#pragma once
#include <SDL.h>
#include <vector>
#include "Point.hpp"

namespace vas::sdl
{
	class VAS_DECLSPEC Rect
	{
	public:
		Rect();
		Rect(int x, int y, int w, int h);
		Rect(const Rect& rect);
		explicit Rect(SDL_Rect rect);
		~Rect();
		int x{ 0 };
		int y{ 0 };
		int w{ 0 };
		int h{ 0 };

		bool intersectWith(const Rect& other) const;
		Rect getIntersectionBetween(const Rect& other) const;
		Rect getUinonBetween(const Rect& other) const;
		bool enclosePoints(const std::vector<Point>& points, Rect* result) const;
		bool intersectWithLine(Point& lineBegin, Point& lineEnd) const;

		bool operator==(const Rect& rhs) const;
		bool operator!=(const Rect& rhs) const;

		Rect& operator=(const Rect& rhs);
		Rect& operator=(const SDL_Rect& rhs);

		operator SDL_Rect();
		operator const SDL_Rect() const;
	};
}