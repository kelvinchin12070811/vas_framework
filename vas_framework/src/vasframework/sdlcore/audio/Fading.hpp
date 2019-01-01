//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
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
