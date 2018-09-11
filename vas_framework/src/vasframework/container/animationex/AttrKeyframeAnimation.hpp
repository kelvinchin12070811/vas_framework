#pragma once
#include <algorithm>
#include <chrono>
#include <functional>
#include "Animateable.hpp"
#include "../../VASConfig.hpp"

namespace vas
{
	template <typename NumericType>
	class AttrKeyframeAnimation : public Animateable
	{
	public:
		template <typename Instance, typename Mutator, typename Accessor>
		AttrKeyframeAnimation(const Instance& instance, Mutator mutator, Accessor accessor)
		{
			this->mutator = std::bind(mutator, instance, std::placeholders::_1);
			this->accessor = std::bind(accessor, instance);
		}

		void setDuration(std::chrono::nanoseconds value)
		{
			duration = value;
		}

		std::chrono::nanoseconds getDuration() const
		{
			return duration;
		}

		void setStartValue(NumericType value)
		{
			startValue = value;
		}

		NumericType getStartValue() const
		{
			return startValue;
		}

		void setStopValue(NumericType value)
		{
			stopValue = value;
		}

		NumericType getStopValue() const
		{
			return stopValue;
		}

		void tick() override
		{
			//restart if finished last time
			if (finished) finished = false;
			auto curValue = accessor();
			std::chrono::nanoseconds diff;
			//check if it is first start
			if (lastTick.time_since_epoch() == std::chrono::nanoseconds::zero())
			{
				lastTick = std::chrono::steady_clock::now();
				if (curValue != startValue)
					curValue = startValue;
			}
			else
			{
				diff = lastTick - std::chrono::steady_clock::now();
			}

			if (duration != duration.zero())
			{
				NumericType deltaValue = stopValue - startValue;
				NumericType rate = static_cast<NumericType>((diff / duration)) * deltaValue;
				curValue = deltaValue >= 0 ?
					std::clamp(curValue + rate, startValue, stopValue) :
					std::clamp(curValue + rate, stopValue, startValue);
			}
			else
			{
				curValue = stopValue;
			}
			if (curValue == stopValue)
				finished = true;

			mutator(curValue);
			lastTick = std::chrono::steady_clock::now();
		}

		bool done() const override
		{
			return finished;
		}
	private:
		bool finished{ false };
		NumericType startValue{ 0 };
		NumericType stopValue{ 0 };
		std::chrono::nanoseconds duration;
		std::chrono::steady_clock::time_point lastTick;
		std::function<void(NumericType value)> mutator;
		std::function<NumericType()> accessor;
	};
}