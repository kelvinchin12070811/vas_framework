//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <algorithm>
#include <chrono>
#include "AnimateAble.hpp"
#include "AttrWrap.hpp"
#include "../../VASConfig.hpp"

namespace vas
{
	/**
	 * @ingroup animate
	 * @{
	 */
	/**
	 * @brief The keyframeable animation of an object's attributes.
	 * 
	 * The AttrKeyframeAnimation add animation to an object's attribute. The keyframe will operate in linear mode only which
	 * increase by x overtime.
	 * 
	 * @note The object's attribute must be an interger type in order the keyframe work.
	 */
	class VAS_DECLSPEC AttrKeyframeAnimation : public AnimateAble
	{ /** @} */
	public:
		//AttrKeyframeAnimation(std::function<void(double)> mutator, std::function<double()> accessor);
		/**
		 * Create animation from object's attribute.
		 * @param[in] mutator Function pointer to the function that call the mutator of the targeted object. The function must accept
		 * a incomming value which represented as the current value computed. The data type of it must be double.
		 */
		AttrKeyframeAnimation(std::function<void(double)> mutator);
		/** Create animation from object's attribute.
			 @param[in] mutator Function pointer to the function that call the mutator of the targeted object.
			 The function must accept a incomming value which represented as the current value computed.
			 The data type of it must be double.
			 @param[in] startVal Starting value of keyframe.
			 @param[in] stopVal Stop value of the keyframe.
			 @param[in] duration Duration of the animation.
		*/
		AttrKeyframeAnimation(std::function<void(double)> mutator, double startVal, double stopVal, std::chrono::nanoseconds duration);

		void setDuration(std::chrono::nanoseconds value);
		std::chrono::nanoseconds getDuration() const;

		void setStartValue(double value);
		double getStartValue() const;

		void setStopValue(double value);
		double getStopValue() const;

		void tick() override;

	private:
		double curVal{ 0.0 };
		/**
		 * Starting value of keyframe.
		 * ####Mutators
		 * -# void setStartValue(double value)
		 *
		 * ####Accessors
		 * -# double getStartValue() const
		 */
		double startValue{ 0 };
		/**
		 * Stop value of the keyframe.
		 * ####Mutators
		 * -# void setStopValue(double value)
		 *
		 * ####Accessors
		 * -# double getStopValue() const
		 */
		double stopValue{ 0 };
		/**
		 * Duration of the animation.
		 * ####Mutators
		 * -# void setDuration(std::chrono::nanoseconds value)
		 *
		 * ####Accessors
		 * -# std::chrono::nanoseconds getDuration() const
		 */
		std::chrono::nanoseconds duration;
		std::chrono::steady_clock::time_point lastTick;
		std::function<void(double value)> mutator;
		//std::function<double()> accessor;
	};
}