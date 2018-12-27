#include "SDLInitFlags.hpp"

namespace vas::sdl
{
	const uint32_t InitFlags::everything{ SDL_INIT_EVERYTHING };
	const uint32_t InitFlags::timer{ SDL_INIT_TIMER };
	const uint32_t InitFlags::audio{ SDL_INIT_AUDIO };
	const uint32_t InitFlags::video{ SDL_INIT_VIDEO };
	const uint32_t InitFlags::joystick{ SDL_INIT_JOYSTICK };
	const uint32_t InitFlags::haptic{ SDL_INIT_HAPTIC };
	const uint32_t InitFlags::gamecontroller{ SDL_INIT_GAMECONTROLLER };
	const uint32_t InitFlags::event{ SDL_INIT_EVENTS };
	const uint32_t InitFlags::noparachute{ SDL_INIT_NOPARACHUTE };
}