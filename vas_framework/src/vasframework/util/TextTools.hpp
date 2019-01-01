//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <boost/format.hpp>

#if !__has_include("../VASConfig.hpp")
#define VAS_TEXTTOOLS_INDIE_MODE
#endif

#ifndef VAS_TEXTTOOLS_INDIE_MODE
#include "../VASConfig.hpp"

#ifndef VAS_GLOB_CONFIG
#error VASConfig.hpp not found. define "VAS_TEXTTOOLS_INDIE_MODE" to make this library works in independent mode.
#endif

#else
#ifdef WIN32
#define VAS_WINDOWS_MODE
#endif

#ifdef VAS_WINDOWS_MODE
#define VAS_DECLSPEC __declspec(dllexport)
#else
#define VAS_DECLSPEC
#endif // VAS_WINDOWS_MODE

#endif // VAS_TEXTTOOLS_INDIE_MODE

namespace vas
{
	/** @addtogroup txt_tool
		  @{
	*/
	/** @brief The alternative console IO class.
		  
		  The static singletone class that provide basic tools for console IO.
	*/
	class VAS_DECLSPEC TextTools
	{ /** @} */
	public:
#ifdef VAS_WINDOWS_MODE
		/** @name Windows only members (only avaliable on Windows).*/
		static bool inited; /**< Determine if the tools is pre initialized. */

		static void initTextTools(); /**< Initialize the tools. */
		/** Convert wide char (UTF-16 encoded) string to multibytes or UTF-8 char string.
			  @param str Input string.
			  @param unicode Convert to unicode or not.
			  @retval std::string UTF-8 encoded string of @p str if @p unicode is true, multibytes char otherwise.
		*/
		static std::string wstos(const std::wstring&str, bool unicode = true);
		/** Convert multibytes or UTF-8 string to UTF-16 string.
			  @param str Input string.
			  @param unicode Is the input string encoded in UTF-8 or multibytes.
			  @retval std::wstring UTF-16 encoded string of @p str.
		*/
		static std::wstring stows(const std::string& str, bool unicode = true);
		/** @} */
#endif // VAS_WINDOWS_MODE

		static void print(const std::string& str); /**< Print a string to console. */
		static void print(const std::ostream& str); /**< Print a std::ostream to console.*/
		static void println(const std::string& str); /**< Print a string to console and end the line with std::endl. */
		static void println(const std::ostream& str); /**< Print a std::ostream to console and end the line with std::endl. */
		static void printf(const boost::format& fStr); /**< Print a boost::format to console. */
		static void printfln(const boost::format& fStr); /**< Print a boost::format to console and end the line with std::endl. */

		static std::string readln(); /**< Read a line of string from console. */

		template <typename ReturnType>
		static ReturnType read(); /**< Read any data type of value from console with `cin::operator>>()` (wcin on Windows). */
	};

	template<typename ReturnType>
	inline ReturnType TextTools::read()
	{
		ReturnType value;
#ifdef VAS_WINDOWS_MODE
		initTextTools();
		wcin >> value;
#else
		cin >> value;
#endif // VAS_WINDOWS_MODE
		return value;
	}

#ifdef VAS_WINDOWS_MODE
#define STD_CIN std::wcin
#define STD_COUT std::wcout
#define STD_CEER std::wcerr
#define VAS_STR_2_WSTR(str) vas::TextTools::stows(str)
#define VAS_WSTR_2_STR(str) vas::TextTools::wstos(str)
#define VAS_COMM_STR std::wstring
#else
#define STD_CIN std::cin
#define STD_COUT std::cout
#define STD_CEER std::cerr
#define VAS_STR_2_WSTR(str) str
#define VAS_WSTR_2_STR(str) str
#define VAS_COMM_STR std::string
#endif // VAS_WINDOWS_MODE

	class VAS_DECLSPEC Cout
	{
	public:
		Cout();
		Cout(const Cout&) = delete;
		Cout(Cout&&) = delete;
		Cout& operator=(const Cout&) = delete;
		Cout& operator=(Cout&&) = delete;
		~Cout();

		inline static decltype(STD_COUT)& getWrapedStream() { return STD_COUT; }

		Cout& operator<<(std::ostream& (*manipulator)(std::ostream& o));
		template<typename Type>
		Cout& operator<<(const Type& rhs)
		{
			ss << rhs;
			return *this;
		}

		static std::stringstream& getBuffer();
	private:
		void outputStream();
	private:
		static std::stringstream ss;
	};

	class VAS_DECLSPEC Ceer
	{
	public:
		Ceer();
		Ceer(const Ceer&) = delete;
		Ceer(Ceer&&) = delete;
		Ceer& operator=(const Ceer&) = delete;
		Ceer& operator=(Ceer&&) = delete;
		~Ceer();

		inline static decltype(STD_CEER)& getWrapedStream() { return STD_CEER; }

		Ceer& operator<<(std::ostream& (*manipulator)(std::ostream& o));
		template<typename Type>
		Ceer& operator<<(const Type& rhs)
		{
			ss << rhs;
			return *this;
		}

		static std::stringstream& getBuffer();
	private:
		void outputStream();
	private:
		static std::stringstream ss;
	};

	class VAS_DECLSPEC Cin
	{
	public:
		Cin();
		Cin(const Cin&) = delete;
		Cin(Cin&&) = delete;
		Cin& operator=(const Cin&) = delete;
		Cin& operator=(Cin&&) = delete;
		inline static decltype(STD_CIN)& getWrapedStream() { return STD_CIN; }

		template<typename Type>
		Cin& operator>>(Type& rhs)
		{
			STD_CIN >> rhs;
			return *this;
		}
		Cin& operator>>(std::string& rhs);
	};
}