#pragma once
#include <SDL.h>

namespace vas::sdl
{
	inline bool boolean_cast(SDL_bool value)
	{
		return (value == SDL_bool::SDL_TRUE) ? true : false;
	}
	inline SDL_bool boolean_cast(bool value)
	{
		return (value == true) ? SDL_bool::SDL_TRUE : SDL_bool::SDL_FALSE;
	}
}