#include "Switch.hpp"

namespace vas
{
	Switch::Switch()
	{
	}

	Switch::Switch(SwitchState state) :
		value(state)
	{
	}


	Switch::~Switch()
	{
	}

	void Switch::setState(SwitchState value)
	{
		this->value = value;
	}

	bool Switch::is(SwitchState state) const
	{
		return value == state;
	}

	bool Switch::not(SwitchState state) const
	{
		return value != state;
	}

	Switch::operator bool() const
	{
		return value;
	}

	Switch & Switch::operator()(SwitchState newState)
	{
		setState(newState);
		return *this;
	}
}