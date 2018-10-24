#pragma once
#include <chrono>
#include <string>
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
		using DurationType = std::chrono::nanoseconds; /**< Duration type use by Clock. */
		enum class TimeType : uint8_t {
			local,
			utc
		};
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

		static time_t getCurrentUnixTime();
		static std::tm getCurrentCalenderDateTime(TimeType tmType = TimeType::utc);
		static std::string getCurrentISO8601Time(TimeType tmType = TimeType::utc, bool withSeperator = true);

		static time_t tmToTime_t(const std::tm& tm, TimeType srcType = TimeType::utc);
		static std::tm time_tToTm(const time_t& time, TimeType desType = TimeType::utc);
		static std::string tmToISO8601(const std::tm& tm, bool seperator = true, TimeType srcType = TimeType::utc);
		static std::tm ISO8601ToTm(const std::string& iso8601Time, TimeType desType = TimeType::utc);

		static time_t getTimezoneOffset();
		static std::tm UTCToLocal(const std::tm& input);
		static std::tm LocalToUTC(const std::tm& input);
		static TimeType ISO8601TimeType(std::string_view time);
	private:
		std::chrono::steady_clock::time_point startTime;
	};
}