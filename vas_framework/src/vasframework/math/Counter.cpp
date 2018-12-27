#include "Counter.hpp"

namespace vas
{
	Counter::Counter(size_t autoResetLimit):
		autoResetLimit(autoResetLimit)
	{
	}

	void Counter::setAutoResetLimit(size_t autoResetLimit)
	{
		this->autoResetLimit = autoResetLimit;
	}

	void Counter::reset()
	{
		ticks = 0;
	}

	size_t Counter::getMaxTick() const
	{
		return getLimit() - 1;
	}

	size_t Counter::getLimit() const
	{
		return autoResetLimit;
	}

	Counter & Counter::operator++(int)
	{
		ticks++;
		if (ticks == autoResetLimit)
			ticks = 0;
		return *this;
	}

	Counter & Counter::operator--(int)
	{
		if (ticks != 0)
			ticks--;
		else
			ticks = autoResetLimit--;
		return *this;
	}

	bool Counter::operator==(const Counter & rhs)
	{
		return ticks == rhs.ticks;
	}

	bool Counter::operator==(const size_t & rhs)
	{
		return ticks == rhs;
	}

	Counter::operator size_t&()
	{
		return ticks;
	}

	Counter::operator const size_t&() const
	{
		return ticks;
	}
}