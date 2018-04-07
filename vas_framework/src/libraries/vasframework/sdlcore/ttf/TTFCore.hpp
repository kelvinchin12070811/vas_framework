#pragma once
#include "../../VASConfig.hpp"

#ifdef VAS_USE_TTF
#include <SDL_ttf.h>
#include "Font.hpp"

namespace sdl
{
	namespace ttf
	{
		VAS_DECLSPEC bool init();
		VAS_DECLSPEC void quit();
		VAS_DECLSPEC bool wasInit();
	}
}
#endif // VAS_USE_TTF