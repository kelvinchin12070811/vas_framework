#include <ctime>
#include <sstream>
#include <iomanip>
#include "Clock.hpp"

namespace vas
{
	Clock::Clock():
		startTime(std::chrono::steady_clock::now())
	{
	}

	std::chrono::nanoseconds Clock::reset()
	{
		auto prev = startTime;
		startTime = std::chrono::steady_clock::now();
		return startTime - prev;
	}

	void Clock::justReset()
	{
		startTime = std::chrono::steady_clock::now();
	}

	std::chrono::nanoseconds Clock::currentTick()
	{
		auto currentTick = std::chrono::steady_clock::now();
		return currentTick - startTime;
	}

	time_t Clock::getCurrentUnixTime()
	{
		auto resultTm = std::chrono::system_clock::now();
		return std::chrono::system_clock::to_time_t(resultTm);
	}

	std::tm Clock::getCurrentCalenderDateTime(Clock::Timezone zone)
	{
		time_t crTime = getCurrentUnixTime();
		std::tm tmTime{ 0 };
		switch (zone)
		{
		case vas::Clock::Timezone::local:
			localtime_s(&tmTime, &crTime);
			break;
		case vas::Clock::Timezone::utc:
			gmtime_s(&tmTime, &crTime);
			break;
		}
		return tmTime;
	}

	std::string Clock::getCurrentISO8601Time(Clock::Timezone zone, bool withSeperator)
	{
		std::tm tmTime = getCurrentCalenderDateTime(zone);
		return tmToISO8601(tmTime, withSeperator, zone);
	}

	time_t Clock::tmToTime_t(const std::tm & tm, Clock::Timezone srcZone)
	{
		auto tmCl = tm;
		time_t result = std::mktime(&tmCl);
		return srcZone == Timezone::utc ? result + getTimezoneOffset() : result;
	}

	std::tm Clock::time_tToTm(const time_t & time, Clock::Timezone desZone)
	{
		std::tm tm;
		switch (desZone)
		{
		case vas::Clock::Timezone::local:
			localtime_s(&tm, &time);
			break;
		case vas::Clock::Timezone::utc:
			gmtime_s(&tm, &time);
			break;
		}
		return tm;
	}

	std::string Clock::tmToISO8601(const std::tm & tm, bool seperator, Clock::Timezone srcZone)
	{
		std::ostringstream timeMaker;

		if (seperator)
			timeMaker << std::put_time(&tm, "%Y-%m-%dT%H:%M:%S");
		else
			timeMaker << std::put_time(&tm, "%Y%m%dT%H%M%S");

		if (srcZone == Timezone::utc)
			timeMaker << "Z";

		return timeMaker.str();
	}

	std::tm Clock::ISO8601ToTm(const std::string & iso8601Time, Clock::Timezone desZone)
	{
		std::string timeStr{ iso8601Time };
		bool withSeperator{ timeStr.find('-') != std::string::npos };
		bool isUTC{ ISO8601Timezone(timeStr) == Timezone::utc };
		std::tm tm;

		if (!withSeperator) //Convert to with seperator if no seperator
		{
			std::ostringstream buffer;
			
			for (size_t loop{ 0 }; loop < timeStr.length(); loop++)
			{
				buffer << timeStr[loop];
				if (loop == 3 || loop == 5)
					buffer << "-";
				else if (loop == 10 || loop == 12)
					buffer << ":";
			}

			timeStr = buffer.str();
		}

		std::istringstream timeMaker{ timeStr };
		timeMaker >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S");

		if (isUTC && desZone == Timezone::local)
			tm = UTCToLocal(tm);

		return tm;
	}

	time_t Clock::getTimezoneOffset()
	{
		time_t utc = 1234567890;
		std::tm zone_conv{ 0 };

		gmtime_s(&zone_conv, &utc);
		return utc - mktime(&zone_conv);
	}

	std::tm Clock::UTCToLocal(const std::tm & input)
	{
		time_t buffer{ tmToTime_t(input, Timezone::utc) };
		return time_tToTm(buffer, Timezone::local);
	}

	std::tm Clock::LocalToUTC(const std::tm & input)
	{
		time_t buffer{ tmToTime_t(input, Timezone::local) };
		return time_tToTm(buffer, Timezone::utc);
	}

	Clock::Timezone Clock::ISO8601Timezone(std::string_view time)
	{
		auto result = time.rfind('Z');
		return result == std::string_view::npos ? Timezone::local : Timezone::utc;
	}
}