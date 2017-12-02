#include "Timer.hpp"

namespace vas
{
	Timer::Timer()
	{
	}

	Timer::Timer(uint32_t tick, bool continues) : tickLimit(tick), continues(continues)
	{
	}


	Timer::~Timer()
	{
	}

	void Timer::tick()
	{
		if (!counting) return;
		tickCount++;
		if (tickCount == tickLimit - 1)
		{
			timedOut = true;
		}
		else if (tickCount >= tickLimit)
		{
			tickCount = 0;
			timedOut = false;
			if (!continues && !firstCount)
				counting = false;
		}
		if (firstCount) firstCount = false;
	}

	void Timer::start()
	{
		if (counting) return;
		counting = true;
		firstCount = true;
	}

	void Timer::stop()
	{
		if (counting) return;
		counting = false;
		firstCount = false;
	}

	void Timer::reset()
	{
		if (counting) return;
		if (tickCount != tickLimit) tickCount = tickLimit;
	}

	void Timer::reset(uint32_t tick, bool continues)
	{
		if (counting) return;
		timedOut = false;
		this->continues = continues;
		tickCount = tick;
		tickLimit = tick;
	}

	bool Timer::isTimedOut()
	{
		return timedOut;
	}

	uint32_t Timer::getTick()
	{
		return tickCount >= tickLimit ? 0 : tickCount;
	}
}