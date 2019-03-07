//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "CommonTools.hpp"
#include "../base/Base.hpp"
#include "../math/Clock.hpp"

namespace vas
{
	CommonTools & CommonTools::getInstance()
	{
		static CommonTools instance;
		return instance;
	}

	int CommonTools::messenger(const std::string & message, CommonTools::MessageType messType, int rtnValue)
	{
		if (loggingFunction != nullptr) loggingFunction(message, messType, rtnValue);
		decltype(messTypeStr)::const_pointer messInfo{ nullptr };
		switch (messType)
		{
		case CommonTools::MessageType::error:
			messInfo = &messTypeStr[0];
			break;
		case CommonTools::MessageType::info:
			messInfo = &messTypeStr[1];
			break;
		case CommonTools::MessageType::log:
			messInfo = &messTypeStr[2];
			break;
		case CommonTools::MessageType::warning:
			messInfo = &messTypeStr[3];
			break;
		}

		if (hasConsole) TextTools::println(outputFormat(consolePrefix, *messInfo, message));
		if (messType != CommonTools::MessageType::log && messType != CommonTools::MessageType::info)
		{
#ifdef VAS_WINDOWS_MODE
			MessageBeep(static_cast<UINT>(messType));
			MessageBox(windowInstance, TextTools::stows(message).c_str(),
				TextTools::stows(Base::getInstance().getWindow().getTitle()).c_str(), static_cast<UINT>(messType));
#else
			SDL_MessageBoxFlags flags;
			if (messType == CommonTools::MessageType::error)
				flags = SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR;
			else if (messType == CommonTools::MessageType::warning)
				flags = SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION;

			SDL_ShowSimpleMessageBox(flags, Base::getInstance().getWindow().getTitle().c_str(), message.c_str(),
				static_cast<SDL_Window*>(windowInstance));
#endif // VAS_WINDOWS_MODE
		}
		return rtnValue;
	}

	int CommonTools::messenger(const std::ostream & message, CommonTools::MessageType messType, int rtnValue)
	{
		return messenger(static_cast<const std::stringstream&>(message).str(), messType, rtnValue);
	}

	int CommonTools::messenger(const boost::format& message, CommonTools::MessageType messType, int rtnValue)
	{
		return messenger(message.str(), messType, rtnValue);
	}

	void CommonTools::setConsolePrefix(const std::string & value)
	{
		setConsolePrefix([=]() { return value; });
	}

	void CommonTools::setConsolePrefix(std::function<std::string()> value)
	{
		consolePrefix = std::move(value);
	}

	std::function<std::string()> CommonTools::getConsolePrefix()
	{
		return consolePrefix;
	}

	std::function<void(const std::string&, CommonTools::MessageType, int)>& CommonTools::Loggingfunction()
	{
		return loggingFunction;
	}

	void CommonTools::setConsoleOutputFormat(std::function<std::string(std::function<std::string()>&, const std::string&, const std::string&)> value)
	{
		outputFormat = std::move(value);
	}

	void CommonTools::setMessTypeStr(std::array<std::string, 4> value)
	{
		messTypeStr = std::move(value);
	}

	CommonTools::CommonTools()
	{
		consolePrefix = []() { return Clock::getCurrentISO8601Time(); };
		outputFormat = [](auto& _1, auto& _2, auto& _3) { return _1() + "[" + _2 + "]: " + _3; };
	}

	CommonTools::~CommonTools()
	{
	}

	Log & Log::operator<<(std::ostream &(*manipulator)(std::ostream &o))
	{
		ss << manipulator;
		return *this;
	}

	Err & Err::operator<<(std::ostream &(*manipulator)(std::ostream &o))
	{
		ss << manipulator;
		return *this;
	}

	Info & Info::operator<<(std::ostream &(*manipulator)(std::ostream &o))
	{
		ss << manipulator;
		return *this;
	}

	Warn & Warn::operator<<(std::ostream &(*manipulator)(std::ostream &o))
	{
		ss << manipulator;
		return *this;
	}
}