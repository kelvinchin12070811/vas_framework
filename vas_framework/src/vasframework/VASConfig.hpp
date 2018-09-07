#pragma once
#include <string>

/*Configuration of framework*/

#ifndef VAS_GLOB_CONFIG
#define VAS_GLOB_CONFIG

/*! \addtogroup compile_time_cfg
@{
*/
/* Generate DLL friendly classes */
//#define VAS_GEN_DLL

/*! Using Windows specific code for some functions to optimize the experience.
	 It will make the code platfrom specific for Windows only.

	 Default is ON.
*/
#define VAS_WINDOWS_MODE

/*! Use SDL_mixer audio library. Comment out this macro will disable the audio functionality of the library
	 (VAS Framework use SDL_mixer as its main audio library for audio play back). But the SDL's audio feature is still valid.

	 Default is ON.

	 \note Disable Audio Module will disable AudioManager too.
*/
#define VAS_USE_MIXER

/*! Use SDL_ttf font rendering engine.

	 Default is ON.

	 \note Disable this will turn off the functionality off text rendering feature such as sdl::TTF.
*/
#define VAS_USE_TTF

/* Use SDL Entry Point */
//#define VAS_SDL_ENTRY

/*! @}*/
#ifndef VAS_SDL_ENTRY

/*! \addtogroup compile_time_cfg
		@}
*/
#define VAS_USE_UNIENTRY
/*! @}*/
#endif

/*Configuration end*/
#endif // !VAS_GLOB_CNFIG

/** @addtogroup vas_framework
	 @{
*/

/** Get current engine version
		
	 Definde in: vasframework/VASConfig.hpp
*/
inline std::string getEngineVersion()
{
	return "2.1.2";
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
