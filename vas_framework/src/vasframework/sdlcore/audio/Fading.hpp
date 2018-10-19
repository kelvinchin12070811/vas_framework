#pragma once
#include "../../VASConfig.hpp"

#ifdef VAS_USE_MIXER
#include <SDL_mixer.h>

namespace vas::sdl
{
	namespace mixer
	{
		/** @addtogroup sdl_mixer
			  @{
		*/
		/** Fading state of music stream. */
		enum class Fading
		{ /** @} */
			noFading = MIX_NO_FADING, /**< Fading effect not aplied.*/
			fadingOut = MIX_FADING_OUT, /**< Fading out. */
			fadingIn = MIX_FADING_IN /**< Fading in. */
		};
	}
}
#endif // VAS_USE_MIXER
