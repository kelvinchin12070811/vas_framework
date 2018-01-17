#pragma once
#include <SDL.h>

namespace sdl
{
	enum InitFlags
	{
		everything = SDL_INIT_EVERYTHING,
		timer = SDL_INIT_TIMER,
		audio = SDL_INIT_AUDIO,
		/**< SDL_INIT_VIDEO implies SDL_INIT_EVENTS */
		video = SDL_INIT_VIDEO,
		/**< SDL_INIT_JOYSTICK implies SDL_INIT_EVENTS */
		joystick = SDL_INIT_JOYSTICK,
		haptic = SDL_INIT_HAPTIC,
		/**< SDL_INIT_GAMECONTROLLER implies SDL_INIT_JOYSTICK */
		gamecontroller = SDL_INIT_GAMECONTROLLER,
		event = SDL_INIT_EVENTS,
		/**< compatibility; this flag is ignored. */
		noparachute = SDL_INIT_NOPARACHUTE
	};
}