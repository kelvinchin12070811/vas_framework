/** @defgroup sdl_core SDL Core Wrapper Library
	  @brief The SDL2 wrapper use by vas_framework.

	  The SDL Core Wrapper Library is a wrapper library on SDL2 and some of its sub library. All of the related classes and
	  functions of a module can included by only one header which specified in each page of the modules.

	  This documentation will only provide basic briefy of all SDL functions, for more information about the functions, please
	  refer to the official SDL documentation.

	  @{
*/

/** @defgroup sdl_basic SDL Basic & Image Library
	  @brief Wrapper of SDL2 and sdl_image libraries.

	  All related class: \#include <vasframework/sdlcore/SDLCore.hpp>
*/

namespace vas
{
	namespace sdl
	{
		/** @addtogroup sdl_basic
			  @{
		*/
		const class EmptyComponent_t;
		/** Define an empty sdl component. */
		EmptyComponent_t emptycomponent;
		/** @} */
	}
}

/** @defgroup sdl_mixer SDL Mixer Library
	  @brief Wrapper of sdl_mixer library.

	  All related class: \#include <vasframework/sdlcore/audio/MixCore.hpp>
*/

/** @defgroup sdl_ttf SDL TTF Font Rendering Library
	  @brief Wrapper of sdl_ttf library.

	  All related class: \#include <vasframework/sdlcore/TTFCore.hpp>
*/

/** @} */