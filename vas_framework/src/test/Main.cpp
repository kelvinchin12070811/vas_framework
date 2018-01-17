#include "../libraries/vasframework/sdlcore/SDLCore.hpp"
#include <exception>

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

		mainRenderer.setRenderDrawColor(255, 255, 255, 255);
		//mainRenderer.drawLines(std::vector<sdl::Point>({ sdl::Point(0, 0), sdl::Point(100, 100), sdl::Point(100, 200), sdl::Point(200, 100) }));
		sdl::Rect rect(100, 100, 100, 100);
		mainRenderer.fillRect(&rect);
		mainRenderer.present();
	}

	mainWindow = nullptr;
	mainRenderer = nullptr;
	sdl::quit();

	return 0;
}