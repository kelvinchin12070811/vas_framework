#pragma once
#include <SDL_image.h>

namespace sdl
{
	namespace image
	{
		struct ImageInitFlags
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