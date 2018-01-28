#pragma once
#include <SDL_ttf.h>
#include "../../VASConfig.hpp"
#include "Font.hpp"

namespace sdl
{
	namespace ttf
	{
		bool VAS_DECLSPEC init();
		void VAS_DECLSPEC quit();
		bool VAS_DECLSPEC wasInit();
	}
}