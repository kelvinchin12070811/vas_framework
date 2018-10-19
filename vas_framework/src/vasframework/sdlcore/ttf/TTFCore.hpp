#pragma once
#include "../../VASConfig.hpp"

#ifdef VAS_USE_TTF
#include <SDL_ttf.h>
#include "Font.hpp"

namespace vas::sdl
{
	namespace ttf
	{
		/** @addtogroup sdl_ttf
			  @{
		*/
		VAS_DECLSPEC bool init(); /**< Initialize sdl_ttf library. @return true if success. */
		VAS_DECLSPEC void quit(); /**< Quit the sdl_ttf library. */
		VAS_DECLSPEC bool wasInit(); /**< Check if the library is initialized. */
		/** @} */
	}
}
#endif // VAS_USE_TTF