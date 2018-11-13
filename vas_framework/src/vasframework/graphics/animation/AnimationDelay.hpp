#pragma once
#include <chrono>
#include "AnimateAble.hpp"
#include "../../VASConfig.hpp"

namespace vas
{
	/** @addtogroup animate
		  @{
	*/
	/** @brief Delay the execution of the AnimationControllerEx.
		  
		  The AnimationDelay is an animation that add a pause between the execution of animations in time.
	*/
	class VAS_DECLSPEC AnimationDelay : public AnimateAble
	{ /** @} */
	public:
		AnimationDelay(); /**< Create empty animation, no delay. */
		/** Create an animation with delay of @p duration.
			  @param duration Duration that the pause added.
		*/
		explicit AnimationDelay(std::chrono::nanoseconds duration);
		~AnimationDelay();

		void tick() override;

	public: //mutators
		void setDuration(std::chrono::nanoseconds value);
		
	public: //accessors
		std::chrono::nanoseconds getDuration() const;
	private:
		bool finished{ false };
		/** [Read & Write] Duration that pause added.\n
				- __mutators__
					-# void setDuration(std::chrono::nanoseconds value)
				- __accessors__
					-# std::chrono::nanoseconds getDuration() const
		*/
		std::chrono::nanoseconds duration;
		std::chrono::steady_clock::time_point startTime;
	};
}