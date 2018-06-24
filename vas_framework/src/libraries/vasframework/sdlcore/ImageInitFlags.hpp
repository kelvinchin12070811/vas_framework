#pragma once
#include <SDL_image.h>
#include "../VASConfig.hpp"

namespace vas::sdl
{
	namespace image
	{
		struct VAS_DECLSPEC ImageInitFlags
		{
			static const int jpg;
			static const int png;
			static const int tif;
			static const int webp;
			static const int all;
			static const int all_webp_not_included;
		};
	}
}