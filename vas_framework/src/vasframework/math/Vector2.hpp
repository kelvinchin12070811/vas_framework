//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <cstdint>
#include "../sdlcore/math/Point.hpp"
#include "../VASConfig.hpp"

namespace vas
{
	class Angle;
	/** @addtogroup math
		  @{
	*/
	/** @brief A quantity that contain both magnitude and direction.
		  
		  Vector2 is a 2D quantity that recorded the magnitude and direction of an 2D elements. It also represent the position
		  of the 2D elements if it is pointing from the origin(0, 0).

		  Beware that the Vector2 use screen's pixel cartesian coordinate system instead of real world cartesian coordinate
		  system, this mean that the origin of the Vector2 are at the top-left corner of the screen.
	*/
	class VAS_DECLSPEC Vector2
	{ /** @} */
	public:
		/** Create a new vector with zero vector. */
		Vector2() = default;
		Vector2(const Vector2&) = default;
		Vector2(Vector2&&) = default;
		Vector2& operator=(const Vector2&) = default;
		Vector2& operator=(Vector2&&) = default;
		~Vector2() {}

		explicit Vector2(const sdl::Point& point); /**< Cast from sdl::Point. */
		/** Create new instance of Vector2 from coordinate.
			  @param x X coordinate of the vector.
			  @param y Y coordinate of the vector.
		*/
		Vector2(float x, float y);
		/** Create new instance of Vector2 from magnitude and angle.
			  @param magnitude Magnitude or distance of the vector.
			  @param value Angle of the vector line.
		*/
		Vector2(float magnitude, const Angle& value);

		/** Get the magnitude of vector from origin(0, 0). */
		float magnitude() const;
		/** Get the magnitude of vector from specified position. */
		float magnitude(const Vector2& rhs) const;
		/** Get the gradient of the vector from other vector. */
		float gradient(const Vector2& rhs = Vector2()) const;
		/** Get the angle of the vector line from the origin. */
		Angle angle() const;
		/** Get the unit vector(normalized vector) of this vector. */
		Vector2 normalize() const;
		/** Get the vector with absolute value(no negative number) from this vector. */
		Vector2 absolute() const;
		/** Linear interpolation algorithm.
			  @param from Starting point of lerp algorithm.
			  @param to Ending point of lerp algorithm.
			  @param speed speed of moving point, must in between 0 and 1 (outside this range will be clampped).
			  @return Current position on @p speed.
		*/
		static Vector2 lerp(const Vector2& from, const Vector2& to, float speed);

		/** @name Overloaded operators
			  @{
		*/
		bool operator==(const Vector2& rhs) const; /**< Determine if both of the vectors with same value. */
		bool operator!=(const Vector2& rhs) const; /**< Determine if both vectors does not with same value. */
		bool operator<(const Vector2& rhs) const; /**< Determine if rhs is less than this. */
		bool operator<=(const Vector2& rhs) const; /**< Determine if rhs is less than or equal to this. */
		bool operator>(const Vector2& rhs) const; /**< Determine if rhs is greather than this. */
		bool operator>= (const Vector2& rhs) const; /**< Determine if rhs is greather than or equal to this. */

		Vector2 operator+(const Vector2& rhs) const; /**< Add two vector and return a new instance of vector of result. */
		Vector2 operator-(const Vector2& rhs) const; /**< Minus two vector and return a new instance of vector of result. */
		Vector2 operator*(const Vector2& rhs) const; /**< Multiply two vector and return a new instance of vector of result. */
		Vector2 operator*(float rhs) const; /**< Multiply the vector with a factor and return result. */
		Vector2 operator/(const Vector2& rhs) const; /**< Divide two vector and return a new instance of vector of result. */
		Vector2 operator/(float rhs) const; /**< Divide the vector with a factor and return result. */

		const Vector2& operator+=(const Vector2& rhs); /**< Add this vector with other vector. */
		const Vector2& operator-=(const Vector2& rhs); /**< Minus this vector with other vector. */
		const Vector2& operator*=(const Vector2& rhs); /**< Multiply this vector with other vector. */
		const Vector2& operator*=(float rhs); /**< Multiply this vector with a factor. */
		const Vector2& operator/=(const Vector2& rhs); /**< Divide this vector with other vector. */
		const Vector2& operator/=(float rhs); /**< Divide this vector with a factor. */
		/** @} */

		/** @name Overloaded operators
			  @{
		*/
		explicit operator sdl::Point() const; /**< Cast to sdl::Point. */
		/** @} */
	public:
		float x{ 0 }; /**< x position of the vector on the cartiesain plan. */
		float y{ 0 }; /**< y position of the vector on the cartiesain plan. */
	private:
		uint8_t getQuaterId() const;
	};

	/** @memberof Vector2
		  Zero vector of a vector, with a value of (0, 0) which pointing from the origin.
	*/
	const Vector2 zerovector{};
	/** @memberof Vector2
		  Vector that hold epsilon of float for both x and y axises.
	*/
	const Vector2 epsilonvector{ std::numeric_limits<float>::epsilon(), std::numeric_limits<float>::epsilon() };
}