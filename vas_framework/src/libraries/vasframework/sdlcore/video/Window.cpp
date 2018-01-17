#include "Window.hpp"
#include "../boolean_cast.hpp"

namespace sdl
{
	const int Window::windowPosCentred = SDL_WINDOWPOS_CENTERED;

	const uint32_t Window::Flags::fullscreen = 0x00000001;
	const uint32_t Window::Flags::opengl = 0x00000002;
	const uint32_t Window::Flags::shown = 0x00000004;
	const uint32_t Window::Flags::hidden = 0x00000008;
	const uint32_t Window::Flags::borderless = 0x00000010;
	const uint32_t Window::Flags::resizable = 0x00000020;
	const uint32_t Window::Flags::minimized = 0x00000040;
	const uint32_t Window::Flags::maximized = 0x00000080;
	const uint32_t Window::Flags::input_grabbed = 0x00000100;
	const uint32_t Window::Flags::input_focus = 0x00000200;
	const uint32_t Window::Flags::mouse_focus = 0x00000400;
	const uint32_t Window::Flags::fullscreen_desktop = (fullscreen | 0x00001000);
	const uint32_t Window::Flags::foreign = 0x00000800;
	const uint32_t Window::Flags::allow_highdpi = 0x00002000;
	const uint32_t Window::Flags::mouse_capture = 0x00004000;
	const uint32_t Window::Flags::always_on_top = 0x00008000;
	const uint32_t Window::Flags::skip_taskbar = 0x00010000;
	const uint32_t Window::Flags::utility = 0x00020000;
	const uint32_t Window::Flags::tooltip = 0x00040000;
	const uint32_t Window::Flags::popup_menu = 0x00080000;

	Window::Window(const std::string & title, const Point & position, const Point & size, uint32_t flags) :
		SDLComponentBase(SDL_CreateWindow(title.c_str(), position.x, position.y, size.x, size.y, flags), &defDeleter)
	{
	}

	Window::Window(SDL_Window * refInstance, SDLComponentBase::DeleterType deleter):
		SDLComponentBase(refInstance, deleter)
	{
	}

	Window::Window(const void * data):
		SDLComponentBase(SDL_CreateWindowFrom(data), &defDeleter)
	{
	}

	Window::Window(const Window & other):
		SDLComponentBase(other)
	{
	}

	Window::Window(Window && other):
		SDLComponentBase(std::move(other))
	{
	}

	Window::~Window()
	{
	}

	void Window::getBorderSize(int * top, int * left, int * bottom, int * right)
	{
		SDL_GetWindowBordersSize(&*this->componentInstance, top, left, bottom, right);
	}

	float Window::getBrightness()
	{
		return SDL_GetWindowBrightness(&*this->componentInstance);
	}

	void * Window::getData(const std::string & name)
	{
		return SDL_GetWindowData(&*this->componentInstance, name.c_str());
	}

	bool Window::getGammaRamp(uint16_t * red, uint16_t * green, uint16_t * bule)
	{
		return SDL_GetWindowGammaRamp(&*this->componentInstance, red, green, bule) == 0 ? true : false;
	}

	bool Window::getGrab()
	{
		return boolean_cast(SDL_GetWindowGrab(&*this->componentInstance));
	}

	uint32_t Window::getId()
	{
		return SDL_GetWindowID(&*this->componentInstance);
	}

	uint32_t Window::getFlags()
	{
		return SDL_GetWindowFlags(&*this->componentInstance);
	}

	Point Window::getMaximumSize()
	{
		Point maxSize;
		SDL_GetWindowMaximumSize(&*this->componentInstance, &maxSize.x, &maxSize.y);
		return Point();
	}

	Point Window::getMinimumSize()
	{
		Point minSize;
		SDL_GetWindowMinimumSize(&*this->componentInstance, &minSize.x, &minSize.y);
		return minSize;
	}

	bool Window::getOpacity(float & opacity)
	{
		return SDL_GetWindowOpacity(&*this->componentInstance, &opacity) == 0 ? true : false;
	}

	uint32_t Window::getPixelFormat()
	{
		return SDL_GetWindowPixelFormat(&*this->componentInstance);
	}

	Point Window::getPosition()
	{
		Point pos;
		SDL_GetWindowPosition(&*this->componentInstance, &pos.x, &pos.y);
		return pos;
	}

	Point Window::getSize()
	{
		Point size;
		SDL_GetWindowSize(&*this->componentInstance, &size.x, &size.y);
		return size;
	}

	SDL_Surface * Window::getSurface()
	{
		return SDL_GetWindowSurface(&*this->componentInstance);
	}

	std::string Window::getTitle()
	{
		return SDL_GetWindowTitle(&*this->componentInstance);
	}

	int Window::getWindowDisplayIndex()
	{
		return SDL_GetWindowDisplayIndex(&*this->componentInstance);
	}

	void Window::hide()
	{
		SDL_HideWindow(&*this->componentInstance);
	}

