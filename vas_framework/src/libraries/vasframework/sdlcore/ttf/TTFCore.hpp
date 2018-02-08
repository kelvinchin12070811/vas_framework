#pragma once
#include <SDL_ttf.h>
#include "../../VASConfig.hpp"
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