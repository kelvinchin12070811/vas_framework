#pragma once
#include <iostream>
#include "TextTools.hpp"

#ifdef VAS_WINDOWS_MODE
#include <memory>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#endif // VAS_WINDOWS_MODE

namespace vas
{
#ifdef VAS_WINDOWS_MODE
	bool TextTools::inited = false;

	void TextTools::initTextTools()
	{
		if (inited) return;
		_setmode(fileno(stdin), _O_U16TEXT);
		_setmode(fileno(stdout), _O_U16TEXT);
		_setmode(fileno(stderr), _O_U16TEXT);
		inited = true;
	}

	std::string TextTools::wstos(const std::wstring & str, bool unicode)
	{
		if (str.empty()) return std::string();
		uint32_t unicodeCP = unicode ? CP_UTF8 : CP_ACP;
		int newLength = 0;
		int oriLength = static_cast<int>(str.length() + 1);
		newLength = WideCharToMultiByte(unicodeCP, 0, str.c_str(), oriLength, nullptr, 0, nullptr, nullptr);
		if (newLength == 0) return std::string();
		std::unique_ptr<char[]> mbstr = std::make_unique<char[]>(newLength);
		WideCharToMultiByte(unicodeCP, 0, str.c_str(), oriLength, mbstr.get(), newLength, nullptr, nullptr);
		return std::string(mbstr.get());
	}

	std::wstring TextTools::stows(const std::string & str, bool unicode)
	{
		if (str.empty()) return std::wstring();
		uint32_t unicodeCP = unicode ? CP_UTF8 : CP_ACP;
		int newLength = 0;
		int oriLength = str.length() + 1;
		newLength = MultiByteToWideChar(unicodeCP, 0, str.c_str(), oriLength, nullptr, 0);
		if (newLength == 0) return std::wstring();
		std::unique_ptr<wchar_t[]> wstr = std::make_unique<wchar_t[]>(newLength);
		MultiByteToWideChar(unicodeCP, 0, str.c_str(), oriLength, wstr.get(), newLength);
		return std::wstring(wstr.get());
	}
#endif // VAS_WINDOWS_MODE

	void TextTools::print(const std::string & str)
	{
#ifdef VAS_WINDOWS_MODE
		initTextTools();
		std::wcout << stows(str);
#else
		std::cout << str;
#endif // VAS_WINDOWS_MODE
	}

	void TextTools::print(const std::ostream & str)
	{
		print(dynamic_cast<const std::stringstream&>(str).str());
	}

	void TextTools::println(const std::string & str)
	{
#ifdef VAS_WINDOWS_MODE
		initTextTools();
		std::wcout << stows(str) << std::endl;
#else
		std::cout << str << std::endl;
#endif // VAS_WINDOWS_MODE
	}

	void TextTools::println(const std::ostream & str)
	{
		println(dynamic_cast<const std::stringstream&>(str).str());
	}

	void TextTools::printf(const boost::format & fStr)
	{
#ifdef VAS_WINDOWS_MODE
		initTextTools();
		std::wcout << stows(boost::str(fStr));
#else
		std::cout << boost::str(fStr);
#endif // VAS_WINDOWS_MODE
	}

	void TextTools::printfln(const boost::format & fStr)
	{
#ifdef VAS_WINDOWS_MODE
		initTextTools();
		std::wcout << stows(boost::str(fStr)) << std::endl;
#else
		std::cout << boost::str(fStr) << std::endl;
#endif // VAS_WINDOWS_MODE
	}

	std::string TextTools::readln()
	{
#ifdef VAS_WINDOWS_MODE
		initTextTools();
		std::wstring buff;
		std::getline(std::wcin, buff);
		return wstos(buff);
#else
		std::string buff;
		std::getline(cin, buff);
		return buff;
#endif // VAS_WINDOWS_MODE
	}

	VAS_DECLSPEC boost::format make_format(const std::string& rhs)
	{
		return boost::format(rhs);
	}

	Cout::Cout()
	{
#ifdef VAS_WINDOWS_MODE
		TextTools::initTextTools();
#endif // VAS_WINDOWS_MODE
	}

	Cout::~Cout()
	{
		STD_COUT << VAS_STR_2_WSTR(ss.str());
	}

	Cout & Cout::operator<<(std::ostream &(*manipulator)(std::ostream &o))
	{
		ss << manipulator;
		return *this;
	}

	Cin::Cin()
	{
#ifdef VAS_WINDOWS_MODE
		TextTools::initTextTools();
#endif // VAS_WINDOWS_MODE
	}

	Cin & Cin::operator>>(std::string & rhs)
	{
		VAS_COMM_STR temp;
		STD_CIN >> temp;
		rhs = VAS_WSTR_2_STR(temp);
		return *this;
	}

	Ceer::Ceer()
	{
#ifdef VAS_WINDOWS_MODE
		TextTools::initTextTools();
#endif // VAS_WINDOWS_MODE
	}

	Ceer::~Ceer()
	{
		STD_CEER << VAS_STR_2_WSTR(ss.str());
	}

	Ceer & Ceer::operator<<(std::ostream &(*manipulator)(std::ostream &o))
	{
		ss << manipulator;
		return *this;
	}
}