	void Window::maximize()
	{
		SDL_MaximizeWindow(&*this->componentInstance);
	}

	void Window::minimize()
	{
		SDL_MinimizeWindow(&*this->componentInstance);
	}

	void Window::raise()
	{
		SDL_RaiseWindow(&*this->componentInstance);
	}

	void Window::restore()
	{
		SDL_RestoreWindow(&*this->componentInstance);
	}

	void Window::setBordered(bool bordered)
	{
		SDL_SetWindowBordered(&*this->componentInstance, boolean_cast(bordered));
	}

	bool Window::setBrightness(float brightness)
	{
		return SDL_SetWindowBrightness(&*this->componentInstance, brightness) == 0 ? true : false;
	}

	void Window::setData(const std::string & name, void * userData)
	{
		SDL_SetWindowData(&*this->componentInstance, name.c_str(), userData);
	}

	bool Window::setGammaRamp(const uint16_t * red, const uint16_t * green, const uint16_t * bule)
	{
		return SDL_SetWindowGammaRamp(&*this->componentInstance, red, green, bule) == 0 ? true : false;
	}

	void Window::setGrab(bool grabbed)
	{
		SDL_SetWindowGrab(&*this->componentInstance, boolean_cast(grabbed));
	}

	void Window::setIcon(Surface & icon)
	{
		SDL_SetWindowIcon(&*this->componentInstance, static_cast<SDL_Surface*>(icon));
	}

	bool Window::setInputFocus()
	{
		return SDL_SetWindowInputFocus(&*this->componentInstance) == 0 ? true : false;
	}

	void Window::setMaximumSize(const Point & size)
	{
		SDL_SetWindowMaximumSize(&*this->componentInstance, size.x, size.y);
	}

	void Window::setMinimumSize(const Point & size)
	{
		SDL_SetWindowMinimumSize(&*this->componentInstance, size.x, size.y);
	}

	bool Window::setOpacity(float opacity)
	{
		return SDL_SetWindowOpacity(&*this->componentInstance, opacity) == 0 ? true: false;
	}

	void Window::setPosition(const Point & position)
	{
		SDL_SetWindowPosition(&*this->componentInstance, position.x, position.y);
	}

	void Window::setResizeAble(bool resizeable)
	{
		SDL_SetWindowResizable(&*this->componentInstance, boolean_cast(resizeable));
	}

	void Window::setSize(const Point & size)
	{
		SDL_SetWindowSize(&*this->componentInstance, size.x, size.y);
	}

	void Window::setTitle(const std::string & title)
	{
		SDL_SetWindowTitle(&*this->componentInstance, title.c_str());
	}

	void Window::setWindowDisplayMode(const SDL_DisplayMode * displayMode)
	{
		SDL_SetWindowDisplayMode(&*this->componentInstance, displayMode);
	}

	bool Window::setWindowFullscreen(uint32_t flags)
	{
		return SDL_SetWindowFullscreen(&*this->componentInstance, flags) == 0 ? true : false;
	}

	void Window::show()
	{
		SDL_ShowWindow(&*this->componentInstance);
	}

	bool Window::updateSurface()
	{
		return SDL_UpdateWindowSurface(&*this->componentInstance) == 0 ? true : false;
	}

	bool Window::updateSurfaceRects(std::vector<Rect>& rects)
	{
		std::vector<SDL_Rect> convertedRects;
		convertedRects.reserve(rects.size());
		for (auto rectsItr = rects.begin(); rectsItr != rects.end(); rectsItr++)
			convertedRects.push_back(static_cast<SDL_Rect>(*rectsItr));
		return updateSurfaceRects(convertedRects);
	}

	bool Window::updateSurfaceRects(const std::vector<SDL_Rect>& rects)
	{
		return SDL_UpdateWindowSurfaceRects(&*this->componentInstance, rects.data(), static_cast<int>(rects.size())) == 0 ? true : false;
	}

	Window& Window::operator=(const Window & other)
	{
		this->componentInstance = other.componentInstance;
		return *this;
	}

	Window& Window::operator=(Window && other)
	{
		this->componentInstance = std::move(other.componentInstance);
		return *this;
	}

	Window & Window::operator=(std::nullptr_t)
	{
		this->componentInstance = nullptr;
		return *this;
	}

	SDL_Window * Window::getGrabbedWindow()
	{
		return SDL_GetGrabbedWindow();
	}

	SDL_Window * Window::getWindowFromId(uint32_t id)
	{
		return SDL_GetWindowFromID(id);
	}

	bool Window::setWindowModalFor(SDL_Window * modalWindow, SDL_Window * parentWindow)
	{
		return SDL_SetWindowModalFor(modalWindow, parentWindow) == 0 ? true : false;
	}

	void Window::defDeleter(SDL_Window * instance)
	{
		SDL_DestroyWindow(instance);
	}

	void Window::notDeleteDeleter(SDL_Window * instance)
	{
		return;
	}
}