#include "SDLCoreException.hpp"
#include <SDL.h>

namespace vas::sdl
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