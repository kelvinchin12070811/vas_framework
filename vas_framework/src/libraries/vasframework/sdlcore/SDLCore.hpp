#pragma once
#include <string>
#include "SDLCoreException.hpp"
#include "boolean_cast.hpp"
#include "ImageInitFlags.hpp"
#include "Math.hpp"
#include "SDLInitFlags.hpp"
#include "Video.hpp"
#include "Events.hpp"
#include "RWops.hpp"
#include "audio/MixCore.hpp"
#include "keyboard/Keycode.hpp"
#include "ttf/TTFCore.hpp"

namespace sdl
{
	std::string VAS_DECLSPEC getError();

	void VAS_DECLSPEC delay(uint32_t ms);
	uint32_t VAS_DECLSPEC getTicks();

	/*return true if success, use sdl::getError() to get last error string
	origin: SDL_Init(uint32_t)*/
	bool VAS_DECLSPEC init(uint32_t flags = sdl::InitFlags::everything);

	/**
	*  This function initializes specific SDL subsystems
	*
	*  Subsystem initialization is ref-counted, you must call
	*  SDL_QuitSubSystem() for each SDL_InitSubSystem() to correctly
	*  shutdown a subsystem manually (or call SDL_Quit() to force shutdown).
	*  If a subsystem is already loaded then this call will
	*  increase the ref-count and return.
	*/
	bool VAS_DECLSPEC initSubSystem(uint32_t flags);

	/**
	*  This function cleans up all initialized subsystems. You should
	*  call it upon all exit conditions.
	*/
	void VAS_DECLSPEC quit();
	/**
	*  This function cleans up specific SDL subsystems
	*/
	void VAS_DECLSPEC quitSubSystem(uint32_t flags);

	/**
	*  This function returns a mask of the specified subsystems which have
	*  previously been initialized.
	*
	*  If \c flags is 0, it returns a mask of all initialized subsystems.
	*/
	uint32_t VAS_DECLSPEC wasInit(uint32_t flags);

	namespace image
	{
		int VAS_DECLSPEC init(int flags = ImageInitFlags::all_webp_not_included);
		void VAS_DECLSPEC quit();
	}
}