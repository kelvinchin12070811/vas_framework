#pragma once
#include <SDL.h>

namespace vas
{
	class Clock
	{
	public:
		Clock();
		Clock(const Clock& rhs);
		~Clock();

		uint32_t getTicks();
		uint32_t reset();
	private:
		uint32_t lastTicks = 0;
	};
}