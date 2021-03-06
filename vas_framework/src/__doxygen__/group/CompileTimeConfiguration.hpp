/**
 * @defgroup compile_time_cfg Compile Time Configuration
 * @brief All of the configuration that controll how VAS Framework to compile.
 * 
 * Configurations is very improtant to almost all application.
 * It change the behaviour of the application and even remember what the application done recently.
 * 
 * Virtual Assistant Framework provide a series of "compile-time" configurations in the form of C++ Macro.
 * 
 * The header file vasframework/VASConfig.hpp contain all of the configurations that library will use.
 * This include the options to turning off some of the module of the library.
 * 
 * The configurations are written as C++ Macro and wrapped under "#ifdef VAS_GLOB_CONFIG" macro, therefore 
 * just comment or uncomment the "#define" syntax that representing the setting.
 * 
 * @note If you don't whant to use sdl_ttf or sdl_mixer for some reason.
 * Turning them off will keep your dependency lower (you don't neet to include and link sdl_mixer or sdl_ttf
 * into your project).
 * 
 * @note The file VASConfig.hpp is licensed under BSD 3 - Clause instead of MPL 2.0
 */

/**
 * @addtogroup compile_time_cfg
 * @{
 */
/**
 * Generate DLL friendly library. This change the value of the macro #VAS_DECLSPEC from empty to Microsoft
 * specific dll export syntax (`__declspec(__dllexport)`).
 * 
 * Default is undefined.
 * @warning This is an experimential feature which might cause unexpected error. If precompile is must, use
 * static library instead.
 */
#define VAS_GEN_DLL

/**
 * Use SDL's entry point (int main(int argc, char** argv) instead of
 * [Object-oriented entry point](ooentry.html).
 * 
 * Default is undefined.
 */
#define VAS_SDL_ENTRY

/**
 * Using Windows specific code for some functions to optimize the experience.
 * It will make the code platfrom specific for Windows only.
 * 
 * defined if on windows platform.
 */
#define VAS_WINDOWS_MODE

/**
 * Use SDL_mixer audio library. Comment out this macro will disable the audio functionality of the library
 * (VAS Framework use SDL_mixer as its main audio library for audio play back). But the SDL's audio feature
 * is still valid.
 * 
 * defined if SDL_mixer library found.
 * 
 * @note Disable Audio Module will disable AudioManager too.
 */
#define VAS_USE_MIXER

/**
 * Use SDL_ttf font rendering engine.
 * 
 * defined if SDL_ttf library found.
 * 
 * @note Disable this will turn off the functionality off text rendering feature such as sdl::TTF.
 */
#define VAS_USE_TTF

/**
 * Auto recover lost frame when enough system resources. This will patch up every frame that skiped when meet
 * frame rate bottle neck.
 * 
 * Default is defined.
 */
#define VAS_AUTO_FRAME_PATCH
/** @} */