#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <boost/format.hpp>

//#define VAS_TEXTTOOLS_INDIE_MODE

#ifndef VAS_TEXTTOOLS_INDIE_MODE
#include "../VASConfig.hpp"

#ifndef VAS_GLOB_CONFIG
#error VASConfig.hpp not found. define "VAS_TEXTTOOLS_INDIE_MODE" to make this library works in independent mode.
#endif

#else
#define VAS_WINDOWS_MODE

#ifdef VAS_WINDOWS_MODE
#define VAS_DECLSPEC __declspec(dllexport)
#else
#define VAS_DECLSPEC
#endif // VAS_WINDOWS_MODE

#endif // VAS_TEXTTOOLS_INDIE_MODE

namespace vas
{
	class VAS_DECLSPEC TextTools
	{
	public:
#ifdef VAS_WINDOWS_MODE
		static bool inited;

		static void initTextTools();
		static std::string wstos(const std::wstring&str, bool unicode = true);
		static std::wstring stows(const std::string& str, bool unicode = true);
#endif // VAS_WINDOWS_MODE

		static void print(const std::string& str);
		static void print(const std::ostream& str);
		static void println(const std::string& str);
		static void println(const std::ostream& str);
		static void printf(const boost::format& fStr);
		static void printfln(const boost::format& fStr);

		static std::string readln();

		template <typename ReturnType>
		static ReturnType read();
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
		~Cout();

		inline static decltype(STD_COUT)& getWrapedStream() { return STD_COUT; }

		Cout& operator<<(std::ostream& (*manipulator)(std::ostream& o));
		template<typename Type>
		Cout& operator<<(const Type& rhs)
		{
			ss << rhs;
			return *this;
		}

		static std::stringstream& getBufer();
	private:
		void outputStream();
	private:
		static std::stringstream ss;
	};

	class VAS_DECLSPEC Ceer
	{
	public:
		Ceer();
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