#include <ctime>
#include <sstream>
#include <iomanip>
#include <map>
#include "Clock.hpp"

namespace vas
{
	Clock::Clock():
		startTime(std::chrono::steady_clock::now())
	{
	}

	Clock::~Clock()
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

	std::tm Clock::getCurrentCalenderDateTime(TimeType tmType)
	{
		time_t crTime = getCurrentUnixTime();
		//std::tm tmTime = tmType == Clock::TimeType::utc ? *std::gmtime(&crTime) : *std::localtime(&crTime);
		std::tm tmTime{ 0 };
		switch (tmType)
		{
		case vas::Clock::TimeType::local:
			localtime_s(&tmTime, &crTime);
			break;
		case vas::Clock::TimeType::utc:
			gmtime_s(&tmTime, &crTime);
			break;
		}
		return tmTime;
	}

	std::string Clock::getCurrentISO8601Time(Clock::TimeType tmType, bool withSeperator)
	{
		std::tm tmTime = getCurrentCalenderDateTime(tmType);
		return tmToISO8601(tmTime, withSeperator);
	}

	time_t Clock::tmToTime_t(const std::tm & tm, TimeType srcType)
	{
		auto tmCl = tm;
		time_t result = std::mktime(&tmCl);
		return srcType == TimeType::utc ? result + getTimezoneOffset() : result;
	}

	std::tm Clock::time_tToTm(const time_t & time, TimeType desType)
	{
		std::tm tm;
		switch (desType)
		{
		case vas::Clock::TimeType::local:
			localtime_s(&tm, &time);
			break;
		case vas::Clock::TimeType::utc:
			gmtime_s(&tm, &time);
			break;
		}
		return tm;
	}

	std::string Clock::tmToISO8601(const std::tm & tm, bool seperator, TimeType srcType)
	{
		std::ostringstream timeMaker;

		if (seperator)
			timeMaker << std::put_time(&tm, "%Y-%m-%dT%H:%M:%S");
		else
			timeMaker << std::put_time(&tm, "%Y%m%dT%H%M%S");

		if (srcType == TimeType::utc)
			timeMaker << "Z";

		return timeMaker.str();
	}

	std::tm Clock::ISO8601ToTm(const std::string & iso8601Time, Clock::TimeType desType)
	{
		std::string timeStr = iso8601Time;
		bool withSeperator = timeStr.find('-') != std::string::npos;
		bool isUTC = ISO8601TimeType(timeStr) == TimeType::utc;
		std::tm tm;

		if (!withSeperator) //Convert to with seperator if no seperator
		{
			std::map<float, char> buffer;
			for (auto itr = timeStr.begin(); itr != timeStr.end(); itr++)
				buffer.insert({ static_cast<float>(std::distance(timeStr.begin(), itr)), *itr });

			buffer.insert({ 3.5f, '-' });
			buffer.insert({ 5.5f, '-' });
			buffer.insert({ 10.5f, ':' });
			buffer.insert({ 12.5f, ':' });

			timeStr = "";
			timeStr.reserve(buffer.size());
			for (auto itr = buffer.begin(); itr != buffer.end(); itr++)
				timeStr.push_back(itr->second);
		}

		std::istringstream timeMaker(timeStr);
		timeMaker >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S");

		if (isUTC && desType == TimeType::local)
			tm = UTCToLocal(tm);

		return tm;
	}

	time_t Clock::getTimezoneOffset()
	{
		time_t utc = 1234567890;
		std::tm zone_conv = { 0 };

		gmtime_s(&zone_conv, &utc);
		return utc - mktime(&zone_conv);
	}

	std::tm Clock::UTCToLocal(const std::tm & input)
	{
		time_t buffer = tmToTime_t(input, TimeType::utc);
		return time_tToTm(buffer, TimeType::local);
	}

	std::tm Clock::LocalToUTC(const std::tm & input)
	{
		time_t buffer = tmToTime_t(input, TimeType::local);
		return time_tToTm(buffer, TimeType::utc);
	}

	Clock::TimeType Clock::ISO8601TimeType(std::string_view time)
	{
		auto result = time.rfind('Z');
		return result == std::string_view::npos ? TimeType::local : TimeType::utc;
	}
}