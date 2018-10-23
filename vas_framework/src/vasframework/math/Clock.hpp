#pragma once
#include <chrono>
#include "../VASConfig.hpp"

namespace vas
{
	/** @addtogroup @math
		  @{
	*/
	/** @brief The object that tell you what time is now.
		  
		  Clock is a utility that tell you current the time of the computer in ticks.
	*/
	class VAS_DECLSPEC Clock
	{ /** @} */
	public:
		using DurationType = std::chrono::nanoseconds;
		Clock();
		~Clock();

		/** Reset the clock and return the currnet elapsed time since last reset.
			  @retval std::chrono::nanoseconds time elapsed in nanoseconds.
		*/
		std::chrono::nanoseconds reset();
		/** Only reset the clock. */
		void justReset();
		/** Get the current time elapsed scine last reset. */
		std::chrono::nanoseconds currentTick();
	private:
		std::chrono::steady_clock::time_point startTime;
	};
}