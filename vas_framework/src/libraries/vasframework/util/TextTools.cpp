#pragma once
#include <iostream>
#include "TextTools.hpp"

#ifdef _WINDOWS
#include <memory>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#endif // _WINDOWS

namespace vas
{
#ifdef _WINDOWS
	bool TextTools::inited = false;

	void TextTools::initTextTools()
	{
		if (inited) return;
		_setmode(fileno(stdin), _O_U16TEXT);
		_setmode(fileno(stdout), _O_U16TEXT);
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
#endif // _WINDOWS

	void TextTools::print(const std::string & str)
	{
#ifdef _WINDOWS
		initTextTools();
		std::wcout << stows(str);
#else
		std::cout << str;
#endif // _WINDOWS
	}

	void TextTools::println(const std::string & str)
	{
#ifdef _WINDOWS
		initTextTools();
		std::wcout << stows(str) << std::endl;
#else
		std::cout << str << std::endl;
#endif // _WINDOWS
	}

	void TextTools::printf(const boost::format & fStr)
	{
#ifdef _WINDOWS
		initTextTools();
		std::wcout << stows(boost::str(fStr));
#else
		std::cout << boost::str(fStr);
#endif // _WINDOWS
	}

	void TextTools::printfln(const boost::format & fStr)
	{
#ifdef _WINDOWS
		initTextTools();
		std::wcout << stows(boost::str(fStr)) << std::endl;
#else
		std::cout << boost::str(fStr) << std::endl;
#endif // _WINDOWS
	}

	std::string TextTools::readln()
	{
#ifdef _WINDOWS
		initTextTools();
		std::wstring buff;
		std::getline(std::wcin, buff);
		return wstos(buff);
#else
		std::string buff;
		std::getline(cin, buff);
		return buff;
#endif // _WINDOWS
	}
}