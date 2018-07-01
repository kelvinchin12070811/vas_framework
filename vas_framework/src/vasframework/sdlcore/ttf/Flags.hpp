#pragma once
#include "../../VASConfig.hpp"

#ifdef VAS_USE_TTF
#include <SDL_ttf.h>

namespace vas::sdl
{
	namespace ttf
	{
		struct FontStyle
		{
			using FlagType = int;
			static const FlagType normal = 0x00;
			static const FlagType bold = 0x01;
			static const FlagType italic = 0x02;
			static const FlagType underline = 0x04;
			static const FlagType strikethrough = 0x08;
		};

		struct FontHinting
		{
			using FlagType = int;
			static const FlagType normal = 0;
			static const FlagType light = 1;
			static const FlagType mono = 2;
			static const FlagType none = 3;
		};
	}
}
#endif // VAS_USE_TTF
