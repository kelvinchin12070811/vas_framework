#pragma once
#include "../VASConfig.hpp"

#define VAS_SWITCH_USE_STATE_CLASS

namespace vas
{
	using SwitchState = bool;

	inline namespace switch_state
	{
#ifndef VAS_SWITCH_USE_STATE_CLASS
		const SwitchState on = true;
		const SwitchState off = false;
#else
		//Switch State: ON
		const class SwitchStateOn_t
		{
		public:
			operator bool() const
			{
				return true;
			}
		} on = {};

		//Switch State: OFF
		const class SwitchStateOff_t
		{
		public:
			operator bool() const
			{
				return false;
			}
		} off = {};
#endif // !VAS_SWITCH_USE_STATE_CLASS
	}

	class VAS_DECLSPEC Switch
	{
	public:
		Switch();
#ifndef VAS_SWITCH_USE_STATE_CLASS
		explicit Switch(SwitchState state);

		void setState(SwitchState value);
		bool is(SwitchState state) const;
		bool not(SwitchState state) const;

		Switch& operator()(SwitchState newState);
#else
		explicit Switch(switch_state::SwitchStateOn_t);
		explicit Switch(switch_state::SwitchStateOff_t);

		void setState(switch_state::SwitchStateOn_t);
		void setState(switch_state::SwitchStateOff_t);

		bool is(switch_state::SwitchStateOn_t) const;
		bool is(switch_state::SwitchStateOff_t) const;

		bool not(switch_state::SwitchStateOn_t) const;
		bool not(switch_state::SwitchStateOff_t) const;

		Switch& operator()(switch_state::SwitchStateOn_t);
		Switch& operator()(switch_state::SwitchStateOff_t);
#endif // !VAS_SWITCH_USE_STATE_CLASS
		~Switch();

		//Flip the switch and return the current state
		bool flip();

		explicit operator bool() const;
	private:
		SwitchState value = off;
	};
}