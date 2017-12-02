#include "Angle.hpp"

namespace vas
{
	Angle::Angle()
	{
	}

	Angle::Angle(double value):
		value(value)
	{
		clampValue();
	}

	const double & Angle::get() const
	{
		return value;
	}

	double & Angle::get()
	{
		return value;
	}

	const Angle & Angle::operator=(const Angle & rhs)
	{
		this->value = rhs.value;
		clampValue();
		return *this;
	}

	const Angle & Angle::operator++(int)
	{
		this->value++;
		clampValue();
		return *this;
	}

	const Angle & Angle::operator--(int)
	{
		this->value--;
		clampValue();
		return *this;
	}

	Angle Angle::operator+(const Angle & rhs) const
	{
		return Angle(this->value + rhs.value);
	}

	Angle Angle::operator-(const Angle & rhs) const
	{
		return Angle(this->value - rhs.value);
	}

	Angle Angle::operator*(const Angle & rhs) const
	{
		return Angle(this->value * rhs.value);
	}

	Angle Angle::operator/(const Angle & rhs) const
	{
		return Angle(this->value / rhs.value);
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

	bool Angle::operator>=(const Angle & rhs) const
	{
		return this->value >= rhs.value;
	}

	bool Angle::operator<=(const Angle & rhs) const
	{
		return this->value <= rhs.value;
	}

	bool Angle::operator>(const Angle & rhs) const
	{
		return this->value > rhs.value;
	}

	bool Angle::operator<(const Angle & rhs) const
	{
		return this->value < rhs.value;
	}

	bool Angle::operator==(const Angle & rhs) const
	{
		return this->value == rhs.value;
	}

	bool Angle::operator!=(const Angle & rhs) const
	{
		return this->value != rhs.value;
	}

	Angle::~Angle()
	{
	}

	void Angle::clampValue()
	{
		if (value > 360.0)
			value -= 360.0;
		if (value < 0)
			value += 360;
	}
}