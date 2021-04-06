//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <SDL2/SDL.h>

namespace vas::sdl
{
	/**
	 * @ingroup sdl_basic
	 * @{
	 */
	/** Cast SDL_bool to bool. */
	inline bool boolean_cast(SDL_bool value)
	{
		return (value == SDL_bool::SDL_TRUE) ? true : false;
	}
	/** Cast bool to SDL_bool. */
	inline SDL_bool boolean_cast(bool value)
	{
		return (value == true) ? SDL_bool::SDL_TRUE : SDL_bool::SDL_FALSE;
	}
	/** @} */
}