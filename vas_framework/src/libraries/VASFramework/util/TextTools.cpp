/*****************************************************************************************

version 1.2.8, April 28th, 2013

Copyright (C) 2017 Kelvin Chin

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

******************************************************************************************/

#include "TextTools.hpp"

namespace vas
{
	std::string TextTools::wstos(const std::wstring & value, bool unicode)
	{
		UINT codepage = unicode ? CP_UTF8 : CP_ACP;
		if (value.empty()) return unicode ? u8"" : "";
		int newlength = WideCharToMultiByte(codepage, 0, value.c_str(), -1, nullptr, 0, nullptr, nullptr);
		if (newlength == 0) return unicode ? u8"" : "";
		char* buffer = new char[newlength];
		WideCharToMultiByte(codepage, 0, value.c_str(), -1, buffer, newlength, nullptr, nullptr);
		std::string result(std::move(buffer));
		delete[] buffer;
		return result;
	}

	std::wstring TextTools::stows(const std::string & value, bool unicode)
	{
		UINT codepage = unicode ? CP_UTF8 : CP_ACP;
		if (value.empty()) return L"";
		int newlength = MultiByteToWideChar(codepage, 0, value.c_str(), -1, nullptr, 0);
		if (newlength == 0) return L"";
		wchar_t* buffer = new wchar_t[newlength];
		MultiByteToWideChar(codepage, 0, value.c_str(), -1, buffer, newlength);
		std::wstring result(std::move(buffer));
		delete[] buffer;
		return result;
	}

	std::string TextTools::cast(const std::wstring & value, bool unicode)
	{
		return wstos(value, unicode);
	}

	std::wstring TextTools::cast(const std::string & value, bool unicode)
	{
		return stows(value, unicode);
	}
}