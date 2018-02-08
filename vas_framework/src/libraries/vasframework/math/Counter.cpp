#include "Counter.hpp"

namespace vas
{
	Counter::Counter()
	{
	}

	Counter::Counter(size_t autoResetLimit):
		autoResetLimit(autoResetLimit)
	{
	}

	Counter::~Counter()
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