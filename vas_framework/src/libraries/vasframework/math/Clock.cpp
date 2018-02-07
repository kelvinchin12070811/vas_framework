#include "Clock.hpp"

namespace vas
{
	Clock::Clock():
		startTime(std::chrono::steady_clock::now())
	{
	}

	Clock::~Clock()
	{
	}

	std::chrono::nanoseconds Clock::reset()
	{
		auto prev = startTime;
		startTime = std::chrono::steady_clock::now();
		return startTime - prev;
	}

	void Clock::justReset()
	{
		startTime = std::chrono::steady_clock::now();
	}

	std::chrono::nanoseconds Clock::currentTick()
	{
		auto currentTick = std::chrono::steady_clock::now();
		return currentTick - startTime;
	}
}