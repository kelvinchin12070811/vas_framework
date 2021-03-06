//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include "../../VASConfig.hpp"

#ifdef VAS_USE_TTF
#include <SDL2/SDL_ttf.h>
#include "Font.hpp"

namespace vas::sdl
{
	namespace ttf
	{
		/**
		 * @ingroup sdl_ttf
		 * @{
		 */
		VAS_DECLSPEC bool init(); /**< Initialize sdl_ttf library. @return true if success. */
		VAS_DECLSPEC void quit(); /**< Quit the sdl_ttf library. */
		VAS_DECLSPEC bool wasInit(); /**< Check if the library is initialized. */
		/** @} */
	}
}
#endif // VAS_USE_TTF