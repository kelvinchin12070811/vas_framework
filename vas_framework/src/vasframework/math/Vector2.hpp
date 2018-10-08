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
		Vector2();
		explicit Vector2(const sdl::Point& point);
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
		Vector2(const Vector2&) = default;
		Vector2(Vector2&&) = default;
		~Vector2();

		/** Get the magnitude of vector from origin(0, 0). */
		float magnitude() const;
		/** Get the magnitude of vector from specified position. */
		float magnitude(const Vector2& rhs) const;
		/** Get the gradient of the vector from other vector. */
		float gradient(const Vector2& rhs = Vector2()) const;
		/** Get the angle of the vector line from the origin. */
		Angle angle() const;

		/** @name Overloaded operators
			  @{
		*/
		bool operator==(const Vector2& rhs) const; /**< Determine if both of the vectors with same value. */
		bool operator!=(const Vector2& rhs) const; /**< Determine if both vectors does not with same value. */

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

		Vector2& operator=(const Vector2&) = default;
		Vector2& operator=(Vector2&&) = default;

		explicit operator sdl::Point() const;
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
}