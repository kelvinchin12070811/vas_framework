#pragma once
#include <algorithm>
#include <chrono>
#include <functional>
#include "AnimateAble.hpp"
#include "../../VASConfig.hpp"

namespace vas
{
	/** @addtogroup animate
		  @{
	*/
	/** @brief The keyframeable animation of an object's attributes.
		  
		  The AttrKeyframeAnimation add animation to an object's attribute. The keyframe will operate in linear mode only which
		  increase by x overtime.

		  @note The object's attribute must be an interger type in order the keyframe work.
	*/
	class VAS_DECLSPEC AttrKeyframeAnimation : public AnimateAble
	{ /** @} */
	public:
		//AttrKeyframeAnimation(std::function<void(double)> mutator, std::function<double()> accessor);
		/** Create animation from object's attribute.
			  @param mutator Function pointer to the function that call the mutator of the targeted object. The function must accept
					a incomming value which represented as the current value computed. The data type of it must be double.
		*/
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
		/** [Read & Write] Starting value of keyframe.\n
				- __mutators__
					-# void setStartValue(double value)
				- __accessors__
					-# double getStartValue() const
		*/
		double startValue{ 0 };
		/** [Read & Write] Stop value of the keyframe.\n
				- __mutators__
					-# void setStopValue(double value)
				- __accessors__
					-# double getStopValue() const
		*/
		double stopValue{ 0 };
		/** [Read & Write] Duration of the animation.\n
				- __mutators__
					-# void setDuration(std::chrono::nanoseconds value)
				- __accessors__
					-# std::chrono::nanoseconds getDuration() const
		*/
		std::chrono::nanoseconds duration;
		std::chrono::steady_clock::time_point lastTick;
		std::function<void(double value)> mutator;
		//std::function<double()> accessor;
	};
}