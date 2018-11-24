#pragma once
#include <string>

/*Configuration of framework*/

#ifndef VAS_GLOB_CONFIG
#define VAS_GLOB_CONFIG

//#define VAS_GEN_DLL
//#define VAS_SDL_ENTRY
#define VAS_AUTO_FRAME_PATCH

//Auto config options
#if __has_include(<Windows.h>)
#define VAS_WINDOWS_MODE
#endif

#if __has_include(<sdl_mixer.h>)
#define VAS_USE_MIXER
#endif

#if __has_include(<sdl_ttf.h>)
#define VAS_USE_TTF
#endif

#endif // !VAS_GLOB_CNFIG

#ifndef VAS_SDL_ENTRY
#define VAS_USE_UNIENTRY
#endif

/** @addtogroup vas_framework
	 @{
*/

/** Get current engine version
		
	 Definde in: vasframework/VASConfig.hpp
*/
inline std::string getEngineVersion()
{
	return "2.2.0";
}
/** @} */

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
