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

#ifndef COM_BLOGSPOT_KELVINCHIN12070811_VAS_TESTTOOLS_H
#define COM_BLOGSPOT_KELVINCHIN12070811_VAS_TESTTOOLS_H
#include <Windows.h>
#include <string>
#include <codecvt>
#include <fcntl.h>
#include <io.h>

#define _TEXTTOOLS

#define VAS_TEXTTOOLS_GETVARNAME(x) std::wstring(L#x)
#define VAS_TEXTTOOLS_GETVARNAMEU8(x) std::string(u8#x)

#define VAS_TEXTTOOLS_SETLOCAL(object) object.imbue(std::locale(object.getloc(), new std::codecvt_utf8<wchar_t>))
#define VAS_TEXTTOOLS_SETLOCALU8U16(object) object.imbue(std::locale(object.getloc(), new std::codecvt_utf8_utf16<wchar_t>))

#define VAS_TEXTTOOL_GENDLL

namespace vas
{
#ifdef VAS_TEXTTOOL_GENDLL
	class __declspec(dllexport) TextTools
#else
	class TextTools
#endif // VAS_TEXTTOOL_GENDLL

	{
	public:
		static std::string wstos(const std::wstring& value, bool unicode = true);	//This function only work on Windows
		static std::wstring stows(const std::string& value, bool unicode = true);	//This function only work on Windows

		static std::string cast(const std::wstring& value, bool unicode = true);
		static std::wstring cast(const std::string& value, bool unicode = false);

		static inline void init_stdout() { _setmode(_fileno(stdout), _O_U16TEXT); }
		static inline void init_stdin() { _setmode(_fileno(stdin), _O_U16TEXT); }
	};

	template <typename OutputStr, typename InputStr>
	OutputStr str_cast(const InputStr& value) //Provide C++ style casting (like boost::any_cast)
	{
		return TextTools::cast(value);
	}
}
#endif // !COM_BLOGSPOT_KELVINCHIN12070811_VAS_TESTTOOLS_H