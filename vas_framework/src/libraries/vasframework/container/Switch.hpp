#pragma once
#include "../VASConfig.hpp"

#define on true
#define off false

namespace vas
{
	using SwitchState = bool;
	class VAS_DECLSPEC Switch
	{
	public:
		Switch();
		explicit Switch(SwitchState state);
		~Switch();

		void setState(SwitchState value);

		bool is(SwitchState state) const;
		bool not(SwitchState state) const;

		explicit operator bool() const;

		Switch& operator()(SwitchState newState);
	private:
		SwitchState value = false;
	};
}