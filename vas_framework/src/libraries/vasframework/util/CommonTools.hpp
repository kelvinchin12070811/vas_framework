#pragma once
#include <string>
#include <functional>
#include <boost/format.hpp>
#include <boost/any.hpp>
#include "../sdlcore/Video.hpp"

#ifdef VAS_WINDOWS_MODE
#include <Windows.h>
#else
#include <SDL.h>
#endif // VAS_WINDOWS_MODE

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

		int messengerf(
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
		sdl::Window windowInstance{ nullptr };
#endif //VAS_WINDOWS_MODE
	private:
		CommonTools();
		~CommonTools();

		std::string assistanceName = "Debug";
		std::function<void(const std::string&, CommonTools::MessageType, int)> loggingFunction = nullptr;
	};
}