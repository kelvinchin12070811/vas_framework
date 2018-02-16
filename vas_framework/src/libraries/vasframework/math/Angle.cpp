#include <algorithm>
#include "Angle.hpp"

namespace vas
{
	Angle::Angle()
	{
	}

	Angle::Angle(const Angle & rhs):
		value(rhs.value)
	{
		clampValue();
	}

	Angle::Angle(double rhs):
		value(rhs)
	{
		clampValue();
	}

	Angle::~Angle()
	{
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

	Angle Angle::operator+(const Angle & rhs) const
	{
		Angle result(this->value + rhs.value);
		result.clampValue();
		return result;
	}

	Angle Angle::operator-(const Angle & rhs) const
	{
		Angle result(this->value - rhs.value);
		result.clampValue();
		return result;
	}

	Angle Angle::operator*(const Angle & rhs) const
	{
		Angle result(this->value * rhs.value);
		result.clampValue();
		return result;
	}

	Angle Angle::operator/(const Angle & rhs) const
	{
		Angle result(this->value / rhs.value);
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

	Angle::operator double() const
	{
		return this->value;
	}

	void Angle::clampValue()
	{
		if (value >= 360)
			value -= 360;
		else if (value < 0)
			value += 360;
	}
}