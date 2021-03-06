//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "AttrKeyframeAnimation.hpp"

namespace vas
{
	/*AttrKeyframeAnimation::AttrKeyframeAnimation(std::function<void(double)> mutator, std::function<double()> accessor) :
		mutator(mutator), accessor(accessor)
	{
	}*/

	AttrKeyframeAnimation::AttrKeyframeAnimation(std::function<void(double)> mutator):
		mutator(mutator)
	{
	}

	AttrKeyframeAnimation::AttrKeyframeAnimation(std::function<void(double)> mutator, double startVal, double stopVal, std::chrono::nanoseconds duration):
		mutator(mutator), startValue(startVal), stopValue(stopVal), duration(duration)
	{
	}

	void AttrKeyframeAnimation::setDuration(std::chrono::nanoseconds value)
	{
		duration = value;
	}

	std::chrono::nanoseconds AttrKeyframeAnimation::getDuration() const
	{
		return duration;
	}

	void AttrKeyframeAnimation::setStartValue(double value)
	{
		startValue = value;
	}

	double AttrKeyframeAnimation::getStartValue() const
	{
		return startValue;
	}

	void AttrKeyframeAnimation::setStopValue(double value)
	{
		stopValue = value;
	}

	double AttrKeyframeAnimation::getStopValue() const
	{
		return stopValue;
	}

	void AttrKeyframeAnimation::tick()
	{
		//restart if finished last time
		if (finished)
		{
			finished = false;
			curVal = startValue;
			lastTick = std::chrono::steady_clock::time_point{};
		}
		std::chrono::nanoseconds diff(0);
		//check if it is first start
		if (lastTick.time_since_epoch() == std::chrono::nanoseconds::zero())
		{
			lastTick = std::chrono::steady_clock::now();
			if (curVal != startValue)
				curVal = startValue;
		}
		else
		{
			diff = std::chrono::steady_clock::now() - lastTick;
		}

		if (duration != duration.zero())
		{
			double deltaValue{ stopValue - startValue };
			double rate{ (static_cast<double>(diff.count()) / static_cast<double>(duration.count())) * deltaValue };
			curVal = deltaValue >= 0 ?
				std::clamp(curVal + rate, startValue, stopValue) :
				std::clamp(curVal + rate, stopValue, startValue);
		}
		else
		{
			curVal = stopValue;
		}
		if (curVal == stopValue)
			this->finished = true;

		mutator(curVal);
		lastTick = std::chrono::steady_clock::now();
	}
}