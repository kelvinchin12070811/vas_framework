//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <chrono>
#include "AnimateAble.hpp"
#include "../../VASConfig.hpp"

namespace vas
{
	/**
	 * @ingroup animate
	 * @{
	 */
	/**
	 * @brief Delay the execution of the AnimationControllerEx.
	 * 
	 * The AnimationDelay is an animation that add a pause between the execution of animations in time.
	 */
	class VAS_DECLSPEC AnimationDelay : public AnimateAble
	{ /** @} */
	public:
		AnimationDelay() = default; /**< Create empty animation, no delay. */
		/**
		 * Create an animation with delay of @p duration.
		 * @param[in] duration Duration that the pause added.
		 */
		explicit AnimationDelay(std::chrono::nanoseconds duration);

		void tick() override;

	public: //mutators
		void setDuration(std::chrono::nanoseconds value);
		
	public: //accessors
		std::chrono::nanoseconds getDuration() const;
	private:
		/**
		 * Duration that pause added.
		 * ####Mutators
		 * -# void setDuration(std::chrono::nanoseconds value)
		 *
		 * ####Accessors
		 * -# std::chrono::nanoseconds getDuration() const
		 */
		std::chrono::nanoseconds duration;
		std::chrono::steady_clock::time_point startTime;
	};
}