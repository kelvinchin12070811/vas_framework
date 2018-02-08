#include "KeyboardCore.hpp"
#include "../boolean_cast.hpp"

namespace sdl
{
	sdl::Window getKeyboardFocus()
	{
		return static_cast<sdl::Window>(SDL_GetKeyboardFocus());
	}

	const uint8_t * getKeyboardState(int * numKey)
	{
		return SDL_GetKeyboardState(numKey);
	}

	SDL_Keymod getModState()
	{
		return SDL_GetModState();
	}

	void setModState(SDL_Keymod modstate)
	{
		SDL_SetModState(modstate);
	}

	sdl::Keycode getKeyFromScancode(sdl::Scancode scancode)
	{
		return static_cast<sdl::Keycode>(SDL_GetKeyFromScancode(static_cast<SDL_Scancode>(scancode)));
	}
	
	sdl::Scancode getScancodeFromKey(sdl::Keycode keycode)
	{
		return static_cast<sdl::Scancode>(SDL_GetScancodeFromKey(static_cast<SDL_Keycode>(keycode)));
	}

	std::string getScancodeName(sdl::Scancode scancode)
	{
		return SDL_GetScancodeName(static_cast<SDL_Scancode>(scancode));
	}
	
	sdl::Scancode getScancodeFromName(const std::string & name)
	{
		return static_cast<sdl::Scancode>(SDL_GetScancodeFromName(name.c_str()));
	}
	
	std::string getKeycodeName(sdl::Keycode key)
	{
		return SDL_GetKeyName(static_cast<SDL_Keycode>(key));
	}
	
	sdl::Keycode getKeycodeFromName(const std::string & name)
	{
		return static_cast<sdl::Keycode>(SDL_GetKeyFromName(name.c_str()));
	}
	
	void startTextInput()
	{
		SDL_StartTextInput();
	}
	
	bool isTextInputActive()
	{
		return boolean_cast(SDL_IsTextInputActive());
	}
	
	void stopTextInput()
	{
		SDL_StopTextInput();
	}
	
	void setTextInputRect(sdl::Rect * rect)
	{
		SDL_SetTextInputRect(reinterpret_cast<SDL_Rect*>(rect));
	}
	
	bool hasScreenKeyboardSupport()
	{
		return boolean_cast(SDL_HasScreenKeyboardSupport());
	}
	
	bool isScreenKeyboardShown(Window & window)
	{
		return boolean_cast(SDL_IsScreenKeyboardShown(static_cast<SDL_Window*>(window)));
	}
}