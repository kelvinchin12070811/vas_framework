#include "Point.hpp"

namespace sdl
{
	Point::Point()
	{
	}

	Point::Point(int x, int y):
		x(x), y(y)
	{
	}

	Point::Point(const SDL_Point & point):
		x(point.x), y(point.y)
	{
	}

	Point::~Point()
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
		return Point(this->x + rhs.x, this->y + rhs.y);
	}

	Point Point::operator-(const Point & rhs) const
	{
		return Point(this->x - rhs.x, this->y - rhs.y);
	}

	Point Point::operator*(const Point & rhs) const
	{
		return Point(this->x * rhs.x, this->y * rhs.y);
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