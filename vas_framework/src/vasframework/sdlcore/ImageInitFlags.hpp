//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <SDL2/SDL_image.h>
#include "../VASConfig.hpp"

namespace vas::sdl
{
	namespace image
	{
		/**
		 * @ingroup sdl_basic
		 * @{
		 */
		/** @brief Initialization flags of sdl_image. */
		struct VAS_DECLSPEC ImageInitFlags
		{
			static const int jpg; /**< jpg/jpeg format. */
			static const int png; /**< png format. */
			static const int tif; /**< tif/tiff format. */
			static const int webp; /**< webp format. */
			static const int all; /**< all image format. */
			static const int all_webp_not_included; /**< all image format except webp. */
		};
		/** @} */
	}
}