#pragma once
#include <string>
#include <SDL_keyboard.h>
#include "../../VASConfig.hpp"
#include "Keycode.hpp"
#include "Scancode.hpp"
#include "../video/Window.hpp"
#include "../math/Rect.hpp"

namespace sdl
{
	/**
	*  \brief Get the window which currently has keyboard focus.
	*/
	VAS_DECLSPEC sdl::Window getKeyboardFocus();

	/**
	*  \brief Get a snapshot of the current state of the keyboard.
	*
	*  \param numkeys if non-NULL, receives the length of the returned array.
	*
	*  \return An array of key states. Indexes into this array are obtained by using ::SDL_Scancode values.
	*
	*  \b Example:
	*  \code
	*  const Uint8 *state = SDL_GetKeyboardState(NULL);
	*  if ( state[SDL_SCANCODE_RETURN] )   {
	*      printf("<RETURN> is pressed.\n");
	*  }
	*  \endcode
	*/
	VAS_DECLSPEC const uint8_t* getKeyboardState(int* numKey = nullptr);

	/**
	*  \brief Get the current key modifier state for the keyboard.
	*/
	VAS_DECLSPEC SDL_Keymod getModState();

	/**
	*  \brief Set the current key modifier state for the keyboard.
	*
	*  \note This does not change the keyboard state, only the key modifier flags.
	*/
	VAS_DECLSPEC void setModState(SDL_Keymod modstate);

	/**
	*  \brief Get the key code corresponding to the given scancode according
	*         to the current keyboard layout.
	*
	*  See ::SDL_Keycode for details.
	*
	*  \sa SDL_GetKeyName()
	*/
	VAS_DECLSPEC sdl::Keycode getKeyFromScancode(sdl::Scancode scancode);

	/**
	*  \brief Get the scancode corresponding to the given key code according to the
	*         current keyboard layout.
	*
	*  See ::SDL_Scancode for details.
	*
	*  \sa SDL_GetScancodeName()
	*/
	VAS_DECLSPEC sdl::Scancode getScancodeFromKey(sdl::Keycode keycode);

	/**
	*  \brief Get a human-readable name for a scancode.
	*
	*  \return A pointer to the name for the scancode.
	*          If the scancode doesn't have a name, this function returns
	*          an empty string ("").
	*
	*  \sa SDL_Scancode
	*/
	VAS_DECLSPEC std::string getScancodeName(sdl::Scancode scancode);

	/**
	*  \brief Get a scancode from a human-readable name
	*
	*  \return scancode, or SDL_SCANCODE_UNKNOWN if the name wasn't recognized
	*
	*  \sa SDL_Scancode
	*/
	VAS_DECLSPEC sdl::Scancode getScancodeFromName(const std::string& name);

	/**
	*  \brief Get a human-readable name for a key.
	*
	*  \return A pointer to a UTF-8 string that stays valid at least until the next
	*          call to this function. If you need it around any longer, you must
	*          copy it.  If the key doesn't have a name, this function returns an
	*          empty string ("").
	*
	*  \sa SDL_Keycode
	*/
	VAS_DECLSPEC std::string getKeycodeName(sdl::Keycode key);

	/**
	*  \brief Get a key code from a human-readable name
	*
	*  \return key code, or SDLK_UNKNOWN if the name wasn't recognized
	*
	*  \sa SDL_Keycode
	*/
	VAS_DECLSPEC sdl::Keycode getKeycodeFromName(const std::string& name);

	/**
	*  \brief Start accepting Unicode text input events.
	*         This function will show the on-screen keyboard if supported.
	*
	*  \sa SDL_StopTextInput()
	*  \sa SDL_SetTextInputRect()
	*  \sa SDL_HasScreenKeyboardSupport()
	*/
	VAS_DECLSPEC void startTextInput();

	/**
	*  \brief Return whether or not Unicode text input events are enabled.
	*
	*  \sa SDL_StartTextInput()
	*  \sa SDL_StopTextInput()
	*/
	VAS_DECLSPEC bool isTextInputActive();

	/**
	*  \brief Stop receiving any text input events.
	*         This function will hide the on-screen keyboard if supported.
	*
	*  \sa SDL_StartTextInput()
	*  \sa SDL_HasScreenKeyboardSupport()
	*/
	VAS_DECLSPEC void stopTextInput();

	/**
	*  \brief Set the rectangle used to type Unicode text inputs.
	*         This is used as a hint for IME and on-screen keyboard placement.
	*
	*  \sa SDL_StartTextInput()
	*/
	VAS_DECLSPEC void setTextInputRect(sdl::Rect *rect);

	/**
	*  \brief Returns whether the platform has some screen keyboard support.
	*
	*  \return SDL_TRUE if some keyboard support is available else SDL_FALSE.
	*
	*  \note Not all screen keyboard functions are supported on all platforms.
	*
	*  \sa SDL_IsScreenKeyboardShown()
	*/
	VAS_DECLSPEC bool hasScreenKeyboardSupport();

	/**
	*  \brief Returns whether the screen keyboard is shown for given window.
	*
	*  \param window The window for which screen keyboard should be queried.
	*
	*  \return SDL_TRUE if screen keyboard is shown else SDL_FALSE.
	*
	*  \sa SDL_HasScreenKeyboardSupport()
	*/
	VAS_DECLSPEC bool isScreenKeyboardShown(Window& window);
}