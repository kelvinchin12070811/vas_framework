//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <vector>
#include <SDL.h>
#include "../../VASConfig.hpp"
#include "../SDLComponentBase.hpp"
#include "Surface.hpp"
#include "../Math.hpp"

namespace vas::sdl
{
	/**
	 * @ingroup sdl_basic
	 * @{
	 */
	/** @brief The window that display everything. */
	class VAS_DECLSPEC Window
	{ /** @} */
	public:
		Window(); /**< Create empty window. */
		/**
		 * Create new window instance.
		 * @param[in] title Title of the window.
		 * @param[in] position Position of the window.
		 * @param[in] size Size of the window.
		 * @param[in] flags Flags of the window.
		 */
		Window(const std::string& title, const Point& position, const Point& size, uint32_t flags);
		/**
		 * Create new window instance at center of the primary screen.
		 * @param[in] title Title of window.
		 * @param[in] size Size of the window.
		 * @param[in] flags Flags of the window.
		 */
		Window(const std::string& title, const Point& size, uint32_t flags);
		/**
		 * Reference to a raw SDL_Window.
		 * @param[in] refInstance Instance to reference.
		 * @param[in] owner Determine if the component own the instance or not. Handle memory management automaticaly if true.
		 */
		explicit Window(SDL_Window* refInstance, bool owner = false);
		/**
		 * Create window from data.
		 * @param[in] data window data.
		 */
		explicit Window(const void* data);

		/**
		 * Get the border size of the window.
		 * @param[in] top Output of top position.
		 * @param[in] left Output of left position.
		 * @param[in] bottom Output of bottom position.
		 * @param[in] right Output of right position.
		 */
		void getBorderSize(int* top, int* left, int* bottom, int* right);
		float getBrightness(); /**< Get the brightness of the window. */
		void* getData(const std::string& name); /**< Get user data of the window. */
		/**
		 * Get gamma ramp.
		 * @return true if success.
		 */
		bool getGammaRamp(uint16_t* red, uint16_t* green, uint16_t* bule);
		bool getGrab(); /**< Get grab. */
		uint32_t getId(); /**< Get ID of the window. */
		uint32_t getFlags(); /**< Get flags of the window. */
		Point getMaximumSize(); /**< Get maximum size of the window. */
		Point getMinimumSize(); /**< Get minimum size of the window. */
		/**
		 * Get opacity of window.
		 * @return true if success.
		 */
		bool getOpacity(float& opacity);
		uint32_t getPixelFormat(); /**< Get pixel format of the window. */
		Point getPosition(); /**< Get position of the window. */
		Point getSize(); /**< Get size of the window. */
		SDL_Surface* getSurface(); /**< Get the window surface. */
		std::string getTitle(); /**< Get the window title. */
		int getWindowDisplayIndex(); /**< Get display index of window. */

		void hide(); /**< Hide the window. */

		void maximize(); /**< Maximize the window. */
		void minimize(); /**< Minimize the window. */

		void raise(); /**< Raise the window. */
		void restore(); /**< Restore the window. */

		void setBordered(bool bordered); /**< Set the if window is bordered or not. */
		/**
		 * Set brightness of the window.
		 * @return true if success.
		 */
		bool setBrightness(float brightness);
		void setData(const std::string& name, void* userData); /**< Set user data of the window. */
		bool setGammaRamp(const uint16_t* red, const uint16_t* green, const uint16_t* bule); /**< Set gama ramp of window. */
		void setGrab(bool grabbed); /**< Set grab. */
		void setIcon(Surface& icon); /**< Set window icon. */
		/**
		 * Set input focus to this window.
		 * @return true if success.
		 * @warning This function is not recommended by the official SDL documentation.
		 */
		bool setInputFocus();
		void setMaximumSize(const Point& size); /**< Set maximum size of the window. */
		void setMinimumSize(const Point& size); /**< Set minimum size of the windwo. */
		bool setOpacity(float opacity); /**< Set opacity of the window. */
		void setPosition(const Point& position); /**< Set position of the window. */
		void setResizeAble(bool resizeable); /**< Set if the window is resizeable or not. */
		void setSize(const Point& size); /**< Set the size of the window. */
		void setTitle(const std::string& title); /**< Set the title of the window. */
		void setWindowDisplayMode(const SDL_DisplayMode* displayMode); /**< Set window display mode. */
		/**
		 * Toggle window's fullscreen state
		 * @return true if success.
		 */
		bool setWindowFullscreen(uint32_t flags);

