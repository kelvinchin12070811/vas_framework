#pragma once
#include "../VASConfig.hpp"

/** @addtogroup math
	  @{
*/
#define ANGLE_FROM_FIRST_QUATER(x) (vas::Angle(x)) /**< Create Angle from first quater. */
#define ANGLE_FROM_SECOND_QUATER(x) (vas::Angle(x + 90.0)) /**< Create Angle from second quater. */
#define ANGLE_FROM_THIRD_QUATER(x) (vas::Angle(x + 180.0)) /**< Create Angle from third quater. */
#define ANGLE_FROM_FOURTH_QUATER(x) (vas::Angle(x + 270.0)) /**< Create Angle from fourth quater. */

/** @} */

//TODO: Fix more calculation error in Angle
namespace vas
{
	/** @addtogroup math
		  @{
	*/
	/** @brief The Angle of lines.

		  The Angle class store the angle of a line from top with clockwise rotation. The quater of it shown like bellow.

			           Fourth quater |    First quater
			        ------------------|-------------------
			            Third quater  |  Second quater

		  The creation of Angle can also done by using these macros:

		   - #ANGLE_FROM_FIRST_QUATER
		   - #ANGLE_FROM_SECOND_QUATER
		   - #ANGLE_FROM_THIRD_QUATER
		   - #ANGLE_FROM_FOURTH_QUATER
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
		Angle();
		Angle(const Angle& rhs);
		/** Construct new instance of Angle.
			  @param rhs Value of the angle.
			  @param type Type of the angle.
		*/
		Angle(double rhs, AngleType type = Angle::AngleType::deg);
		~Angle();

		Angle toRadian() const; /**< Convert current Angle to radian. */
		Angle toDegree() const; /**< Convert current Angle to degree. */

		Angle::AngleType getAngleType() const; /**< Get current angle type. */

		/** @name Overloaded operators
			  @{
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