//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <SDL2/SDL.h>
#include "../VASConfig.hpp"

namespace vas::sdl
{
	/**
	 * @ingroup sdl_basic
	 * @{
	 */
	/**
	 * @brief Initialization flags of sdl library.
	 * 
	 * The InitFlags is the flags that tell sdl what sub component to init during the initialization of the library.
	 */
	struct VAS_DECLSPEC InitFlags
	{ /** @} */
		static const uint32_t everything; /**< Init all subsystem. */
		static const uint32_t timer; /**< Init timer subsystem. */
		static const uint32_t audio; /**< Init audio subsystem. */
		static const uint32_t video; /** Init video subsystem, from official docs: SDL_INIT_VIDEO implies SDL_INIT_EVENTS. */
		static const uint32_t joystick; /**<Init joystick subsystem, from official docs: SDL_INIT_JOYSTICK implies SDL_INIT_EVENTS. */
		static const uint32_t haptic; /**< Init haptic subsystem. */
		static const uint32_t gamecontroller; /**< Init gamecontroller subsystem, from official docs: SDL_INIT_GAMECONTROLLER implies SDL_INIT_JOYSTICK */
		static const uint32_t event; /**< Init event subsystem. */
		static const uint32_t noparachute; /**< compatibility, this flag is ignored. */
	};
}