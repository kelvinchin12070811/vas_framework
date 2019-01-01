//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
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
	/** @addtogroup util
		  @{
	*/
	/** @brief Common tools that might help at input and output.

		  The CommonTools contain tools for console input, output and also message boxes.

		  ## Helper stream
		  The helper stream is a class that designed to output the message more eiser. Most of them have std::cout like
		  interface (using operator<< on a temporary instance). The helper stream will output them once it get destroyed.
		
		- vas::Log\n
			Log the message. MessageType::log
		- vas::Info\n
			Info the user. MessageType::info
		- vas::Warn\n
			Warn the user. MessageType::warning
		- vas::Err\n
			Promp the user with error message. MessageType::error

		@note The helper stream call messenger to output message therefore std::endl does not required.
	*/
	class VAS_DECLSPEC CommonTools
	{ /** @} */
	public:
		/** Type of message, also determine it will promp with message box or not.
		*/
		enum class MessageType : long
		{
			log = -1, /**< Log, output the message only. Default type of output. (-1) */
			info, /**< Info, ouptut and tell the user something in console only, message box not promped. (0) */
			warning = 0x00000040L, /**< Warning, promp the user with information icon and output it to console. (0x00000040L) */
			error = 0x00000010L /**< Critical error, promp the user with error icon and output it to console. (0x00000010L) */
		};
		static CommonTools& getInstance(); /**< Get the singletone instance of the CommonTools. */

		bool hasConsole{ false };

		/** Output message to console, promp user if the condition is true.
			  @param message Message to output.
			  @param messType Type of the message to output.
			  @param rtnValue Return value of the function.
			  @return Value of @p rtnValue.
		*/
		int messenger(
			const std::string& message,
			CommonTools::MessageType messType = CommonTools::MessageType::log,
			int rtnValue = 0
		);
		
		/** Output message to console, promp user if the condition is true.
			  @param message Stream of message to output.
			  @param messType Type of the message to output.
			  @param rtnValue Return value of the function.
			  @return Value of @p rtnValue.
		*/
		int messenger(
			const std::ostream& message,
			CommonTools::MessageType messType = CommonTools::MessageType::log,
			int rtnValue = 0
		);

		/** Output message to console, promp user if the condition is true.
			  @param message boost::format message to output.
			  @param messType Type of the message to output.
			  @param rtnValue Return value of the function.
			  @return Value of @p rtnValue.
		*/
		int messenger(
			const boost::format& message,
			CommonTools::MessageType messType = CommonTools::MessageType::log,
			int rtnValue = 0
		);

		void setConsolePrefix(const std::string& value);
		std::string getConsolePrefix();

		std::function<void(const std::string&, CommonTools::MessageType, int)>& Loggingfunction();

		void setMessTypeStr(std::array<std::string, 4> value);
#ifdef VAS_WINDOWS_MODE
		HWND windowInstance = nullptr;
#else
		sdl::Window windowInstance;
#endif //VAS_WINDOWS_MODE
	private:
		CommonTools();
		~CommonTools();

		/** [Read & Write] Prefix of the console output. Timestamp will be outputed if empty.

			- __mutators__
				-# void setConsolePrefix(const std::string& value)
			- __accessors__
				-# std::string getConsolePrefix()
		*/
		std::string consolePrefix = "";
		/** [Read & Write] Logger function of messenger. use to handle additional task.
			
			- __mutaors & accessors__
				-# std::function<void(const std::string&, CommonTools::MessageType, int)>& Loggingfunction()
		*/
		std::function<void(const std::string&, CommonTools::MessageType, int)> loggingFunction = nullptr;
		/** [Write Only] Stringnified message type name.
			  
			  - __mutators__
				-# void setMessTypeStr(std::array<std::string, 4> value)
		*/
		std::array<std::string, 4> messTypeStr{ "ERROR", "INFO", "LOG", "WARN" };
	};

	/* @addtogroup util
		  @{
	*/
	/* @brief Output to console with stream and CommonTools::MessageType::log type.
		  
		  The Log class is a std::cout like stream that output message to consome via CommonTools::messenger() with
		  CommonTools::MessageType::log type.

		  example usage:
			```cpp
			vas::Log() << "message to output";	// std::endl not required, the line ended when the instance destroy.	  
			```
	*/
	class Log
	{ /* @} */
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

	class Warn
	{
	public:
		Warn() = default;
		~Warn()
		{
			vas::CommonTools::getInstance().messenger(ss, vas::CommonTools::MessageType::warning);
		}
		template<typename Type>
		Warn& operator<<(const Type& rhs)
		{
			ss << rhs;
			return *this;
		}
		Warn& operator<<(std::ostream& (*manipulator)(std::ostream& o));
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