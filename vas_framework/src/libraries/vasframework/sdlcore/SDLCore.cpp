#include "SDLCore.hpp"

namespace sdl
{
	std::string getError()
	{
		return SDL_GetError();
	}

	void VAS_DECLSPEC delay(uint32_t ms)
	{
		SDL_Delay(ms);
	}

	bool init(uint32_t flags)
	{
		return SDL_Init(flags) == 0 ? true : false;
	}

	bool VAS_DECLSPEC initSubSystem(uint32_t flags)
	{
		return SDL_InitSubSystem(flags) == 0 ? true : false;
	}

	void VAS_DECLSPEC quit()
	{
		SDL_Quit();
	}

	void VAS_DECLSPEC quitSubSystem(uint32_t flags)
	{
		return SDL_QuitSubSystem(flags);
	}

	uint32_t VAS_DECLSPEC wasInit(uint32_t flags)
	{
		return SDL_WasInit(flags);
	}
}