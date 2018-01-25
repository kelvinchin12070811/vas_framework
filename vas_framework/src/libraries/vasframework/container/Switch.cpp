#include "Switch.hpp"

namespace vas
{
	Switch::Switch()
	{
	}

	Switch::Switch(bool state) :
		value(state)
	{
	}


	Switch::~Switch()
	{
	}

	Switch::operator bool() const
	{
		return value;
	}

	Switch::operator std::string() const
	{
		return value ? "on" : "false";
	}

	bool Switch::operator==(const Switch & rhs) const
	{
		return this->value == rhs.value;
	}

	bool Switch::operator==(bool rhs) const
	{
		return this->value == rhs;
	}

	bool Switch::operator!=(const Switch & rhs) const
	{
		return this->value != rhs.value;
	}

	bool Switch::operator!=(bool rhs) const
	{
		return this->value != rhs;
	}

}