#pragma once
#include <string>
#include <functional>
#include <boost/format.hpp>
#include <boost/any.hpp>
#include "../sdlcore/Video.hpp"
#include "TextTools.hpp"

#ifdef VAS_WINDOWS_MODE
#include <Windows.h>
#else
#include <SDL.h>
#endif // VAS_WINDOWS_MODE

//#define vasout vassstream

namespace vas
{
	class CommonTools
	{
	public:
		enum class MessageType : long
		{
			log = -1,
			info,
			warning = 0x00000040L,
			error = 0x00000010L
		};
		static CommonTools& getInstance();

		bool hasConsole{ false };

		int messenger(
			const std::string& message,
			CommonTools::MessageType messType = CommonTools::MessageType::log,
			int rtnValue = 0
		);

		int messenger(
			const std::ostream& message,
			CommonTools::MessageType messType = CommonTools::MessageType::log,
			int rtnValue = 0
		);

		int messenger(
			const boost::format& message,
			CommonTools::MessageType messType = CommonTools::MessageType::log,
			int rtnValue = 0
		);

		void setAssistanceName(const std::string& value);
		std::string getAssistanceName();

		std::function<void(const std::string&, CommonTools::MessageType, int)>& Loggingfunction();
#ifdef VAS_WINDOWS_MODE
		HWND windowInstance = nullptr;
#else
		sdl::Window windowInstance;
#endif //VAS_WINDOWS_MODE
	private:
		CommonTools();
		~CommonTools();

		std::string assistanceName = "Debug";
		std::function<void(const std::string&, CommonTools::MessageType, int)> loggingFunction = nullptr;
	};

	class Log
	{
	public:
		Log() = default;
		~Log()
		{
			vas::CommonTools::getInstance().messenger(ss);
		}
		template<typename Type>
		Log& operator<<(const Type& rhs)
		{
			ss << rhs;
			return *this;
		}
		Log& operator<<(std::ostream& (*manipulator)(std::ostream& o));
	private:
		std::stringstream ss;
	};

	class Info
	{
	public:
		Info() = default;
		~Info()
		{
			vas::CommonTools::getInstance().messenger(ss, vas::CommonTools::MessageType::info);
		}
		template<typename Type>
		Info& operator<<(const Type& rhs)
		{
			ss << rhs;
			return *this;
		}
		Info& operator<<(std::ostream& (*manipulator)(std::ostream& o));
	private:
		std::stringstream ss;
	};

	class Err
	{
	public:
		Err() = default;
		~Err()
		{
			vas::CommonTools::getInstance().messenger(ss, vas::CommonTools::MessageType::error);
		}
		template<typename Type>
		Err& operator<<(const Type& rhs)
		{
			ss << rhs;
			return *this;
		}
		Err& operator<<(std::ostream& (*manipulator)(std::ostream& o));
	private:
		std::stringstream ss;
	};
}