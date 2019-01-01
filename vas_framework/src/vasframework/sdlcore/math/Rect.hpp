//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <SDL.h>
#include <vector>
#include "Point.hpp"

namespace vas::sdl
{
	/** @addtogroup sdl_basic
		  @{
	*/
	/** @brief A rectangle, with the origin at the upper left. */
	class VAS_DECLSPEC Rect
	{ /** @} */
	public:
		Rect() = default; /**< Create empty rect. */
		Rect(int x, int y, int w, int h); /**< Create Rect with value. */
		explicit Rect(SDL_Rect rect); /**< Create Rect from SDL_Rect. */

		int x{ 0 }; /**< x position of rect. */
		int y{ 0 }; /**< y position of rect. */
		int w{ 0 }; /**< width of rect. */
		int h{ 0 }; /**< height of rect. */

		/** Determine if twr Rect is intersected.
			  @param other Rect to compare.
			  @return true if both Rects are intersected.
		*/
		bool intersectWith(const Rect& other) const;
		/** Calculate the intersection between two rect.
			  @param other Rect to compare.
			  @retval vas::sdl::Rect Area intersected between two Rects.
		*/
		Rect getIntersectionBetween(const Rect& other) const;
		/** Calculate the union between two rect.
			  @param other Rect to compare.
			  @retval vas::sdl::Rect Area of union between two Rects.
		*/
		Rect getUinonBetween(const Rect& other) const;
		/** Calculate a minimal rectangle enclosing a set of points.
			  @param points Points to enclose.
			  @param result Output of result.
			  @return true if any points were within the clipping rect.
		*/
		bool enclosePoints(const std::vector<Point>& points, Rect* result) const;
		/** Calculate the intersection of a rectangle and line segment.
			  @param lineBegin Starting point of the line.
			  @param lineEnd Ending of the line.
			  @return true if there is an intersection, false otherwise.
		*/
		bool intersectWithLine(Point& lineBegin, Point& lineEnd) const;

		/** @name Overloaded operators
			  @{
		*/
		bool operator==(const Rect& rhs) const; /**< Compare two rect if is equal. */
		bool operator!=(const Rect& rhs) const; /**< Compare two rect if is not equal. */
		/** @} */
		Rect& operator=(const SDL_Rect& rhs); /**< Assign with SDL_Rect. */
		/** @name Overloaded operators*/
		operator SDL_Rect(); /**< Cast to SDL_Rect. */
		operator const SDL_Rect() const; /**< Cast to const SDL_Rect. */
		/** @} */
	};
}