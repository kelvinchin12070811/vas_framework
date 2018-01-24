#include "SDLCoreException.hpp"
#include <SDL.h>

namespace sdl
{
	SDLCoreException::SDLCoreException()
	{
	}

	SDLCoreException::~SDLCoreException()
	{
	}

	char const * SDLCoreException::what() const
	{
		return SDL_GetError();
	}
}