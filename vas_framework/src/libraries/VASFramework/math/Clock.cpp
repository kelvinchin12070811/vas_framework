#include "Clock.hpp"

namespace vas
{
	Clock::Clock():
		lastTicks(SDL_GetTicks())
	{
	}

	Clock::Clock(const Clock & rhs):
		lastTicks(rhs.lastTicks)
	{
	}


	Clock::~Clock()
	{
	}

	uint32_t Clock::getTicks()
	{
		return SDL_GetTicks() - lastTicks;
	}

	uint32_t Clock::reset()
	{
		uint32_t ticksOver = SDL_GetTicks() - lastTicks;
		lastTicks = SDL_GetTicks();
		return ticksOver;
	}
}