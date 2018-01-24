#pragma once
#include <vector>
#include <SDL.h>
#include "../../VASConfig.hpp"
#include "../SDLComponentBase.hpp"
#include "Surface.hpp"
#include "../Math.hpp"

namespace sdl
{
	class VAS_DECLSPEC Window : public SDLComponentBase<SDL_Window, Window>
	{
	public:
		Window();
		Window(const std::string& title, const Point& position, const Point& size, uint32_t flags);
		Window(const std::string& title, const Point& size, uint32_t flags);
		explicit Window(SDL_Window* refInstance, SDLComponentBase::DeleterType deleter = &Window::notDeleteDeleter);
		explicit Window(const void* data);
		Window(const Window& other);
		Window(Window&& other);
		~Window();

		void getBorderSize(int* top, int* left, int* bottom, int* right);
		float getBrightness();
		void* getData(const std::string& name);
		bool getGammaRamp(uint16_t* red, uint16_t* green, uint16_t* bule);
		bool getGrab();
		uint32_t getId();
		uint32_t getFlags();
		Point getMaximumSize();
		Point getMinimumSize();
		bool getOpacity(float& opacity);
		uint32_t getPixelFormat();
		Point getPosition();
		Point getSize();
		SDL_Surface* getSurface();
		std::string getTitle();
		int getWindowDisplayIndex();

		void hide();

		void maximize();
		void minimize();

		void raise();
		void restore();

		void setBordered(bool bordered);
		bool setBrightness(float brightness);
		void setData(const std::string& name, void* userData);
		bool setGammaRamp(const uint16_t* red, const uint16_t* green, const uint16_t* bule);
		void setGrab(bool grabbed);
		void setIcon(Surface& icon);
		bool setInputFocus();
		void setMaximumSize(const Point& size);
		void setMinimumSize(const Point& size);
		bool setOpacity(float opacity);
		void setPosition(const Point& position);
		void setResizeAble(bool resizeable);
		void setSize(const Point& size);
		void setTitle(const std::string& title);
		void setWindowDisplayMode(const SDL_DisplayMode* displayMode);
		//return true if success, original: SDL_SetWindowFullscreen(SDL_Window*, Uint32)
		bool setWindowFullscreen(uint32_t flags);

		void show();

		bool updateSurface();
		bool updateSurfaceRects(std::vector<Rect>& rects);
		bool updateSurfaceRects(const std::vector<SDL_Rect>& rects);

		Window& operator=(const Window& other);
		Window& operator=(Window&& other);
		Window& operator=(std::nullptr_t);

		static SDL_Window* getGrabbedWindow();
		static SDL_Window* getWindowFromId(uint32_t id);
		static bool setWindowModalFor(SDL_Window* modalWindow, SDL_Window* parentWindow);
		
		struct DefultValues
		{
			static const int posCentered = SDL_WINDOWPOS_CENTERED;
			static const int posUndefine = SDL_WINDOWPOS_UNDEFINED;
		};
		struct Flags
		{
			/* !!! FIXME: change this to name = (1<<x). */
			/**< fullscreen window */
			static const uint32_t fullscreen;
			/**< window usable with OpenGL context */
			static const uint32_t opengl;
			/**< window is visible */
			static const uint32_t shown;
			/**< window is not visible */
			static const uint32_t hidden;
			/**< no window decoration */
			static const uint32_t borderless;
			/**< window can be resized */
			static const uint32_t resizable;
			/**< window is minimized */
			static const uint32_t minimized;
			/**< window is maximized */
			static const uint32_t maximized;
			/**< window has grabbed input focus */
			static const uint32_t input_grabbed;
			/**< window has input focus */
			static const uint32_t input_focus;
			/**< window has mouse focus */
			static const uint32_t mouse_focus;
			static const uint32_t fullscreen_desktop;
			/**< window not created by SDL */
			static const uint32_t foreign;
			/**< window should be created in high-DPI mode if supported */
			static const uint32_t allow_highdpi;
			/**< window has mouse captured (unrelated to INPUT_GRABBED) */
			static const uint32_t mouse_capture;
			/**< window should always be above others */
			static const uint32_t always_on_top;
			/**< window should not be added to the taskbar */
			static const uint32_t skip_taskbar;
			/**< window should be treated as a utility window */
			static const uint32_t utility;
			/**< window should be treated as a tooltip */
			static const uint32_t tooltip;
			/**< window should be treated as a popup menu */
			static const uint32_t popup_menu;
		};

		static void VAS_PROTOTYPE_DEFINE_DEF_DELETER(SDL_Window);
	};
}