#pragma once
#include <SDL.h>

namespace sdl
{
	struct InitFlags
	{
		static const uint32_t everything;
		static const uint32_t timer;
		static const uint32_t audio;
		/**< SDL_INIT_VIDEO implies SDL_INIT_EVENTS */
		static const uint32_t video;
		/**< SDL_INIT_JOYSTICK implies SDL_INIT_EVENTS */
		static const uint32_t joystick;
		static const uint32_t haptic;
		/**< SDL_INIT_GAMECONTROLLER implies SDL_INIT_JOYSTICK */
		static const uint32_t gamecontroller;
		static const uint32_t event;
		/**< compatibility; this flag is ignored. */
		static const uint32_t noparachute;
	};
}