#include "Rect.hpp"
#include "../boolean_cast.hpp"

namespace vas::sdl
{
	Rect::Rect(int x, int y, int w, int h):
		x(x), y(y), w(w), h(h)
	{
	}

	Rect::Rect(SDL_Rect rect):
		x(rect.x), y(rect.y), w(rect.w), h(rect.h)
	{
	}

	bool Rect::intersectWith(const Rect & other) const
	{
		auto first = static_cast<SDL_Rect>(*this);
		auto second = static_cast<SDL_Rect>(other);
		return boolean_cast(SDL_HasIntersection(&first, &second));
	}

	Rect Rect::getIntersectionBetween(const Rect & other) const
	{
		SDL_Rect result = { 0 };
		auto first = static_cast<SDL_Rect>(*this);
		auto second = static_cast<SDL_Rect>(other);
		SDL_IntersectRect(&first, &second, &result);
		return static_cast<Rect>(result);
	}

	Rect Rect::getUinonBetween(const Rect & other) const
	{
		SDL_Rect result = { 0 };
		auto first = static_cast<SDL_Rect>(*this);
		auto second = static_cast<SDL_Rect>(other);
		SDL_UnionRect(&first, &second, &result);
		return static_cast<Rect>(result);
	}

	bool Rect::enclosePoints(const std::vector<Point>& points, Rect * result) const
	{
		auto clip = static_cast<SDL_Rect>(*this);
		SDL_Rect resultRaw{ 0 };
		std::vector<SDL_Point> pointsRaw;
		pointsRaw.reserve(points.size());

		for (auto itr = points.begin(); itr != points.end(); itr++)
			pointsRaw.push_back(static_cast<SDL_Point>(*itr));

		bool success = boolean_cast(SDL_EnclosePoints(pointsRaw.data(), static_cast<int>(pointsRaw.size()), &clip, &resultRaw));
		if (success && result != nullptr)
			*result = static_cast<Rect>(resultRaw);
		return success;
	}

	bool Rect::intersectWithLine(Point & lineBegin, Point& lineEnd) const
	{
		auto thisInstance = static_cast<SDL_Rect>(*this);
		return boolean_cast(SDL_IntersectRectAndLine(&thisInstance, &lineBegin.x, &lineBegin.y, &lineEnd.x, &lineEnd.y));
	}

	bool Rect::operator==(const Rect & rhs) const
	{
		return (this->x == rhs.x) && (this->y == rhs.y) &&
			(this->w == rhs.w) && (this->h == rhs.h);
	}

	bool Rect::operator!=(const Rect & rhs) const
	{
		return (this->x != rhs.x) || (this->y != rhs.y) ||
			(this->w != rhs.w) || (this->h != rhs.h);
	}

	Rect & Rect::operator=(const SDL_Rect & rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;
		this->w = rhs.w;
		this->h = rhs.h;
		return *this;
	}

	Rect::operator SDL_Rect()
	{
		return SDL_Rect{ x, y, w, h };
	}

	Rect::operator const SDL_Rect() const
	{
		return SDL_Rect{ x, y, w, h };
	}
}