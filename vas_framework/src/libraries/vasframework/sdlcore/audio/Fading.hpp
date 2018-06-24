#pragma once
#include "../../VASConfig.hpp"

#ifdef VAS_USE_MIXER
#include <SDL_mixer.h>

namespace vas::sdl
{
	namespace mixer
	{
		enum class Fading
		{
			noFading = MIX_NO_FADING,
			fadingOut = MIX_FADING_OUT,
			fadingIn = MIX_FADING_IN
		};
	}
}
#endif // VAS_USE_MIXER
