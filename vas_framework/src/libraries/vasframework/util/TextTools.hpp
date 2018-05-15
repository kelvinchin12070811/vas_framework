#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <boost/format.hpp>
#include "../VASConfig.hpp"

#define vasstream std::stringstream()
#define vasformat(str) boost::format(str)

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
}