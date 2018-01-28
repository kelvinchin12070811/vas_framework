#include "Boolean.hpp"

namespace vas
{
	Boolean::Boolean()
	{
	}

	Boolean::Boolean(bool state):
		value(state)
	{
	}

	Boolean::Boolean(const Boolean & rhs):
		value(rhs.value)
	{
	}

	bool Boolean::operator==(const Boolean & rhs) const
	{
		return this->value == rhs.value;
	}

	bool Boolean::operator==(bool rhs) const
	{
		return this->value == rhs;
	}

	bool Boolean::operator!=(const Boolean & rhs)const
	{
		return this->value != rhs.value;
	}

	bool Boolean::operator!=(bool rhs) const
	{
		return this->value != rhs;
	}

	Boolean & Boolean::operator=(bool rhs)
	{
		this->value = rhs;
		return *this;
	}

	Boolean & Boolean::operator=(const Boolean& rhs)
	{
		this->value = rhs.value;
		return *this;
	}

	Boolean::operator bool&()
	{
		return this->value;
	}

	Boolean::operator const bool&() const
	{
		return this->value;
	}
}