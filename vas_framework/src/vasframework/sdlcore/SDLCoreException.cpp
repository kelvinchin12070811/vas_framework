#include "SDLCoreException.hpp"
#include <SDL.h>

namespace vas::sdl
{
	char const * SDLCoreException::what() const
	{
		return SDL_GetError();
	}
}