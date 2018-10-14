#pragma once
#include <SDL_image.h>
#include "../VASConfig.hpp"

namespace vas::sdl
{
	namespace image
	{
		/** @addtogroup sdl_basic
			  @{
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