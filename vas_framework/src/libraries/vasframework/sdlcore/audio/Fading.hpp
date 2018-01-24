#pragma once
#include <SDL_mixer.h>

namespace sdl
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