#pragma once
#include <string>

/*Configuration of framework*/

//#define VAS_GEN_DLL
//#define VAS_USE_UTF16
#define VAS_WINDOWS_MODE

/*Configuration end*/

//Generate library for dll
#ifdef VAS_GEN_DLL
#define VAS_DECLSPEC __declspec(dllexport)
#else
#define VAS_DECLSPEC
#endif //VAS_GEN_DLL

//Use UTF16 encoded string
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
