#pragma once
#include <algorithm>
#include <chrono>
#include <functional>
#include "AnimateAble.hpp"
#include "../../VASConfig.hpp"

namespace vas
{
	class VAS_DECLSPEC AttrKeyframeAnimation : public AnimateAble
	{
	public:
		//AttrKeyframeAnimation(std::function<void(double)> mutator, std::function<double()> accessor);
		AttrKeyframeAnimation(std::function<void(double)> mutator);

		void setDuration(std::chrono::nanoseconds value);
		std::chrono::nanoseconds getDuration() const;

		void setStartValue(double value);
		double getStartValue() const;

		void setStopValue(double value);
		double getStopValue() const;

		void tick() override;
		bool done() const override;

	private:
		bool finished{ false };
		double curVal{ 0.0 };
		double startValue{ 0 };
		double stopValue{ 0 };
		std::chrono::nanoseconds duration;
		std::chrono::steady_clock::time_point lastTick;
		std::function<void(double value)> mutator;
		//std::function<double()> accessor;
	};
}