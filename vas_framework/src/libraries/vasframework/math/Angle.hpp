#pragma once
#include "../VASConfig.hpp"

#define ANGLE_FROM_FIRST_QUATER(x) (vas::Angle(x))
#define ANGLE_FROM_SECOND_QUATER(x) (vas::Angle(x + 90.0))
#define ANGLE_FROM_THIRD_QUATER(x) (vas::Angle(x + 180.0))
#define ANGLE_FROM_FOURT_QUATER(x) (vas::Angle(x + 270.0))

//TODO: Fix more calculation error in Angle
namespace vas
{
	class Angle
	{
	public:
		enum class AngleType { deg, rad };
	public:
		Angle();
		Angle(const Angle& rhs);
		Angle(double rhs, AngleType type = Angle::AngleType::deg);
		~Angle();

		Angle toRadian() const;
		Angle toDegree() const;

		Angle::AngleType getAngleType() const;

		bool operator==(const Angle& rhs) const;
		bool operator!=(const Angle& rhs) const;
		const Angle& operator=(const Angle& rhs);
		const Angle& operator=(double rhs);
		
		Angle& operator++(int);
		Angle& operator--(int);

		Angle operator+(const Angle& rhs) const;
		Angle operator-(const Angle& rhs) const;
		Angle operator*(const Angle& rhs) const;
		Angle operator/(const Angle& rhs) const;

		Angle operator+(double rhs) const;
		Angle operator-(double rhs) const;
		Angle operator*(double rhs) const;
		Angle operator/(double rhs) const;

		const Angle& operator+=(const Angle& rhs);
		const Angle& operator-=(const Angle& rhs);
		const Angle& operator*=(const Angle& rhs);
		const Angle& operator/=(const Angle& rhs);

		const Angle& operator+=(double rhs);
		const Angle& operator-=(double rhs);
		const Angle& operator*=(double rhs);
		const Angle& operator/=(double rhs);

		operator double() const;
	private:
		void clampValue();

		double value{ 0 };
		AngleType angleType{ AngleType::deg };
	};
}