//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include <algorithm>
#include <boost/math/constants/constants.hpp>
#include "Angle.hpp"

namespace vas
{
	Angle::Angle(const Angle & rhs):
		value(rhs.value)
	{
		clampValue();
	}

	Angle::Angle(double rhs, Angle::AngleType type):
		value(rhs), angleType(type)
	{
		clampValue();
	}

	Angle Angle::toRadian() const
	{
		using namespace boost::math;
		return Angle{ (value / 180) * constants::pi<double>(), AngleType::rad };
	}

	Angle Angle::toDegree() const
	{
		using namespace boost::math;
		return { (value / constants::pi<double>()) * 180, AngleType::deg };
	}

	Angle::AngleType Angle::getAngleType() const
	{
		return angleType;
	}

	bool Angle::operator==(const Angle & rhs) const
	{
		return this->value == rhs.value;
	}

	bool Angle::operator!=(const Angle & rhs) const
	{
		return this->value != rhs.value;
	}

	const Angle & Angle::operator=(const Angle & rhs)
	{
		this->value = rhs.value;
		clampValue();
		return *this;
	}

	const Angle & Angle::operator=(double rhs)
	{
		this->value = rhs;
		clampValue();
		return *this;
	}

	Angle & Angle::operator++(int)
	{
		this->value++;
		clampValue();
		return *this;
	}

	Angle & Angle::operator--(int)
	{
		this->value--;
		clampValue();
		return *this;
	}

	Angle Angle::operator+(const Angle & rhs) const
	{
		Angle result{ this->value + rhs.value };
		result.clampValue();
		return result;
	}

	Angle Angle::operator-(const Angle & rhs) const
	{
		Angle result{ this->value - rhs.value };
		result.clampValue();
		return result;
	}

	Angle Angle::operator*(const Angle & rhs) const
	{
		Angle result{ this->value * rhs.value };
		result.clampValue();
		return result;
	}

	Angle Angle::operator/(const Angle & rhs) const
	{
		Angle result{ this->value / rhs.value };
		result.clampValue();
		return result;
	}

	Angle Angle::operator+(double rhs) const
	{
		Angle result{ this->value + rhs };
		result.clampValue();
		return result;
	}

	Angle Angle::operator-(double rhs) const
	{
		Angle result{ this->value - rhs };
		result.clampValue();
		return result;
	}

	Angle Angle::operator*(double rhs) const
	{
		Angle result{ this->value * rhs };
		result.clampValue();
		return result;
	}

	Angle Angle::operator/(double rhs) const
	{
		Angle result{ this->value / rhs };
		result.clampValue();
		return result;
	}

	const Angle & Angle::operator+=(const Angle & rhs)
	{
		this->value += rhs.value;
		clampValue();
		return *this;
	}

	const Angle & Angle::operator-=(const Angle & rhs)
	{
		this->value -= rhs.value;
		clampValue();
		return *this;
	}

	const Angle & Angle::operator*=(const Angle & rhs)
	{
		this->value *= rhs.value;
		clampValue();
		return *this;
	}

	const Angle & Angle::operator/=(const Angle & rhs)
	{
		this->value /= rhs.value;
		clampValue();
		return *this;
	}

	const Angle & Angle::operator+=(double rhs)
	{
		this->value += rhs;
		clampValue();
		return *this;
	}

	const Angle & Angle::operator-=(double rhs)
	{
		this->value -= rhs;
		clampValue();
		return *this;
	}

	const Angle & Angle::operator*=(double rhs)
	{
		this->value *= rhs;
		clampValue();
		return *this;
	}

	const Angle & Angle::operator/=(double rhs)
	{
		this->value /= rhs;
		clampValue();
		return *this;
	}

	Angle::operator double() const
	{
		return this->value;
	}

	void Angle::clampValue()
	{
		if (this->angleType == Angle::AngleType::deg)
		{
			if (value >= 360)
				value -= 360;
			else if (value < 0)
				value += 360;
		}
		else
		{
			if (value >= 2 * boost::math::constants::pi<double>())
				value -= 2 * boost::math::constants::pi<double>();
			else if (value < 0)
				value += 2 * boost::math::constants::pi<double>();
		}
	}
}