#pragma once
#include "../../VASConfig.hpp"

#ifdef VAS_USE_TTF
#include <SDL_ttf.h>

namespace vas::sdl
{
	namespace ttf
	{
		/** @addtogroup sdl_ttf
			  @{
		*/
		/** @brief Font style of rendered text. */
		struct FontStyle
		{
			using FlagType = int; /**< Font style flag type. */
			static const FlagType normal = 0x00; /**< Normal style. */
			static const FlagType bold = 0x01; /**< Bold style. */
			static const FlagType italic = 0x02; /**< Italic style. */
			static const FlagType underline = 0x04; /**< Underline style. */
			static const FlagType strikethrough = 0x08; /**< Strikethrough style. */
		};

		/** @brief Set and retrieve FreeType hinter settings. */
		struct FontHinting
		{
			using FlagType = int; /**< Flags type. */
			static const FlagType normal = 0; /**< Normal. */
			static const FlagType light = 1; /**< Light. */
			static const FlagType mono = 2; /**< Mono. */
			static const FlagType none = 3; /**< None. */
		};
		/** @} */
	}
}
#endif // VAS_USE_TTF
