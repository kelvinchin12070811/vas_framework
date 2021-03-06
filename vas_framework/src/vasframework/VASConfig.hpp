//======================================================================
// This file is licensed under public domain
//======================================================================
#pragma once
#include <string>

#ifdef VAS_GEN_DLL
#include <boost/config.hpp>
#endif

/*Configuration of framework*/

#ifndef VAS_GLOB_CONFIG
#define VAS_GLOB_CONFIG

//#define VAS_GEN_DLL
//#define VAS_SDL_ENTRY
#define VAS_AUTO_FRAME_PATCH

#if __has_include(<Windows.h>)
#define WIN32
#endif

//Auto config options
#ifdef WIN32
#define VAS_WINDOWS_MODE
#endif

#if __has_include(<SDL2/SDL_mixer.h>) || defined(DOXYGEN)
#define VAS_USE_MIXER
#endif

#if __has_include(<SDL2/SDL_ttf.h>) || defined(DOXYGEN)
#define VAS_USE_TTF
#endif

#if __has_include(<Box2D/Box2D.h>) || defined(DOXYGEN)
#define VAS_HAS_B2D
#endif

#endif // !VAS_GLOB_CNFIG

#ifndef VAS_SDL_ENTRY
#define VAS_USE_OOENTRY
#endif

#ifdef VAS_WINDOWS_MODE
#define NOMINMAX
#endif

/** @ingroup vas_framework
	 @{
*/

/** Get current engine version
		
	 Definde in: vasframework/VASConfig.hpp
*/
inline std::string getEngineVersion()
{
	return "2.2.1";
}
/** @} */

//Generate library for dll
#ifdef VAS_GEN_DLL
#ifndef VAS_NO_WARNING
#error You enabled an experimential feature, it might not stable for development. Use VAS_NO_WARNING to supress this warning.
#endif
#if !defined(BOOST_HAS_DECLSPEC) && !defined(VAS_NO_WARNING)
#error This compiler does not support __declspec symbol and it might cause unexpected error. Use VAS_NO_WARNING to supress this warning.
#endif

#ifndef VAS_IMPORT
#define VAS_DECLSPEC BOOST_SYMBOL_EXPORT
#else
#define VAS_DECLSPEC BOOST_SYMBOL_IMPORT
#endif
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
