#pragma once
#include <string>

/*Configuration of framework*/

#ifndef VAS_GLOB_CONFIG
#define VAS_GLOB_CONFIG
/* Generate DLL friendly classes */
//#define VAS_GEN_DLL

/* Using Windows specific codes */
#define VAS_WINDOWS_MODE

/* Enable SDL_Mixer */
#define VAS_USE_MIXER

/* Enable SDL_TTF */
#define VAS_USE_TTF

/*Configuration end*/
#endif // !VAS_GLOB_CNFIG


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
