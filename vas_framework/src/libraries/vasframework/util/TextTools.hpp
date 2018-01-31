#pragma once
#include <iostream>
#include <string>
#include <boost/format.hpp>

#include "../VASConfig.hpp"

namespace vas
{
	class VAS_DECLSPEC TextTools
	{
	public:
#ifdef _WINDOWS
		static bool inited;

		static void initTextTools();
		static std::string wstos(const std::wstring&str, bool unicode = true);
		static std::wstring stows(const std::string& str, bool unicode = true);
#endif // _WINDOWS

		static void print(const std::string& str);
		static void println(const std::string& str);
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
#ifdef _WINDOWS
		initTextTools();
		wcin >> value;
#else
		cin >> value;
#endif // _WINDOWS
		return value;
	}
}