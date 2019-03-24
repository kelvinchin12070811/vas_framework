//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <exception>
#include <boost/signals2.hpp>
#include "../sdlcore/SDLCore.hpp"

namespace vas
{
	/**
	 * @ingroup managers
	 * @{
	 */
	/** @brief Manager that manage the standard input output of the keyboard and mouse. */
	class VAS_DECLSPEC InputManager
	{ /** @} */
	public:
		static InputManager& getInstance(); /**< Get singletone instance of the InputManager. */

		void init(sdl::Event* ev);
		void tick();

		/**
		 * Check if a key is pressed.
		 * @param key vas::sdl::Scancode of key identifier to a key to check.
		 * @return true if key is pressed, false otherwise.
		 */
		bool isKeyTriggered(sdl::Scancode key);
		/**
		 * Check if a set of key is pressed.
		 * @param keys An array of keys to test.
		 * @return true if all of the keys is pressed.
		 */
		bool isKeysTriggered(std::initializer_list<sdl::Scancode> keys);
		
	public: //Setters
		void __setMousePosition(sdl::Point value);
		void __setRealMousePosition(sdl::Point value);
	public: //Getters
		sdl::Point getMousePosition();
		sdl::Point getRealMousePosition();
		sdl::Point getMousePositionRaw(); /**< Get raw position of the mouse pointer with SDL_GetMouseState.*/
		uint32_t getMouseState(); /**< Get the state of the mouse. */

	public: // Public members
		/**
		 * @name Signals
		 * @{
		 */
		/**
		 * Fired when a key is pressed.
		 * @param[in] sdl::Keycode Key that triggered the event.
		 */
		boost::signals2::signal<void(sdl::Keycode)> KeyPressed;
		/**
		 * Fired when a key is releaseed.
		 * @param[in] sdl::Keycode Key that triggered the event.
		 */
		boost::signals2::signal<void(sdl::Keycode)> KeyReleased;
		/**
		 * Fired when a mouse button is pressed. Take two parameters
		 * @param[in] sdl::MouseButtonIndex Index of the mouse button.
		 * @param[in] sdl::Point Position of the mouse pointer.
		 */
		boost::signals2::signal<void(sdl::MouseButtonIndex, sdl::Point)> MouseButtonPressed;
		/**
		 * Fired when a mouse button is pressed. Take two parameters
		 * @param[in] sdl::MouseButtonIndex Index of the mouse button.
		 * @param[in] sdl::Point Position of the mouse pointer.
		 */
		boost::signals2::signal<void(sdl::MouseButtonIndex, sdl::Point)> MouseButtonReleased;
		/**
		 * Fired when mouse moved.
		 * @param int x position of the mouse pointer.
		 * @param int y position of the mouse pointer.
		 */
		boost::signals2::signal<void(int, int)> MouseMoved;
		/**
		 * Fired when mouse wheel is scrolled.
		 * @param sdl::MouseWheelDirection Direction of the mouse wheel scrolled
		 * @param sdl::Point Amount of user scrolled. (x positive to right, negative to left; y positive away from the
		 * user, negative toward the user.)
		 */
		boost::signals2::signal<void(sdl::MouseWheelDirection, sdl::Point)> MouseWheelMoved;
		/** @} */
	private:
		InputManager();
		~InputManager();
		sdl::Event* ev{ nullptr };
		const uint8_t* keyState{ nullptr };
		/**
		 * Current mouse position.
		 * 
		 * ####Accessors
		 * -# sdl::Point getMousePosition()
		 */
		sdl::Point currentMousePosition;
		/**
		 * Current mouse position on the system (desktop).
		 * 
		 * ####Accessors
		 * -# sdl::Point getRealMousePosition()
		 */
		sdl::Point currentRealMousePosition;
	};
}