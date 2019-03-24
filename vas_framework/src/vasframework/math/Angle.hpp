//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include "../VASConfig.hpp"

namespace vas
{
	/**
	 * @ingroup math
	 * @{
	 */
	/**
	 * @brief The Angle of lines.
	 * 
	 * The Angle class store the angle of a line from top with clockwise rotation.
	 */
	class VAS_DECLSPEC Angle
	{ /** @} */
	public:
		/** The type of angle. */
		enum class AngleType {
			deg, /**< degree. */
			rad /**< radian. */
		};
	public:
		Angle() = default;
		Angle(const Angle& rhs);
		/**
		 * Construct new instance of Angle.
		 * @param[in] rhs Value of the angle.
		 * @param[in] type (Optional)Type of the angle.
		 */
		Angle(double rhs, AngleType type = Angle::AngleType::deg);

		Angle toRadian() const; /**< Convert current Angle to radian. */
		Angle toDegree() const; /**< Convert current Angle to degree. */

		Angle::AngleType getAngleType() const; /**< Get current angle type. */

		/**
		 * @name Overloaded operators
		 * @{
		 */
		bool operator==(const Angle& rhs) const; /**< Compare if two Angle with same value. */
		bool operator!=(const Angle& rhs) const; /**< Compare if two Angle does not with same value. */
		const Angle& operator=(const Angle& rhs);
		const Angle& operator=(double rhs);
		
		Angle& operator++(int); /**< Self increment by 1. */
		Angle& operator--(int); /**< Self decrement by 1. */

		Angle operator+(const Angle& rhs) const; /**< Add two Angle and return result. */
		Angle operator-(const Angle& rhs) const; /**< Minus two Angle and return result. */
		Angle operator*(const Angle& rhs) const; /**< Multiply two Angle and return result. */
		Angle operator/(const Angle& rhs) const; /**< Divide two Angle and return result. */

		Angle operator+(double rhs) const; /**< Add two Angle and return result. */
		Angle operator-(double rhs) const; /**< Minus two Angle and return result. */
		Angle operator*(double rhs) const; /**< Multiply two Angle and return result. */
		Angle operator/(double rhs) const; /**< Divide two Angle and return result. */

		const Angle& operator+=(const Angle& rhs); /**< Add this Angle with other. */
		const Angle& operator-=(const Angle& rhs); /**< Minus this Angle with other. */
		const Angle& operator*=(const Angle& rhs); /**< Multiply this Angle with other. */
		const Angle& operator/=(const Angle& rhs); /**< Divide this Angle with other. */

		const Angle& operator+=(double rhs); /**< Add this Angle with other. */
		const Angle& operator-=(double rhs); /**< Minus this Angle with other. */
		const Angle& operator*=(double rhs); /**< Multiply this Angle with other. */
		const Angle& operator/=(double rhs); /**< Divide this Angle with other. */

		operator double() const; /**< Inplict cast Angle to double. */
		/** @} */
	private:
		void clampValue();

		double value{ 0 };
		AngleType angleType{ AngleType::deg };
	};
}