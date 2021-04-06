//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <SDL2/SDL.h>
#include "../../VASConfig.hpp"

namespace vas::sdl
{
	/**
	 * @ingroup sdl_basic
	 * @{
	 */
	/** @brief The structure that defines a point. */
	class VAS_DECLSPEC Point
	{ /** @} */
	public:
		Point() = default; /**< Empty point(0, 0). */
		Point(int x, int y); /**< Create point from coordinate. */
		explicit Point(const SDL_Point& point);
		Point(const Point&) = default;
		Point(Point&&) = default;
		Point& operator=(const Point&) = default;
		Point& operator=(Point&&) = default;
		~Point() {}

		int x{ 0 }; /**< x position of point. */
		int y{ 0 }; /**< y position of point. */

		int& w(); /**< Get width, alias of Point::x. */
		const int& w() const; /**< Get const width, alias of const Point::x. */
		int& h(); /**< Get height, alias of Point::y. */
		const int& h() const; /**< Get const height, alias of const Point::y. */

		explicit operator SDL_Point(); /**< Cast to SDL_Point. */
		explicit operator const SDL_Point() const; /**< Cast to const SDL_Point. */

		/**
		 * @name Overloaded operators
		 * @{
		 */
		bool operator==(const Point& rhs) const; /**< Compare if two Point is equal. */
		bool operator!=(const Point& rhs) const; /**< Compare if two Point is not equal. */

		Point operator+(const Point& rhs) const; /**< Add two Point. */
		Point operator-(const Point& rhs) const; /**< Minus two Point. */
		Point operator*(const Point& rhs) const; /**< Multiply two Point. */
		Point operator/(const Point& rhs) const; /**< Divide two Point. */

		const Point& operator+=(const Point& rhs); /**< Add to this Point. */
		const Point& operator-=(const Point& rhs); /**< Minus from this Point. */
		const Point& operator*=(const Point& rhs); /**< Multiply with this Point. */
		const Point& operator/=(const Point& rhs); /**< Divide with this Point. */
		/** @} */
	};
}