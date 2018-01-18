#include "../libraries/vasframework/sdlcore/SDLCore.hpp"
#include <exception>
#include <SDL_image.h>

int main(int argc, char** argv)
{
	sdl::init(sdl::InitFlags::everything);
	//sdl::Window mainWindow("hello world", sdl::Point(sdl::Window::windowPosCentred, sdl::Window::windowPosCentred), sdl::Point(640, 480), sdl::Window::Flags::shown);
	sdl::Window mainWindow;
	mainWindow = sdl::createComponent<sdl::Window>(SDL_CreateWindow("test", 100, 100, 640, 480, SDL_WINDOW_SHOWN));
	if (mainWindow == nullptr)
		throw std::runtime_error(sdl::getError());

	sdl::Renderer mainRenderer(mainWindow, sdl::Renderer::defIndex, sdl::Renderer::RendererFlags::accelerated);
	if (mainRenderer == nullptr)
		throw std::runtime_error(sdl::getError());

	mainWindow.show();

	sdl::Surface tempSurface = sdl::createComponent<sdl::Surface>(IMG_Load(u8"assets/textures/639111.jpg"));
	if (tempSurface == nullptr) throw std::runtime_error(sdl::getError());

	sdl::Texture testTexture(mainRenderer, tempSurface);
	if (testTexture == nullptr) throw std::runtime_error(sdl::getError());
	tempSurface.destroy();

	sdl::Rect testRect;
	testTexture.queryTexture(nullptr, nullptr, &testRect.w, &testRect.h);

	bool exec = true;
	sdl::Event ev;
	while (exec)
	{
		while (ev.pollEvent())
		{
			if (ev.is(sdl::EventType::quit))
			{
				exec = false;
				break;
			}
			else if (ev.is(sdl::EventType::keydown))
			{
				if (ev.key().keysym.sym == SDLK_ESCAPE)
					ev.pushEvent(sdl::EventType::quit);
			}
		}
		if (exec == false) break;
		mainRenderer.clear();
		mainRenderer.copy(testTexture, &testRect, &testRect);
		mainRenderer.present();
	}

	mainWindow = nullptr;
	mainRenderer = nullptr;
	sdl::quit();

	return 0;
}