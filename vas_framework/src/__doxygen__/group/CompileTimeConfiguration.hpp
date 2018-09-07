/*! \defgroup compile_time_cfg Compile Time Configuration
\brief All of the configuration that controll how VAS Framework to compile.

| Header |
| : --- : |
| vasframework/VASConfig.hpp |

Configurations is very improtant to almost all application.
It change the behaviour of the application and even remember what the application done recently.

Virtual Assistant Framework provide a series of "compile-time" configurations in the form of C++ Macro.

The header file VASConfig.hpp contain all of the configurations that library will use.
This include the options to turning off some of the module of the library.

The configurations are written as C++ Macro and wrapped under "#ifdef VAS_GLOB_CONFIG" macro, therefore just
comment or uncomment the "#define" syntax that representing the setting.

\note If you don't whant to use sdl_ttf or sdl_mixer for some reason.
Turning them off will keep your dependency lower (you don't neet to include and link sdl_mixer or sdl_ttf into
your project).
*/

/*! \addtogroup compile_time_cfg
@{
*/
/*! Generate DLL friendly library. This change the value of the macro `VAS_DECLSPEC` from empty to Microsoft specific dll
export syntax (`__declspec(__dllexport)`).

Default is OFF.
*/
#define VAS_GEN_DLL

/*! Use SDL's entry point (int main(int argc, char** argv) instead of [Uniform Entry Point](uni_entry.html).
	 
	 Default is OFF.
*/
#define VAS_SDL_ENTRY
/*! @}*/