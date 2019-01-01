//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
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
		/** Timezone of the time, utc +0 or local time. */
		enum class Timezone : uint8_t {
			local, /**< Current system's local time. */
			utc /**< UTC zone +0 time. */
		};
		Clock(); /**< Create and start counting time (first reset). */

		/** Reset the clock and return the currnet elapsed time since last reset.
			  @retval std::chrono::nanoseconds time elapsed in nanoseconds.
		*/
		std::chrono::nanoseconds reset();
		/** Only reset the clock. */
		void justReset();
		/** Get the current time elapsed scine last reset. */
		std::chrono::nanoseconds currentTick();

		/** Get current system time in UNIX time format.
			  @return Ticks in seconds since epoch (1 Jan 1970 00:00 a.m.)
		*/
		static time_t getCurrentUnixTime();
		/** Get current system time in human readable calender format.
			  @param zone Output time timezone.
			  @return std::tm structure of current system time.
		*/
		static std::tm getCurrentCalenderDateTime(Timezone zone = Timezone::utc);
		/** Get current system time in ISO8601 format.
			  @param zone Output time timezone.
			  @param withSeperator Determine if outputed text with seperator.
			  @return ISO8601 formated time.
		*/
		static std::string getCurrentISO8601Time(Timezone zone = Timezone::utc, bool withSeperator = true);

		/** Convert std::tm to time_t.
			  @param tm Input time.
			  @param srcZone Timezone of time inputed.
			  @return @p tm in UNIX time format.
		*/
		static time_t tmToTime_t(const std::tm& tm, Timezone srcZone = Timezone::utc);
		/** Convert time_t to std::tm.
			  @param time Input time.
			  @param desZone Output time timezone.
			  @return std::tm of @p time.
		*/
		static std::tm time_tToTm(const time_t& time, Timezone desZone = Timezone::utc);
		/** Convert std::tm to ISO8601 formated text.
			  @param tm Input time.
			  @param seperator Determine if outputed text with seperator.
			  @param srcZone Timezone of time inputed.
			  @return ISO8601 formated time of @p tm
		*/
		static std::string tmToISO8601(const std::tm& tm, bool seperator = true, Timezone srcZone = Timezone::utc);
		/** Convert ISO8601 formated time to std::tm.
			  @param iso8601Time Input time, ISO8601 formated.
			  @param desZone Output time timezone.
		*/
		static std::tm ISO8601ToTm(const std::string& iso8601Time, Timezone desZone = Timezone::utc);

		/** Get the offset of current local time from utc zero time in seconds. */
		static time_t getTimezoneOffset();
		/** Convert utc zero time to local time. */
		static std::tm UTCToLocal(const std::tm& input);
		/** Convert local time to utc zero time. */
		static std::tm LocalToUTC(const std::tm& input);
		/** Get the timezone of an ISO8601 formated time. */
		static Timezone ISO8601Timezone(std::string_view time);
	private:
		std::chrono::steady_clock::time_point startTime;
	};
}