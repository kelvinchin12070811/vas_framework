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
		sdl::Window windowInstance{ nullptr };
#endif //VAS_WINDOWS_MODE
	private:
		CommonTools();
		~CommonTools();

		std::string assistanceName = "Debug";
		std::function<void(const std::string&, CommonTools::MessageType, int)> loggingFunction = nullptr;
	};

	const class vasout_t
	{
	public:
		void operator=(std::ostream& rhs) const;
	} vasout_base = {};

	const class vasinfo_t
	{
	public:
		void operator=(std::ostream& rhs) const;
	} vasinfo_base = {};

	const class vaserr_t
	{
	public:
		void operator=(std::ostream& rhs) const;
	} vaserr_base = {};
}
#define vasout vas::vasout_base = vasstream
#define vasinfo vas::vasinfo_base = vasstream
#define vaserr vas::vaserr_base = vasstream