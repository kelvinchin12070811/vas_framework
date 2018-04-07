#pragma once
#include <string>

/*Configuration of framework*/

//#define VAS_GEN_DLL
#define VAS_WINDOWS_MODE
#define VAS_USE_MIXER
#define VAS_USE_TTF

/*Configuration end*/

//Generate library for dll
#ifdef VAS_GEN_DLL
#define VAS_DECLSPEC __declspec(dllexport)
#else
#define VAS_DECLSPEC
#endif //VAS_GEN_DLL

#ifdef VAS_USE_UTF16
namespace vas
{
	using String = std::wstring;
}
#define STR(string) L##string
#else
namespace vas
{
	using String = std::string;
}
#define STR(string) string
#endif // VAS_USE_UTF16
