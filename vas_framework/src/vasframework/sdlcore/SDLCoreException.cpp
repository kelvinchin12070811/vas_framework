//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "SDLCoreException.hpp"
#include <SDL2/SDL.h>

namespace vas::sdl
{
	char const * SDLCoreException::what() const
	{
		return SDL_GetError();
	}
}