		void show(); /**< Show the window. */

		/**
		 * Update the window surface.
		 * @return true if success.
		 */
		bool updateSurface();
		/**
		 * Update the window surface rects.
		 * @return true if success.
		 */
		bool updateSurfaceRects(std::vector<Rect>& rects);
		/**
		 * Update the window surface rects. (rvalue overloaded)
		 * @return true if success.
		 */
		bool updateSurfaceRects(const std::vector<SDL_Rect>& rects);

		bool isNull();
		/**
		 * @name Overloaded operators
		 * @{
		 */
		bool operator==(const Window& other); /**< Compare if two instances are equal. */
		bool operator!=(const Window& other); /**< Compare if two instances are not equal. */
		bool operator==(NullComponent_t); /**< Compare if this instance is equal to nullcomponent. */
		bool operator!=(NullComponent_t); /**< Compare if this instance is not equal to nullcomponent. */

		Window& operator=(NullComponent_t); /**< Destroy by set to null. */
		explicit operator SDL_Window*();
		/** @} */
		void destroy(); /**< Destroy window */
		
		static SDL_Window* getGrabbedWindow(); /**< Get the grabbed window.
																					 * @retval SDL_Window Raw SDL_Window instance of grabbed window. */
		/**
		 * Get window from id
		 * @retval SDL_Window Raw instance of window.
		 */
		static SDL_Window* getWindowFromId(uint32_t id);
		/**
		 * Set window modal for this window.
		 * @return true if success.
		 */
		static bool setWindowModalFor(SDL_Window* modalWindow, SDL_Window* parentWindow);
		
		/** @brief Default values set of Window. */
		struct DefultValues
		{
			static const int posCentered = SDL_WINDOWPOS_CENTERED; /**< Window positioned at center of the screen. */
			static const int posUndefine = SDL_WINDOWPOS_UNDEFINED; /**< Random position the window. */
		};

		/** @brief Flags to initialize the Window. */
		struct Flags
		{
			/* !!! FIXME: change this to name = (1<<x). */
			static const uint32_t fullscreen; /**< fullscreen window */
			static const uint32_t opengl; /**< window usable with OpenGL context */
			static const uint32_t shown; /**< window is visible */
			static const uint32_t hidden; /**< window is not visible */
			static const uint32_t borderless; /**< no window decoration */
			static const uint32_t resizable; /**< window can be resized */
			static const uint32_t minimized; /**< window is minimized */
			static const uint32_t maximized; /**< window is maximized */
			static const uint32_t input_grabbed; /**< window has grabbed input focus */
			static const uint32_t input_focus; /**< window has input focus */
			static const uint32_t mouse_focus; /**< window has mouse focus */
			static const uint32_t fullscreen_desktop; /**< fullscreen window with desktop resolution. */
			static const uint32_t foreign; /**< window not created by SDL */
			static const uint32_t allow_highdpi; /**< window should be created in high-DPI mode if supported */
			static const uint32_t mouse_capture; /**< window has mouse captured (unrelated to INPUT_GRABBED) */
			static const uint32_t always_on_top; /**< window should always be above others */
			static const uint32_t skip_taskbar; /**< window should not be added to the taskbar */
			static const uint32_t utility; /**< window should be treated as a utility window */
			static const uint32_t tooltip; /**< window should be treated as a tooltip */
			static const uint32_t popup_menu; /**< window should be treated as a popup menu */
		};

		std::shared_ptr<SDL_Window> componentInstance;
	};
}