//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "SDLCore.hpp"

namespace vas::sdl
{
	std::string getError()
	{
		return SDL_GetError();
	}

	void delay(uint32_t ms)
	{
		SDL_Delay(ms);
	}

	uint32_t VAS_DECLSPEC getTicks()
	{
		return SDL_GetTicks();
	}

	bool init(uint32_t flags)
	{
		return SDL_Init(flags) == 0 ? true : false;
	}

	bool initSubSystem(uint32_t flags)
	{
		return SDL_InitSubSystem(flags) == 0 ? true : false;
	}

	void quit()
	{
		SDL_Quit();
	}

	void quitSubSystem(uint32_t flags)
	{
		return SDL_QuitSubSystem(flags);
	}

	uint32_t wasInit(uint32_t flags)
	{
		return SDL_WasInit(flags);
	}
}

int vas::sdl::image::init(int flags)
{
	return IMG_Init(flags);
}

void vas::sdl::image::quit()
{
	IMG_Quit();
}
