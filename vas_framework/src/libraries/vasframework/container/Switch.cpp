#include "Switch.hpp"

namespace vas
{
	Switch::Switch()
	{
	}

#ifndef VAS_SWITCH_USE_STATE_CLASS
	Switch::Switch(SwitchState state) :
		value(state)
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

	Switch & Switch::operator()(SwitchState newState)
	{
		setState(newState);
		return *this;
	}
#else
	Switch::Switch(switch_state::SwitchStateOn_t):
		value(switch_state::on)
	{
	}

	Switch::Switch(switch_state::SwitchStateOff_t):
		value(switch_state::off)
	{
	}

	void Switch::setState(switch_state::SwitchStateOn_t)
	{
		value = switch_state::on;
	}

	void Switch::setState(switch_state::SwitchStateOff_t)
	{
		value = switch_state::off;
	}

	bool Switch::is(switch_state::SwitchStateOn_t) const
	{
		return value == switch_state::on;
	}

	bool Switch::is(switch_state::SwitchStateOff_t) const
	{
		return value == switch_state::off;
	}

	bool Switch::not(switch_state::SwitchStateOn_t) const
	{
		return value != switch_state::on;
	}

	bool Switch::not(switch_state::SwitchStateOff_t) const
	{
		return value != switch_state::off;
	}

	Switch & Switch::operator()(switch_state::SwitchStateOn_t)
	{
		value = switch_state::on;
		return *this;
	}

	Switch & Switch::operator()(switch_state::SwitchStateOff_t)
	{
		value = switch_state::off;
		return *this;
	}
#endif // !VAS_SWITCH_USE_STATE_CLASS

	Switch::~Switch()
	{
	}

	bool Switch::flip()
	{
		if (value == switch_state::on)
			value = switch_state::off;
		else
			value = switch_state::on;
		return value;
	}

	Switch::operator bool() const
	{
		return value;
	}
}