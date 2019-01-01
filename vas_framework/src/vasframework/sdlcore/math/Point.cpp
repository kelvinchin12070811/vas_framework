//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "Point.hpp"

namespace vas::sdl
{
	Point::Point(int x, int y):
		x(x), y(y)
	{
	}

	Point::Point(const SDL_Point & point):
		x(point.x), y(point.y)
	{
	}

	int & Point::w()
	{
		return x;
	}

	const int & Point::w() const
	{
		return x;
	}

	int & Point::h()
	{
		return y;
	}

	const int & Point::h() const
	{
		return y;
	}

	Point::operator SDL_Point()
	{
		return SDL_Point{ x, y };
	}

	Point::operator const SDL_Point() const
	{
		return SDL_Point{ x, y };
	}

	bool Point::operator==(const Point & rhs) const
	{
		return (this->x == rhs.x) && (this->y == rhs.y);
	}

	bool Point::operator!=(const Point & rhs) const
	{
		return (this->x != rhs.x) || (this->y != rhs.y);
	}

	Point Point::operator+(const Point & rhs) const
	{
		return Point{ this->x + rhs.x, this->y + rhs.y };
	}

	Point Point::operator-(const Point & rhs) const
	{
		return Point{ this->x - rhs.x, this->y - rhs.y };
	}

	Point Point::operator*(const Point & rhs) const
	{
		return Point{ this->x * rhs.x, this->y * rhs.y };
	}

	Point Point::operator/(const Point & rhs) const
	{
		return Point(this->x / rhs.x, this->y / rhs.y);
	}

	const Point & Point::operator+=(const Point & rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}

	const Point & Point::operator-=(const Point & rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		return *this;
	}
	
	const Point & Point::operator*=(const Point & rhs)
	{
		this->x *= rhs.x;
		this->y *= rhs.y;
		return *this;
	}

	const Point & Point::operator/=(const Point & rhs)
	{
		this->x /= rhs.x;
		this->y /= rhs.y;
		return *this;
	}
}