#include <Windows.h>
#include "../libraries/vasframework/base/Base.hpp"
#include "../libraries/vasframework/manager/SceneManager.hpp"
#include "../libraries/vasframework/util/TextTools.hpp"
#include "scenes/MainScene.hpp"

//int main(int argc, char** argv)
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR cmdLine, int cmdShow)
{
	AllocConsole();
	freopen("CONIN$", "r+t", stdin);
	freopen("CONIN$", "w+t", stdout);

	try
	{
		vas::Base::getInstance().init();
		sdl::Window mainWindow("hello world", sdl::Point(640, 480), sdl::Window::Flags::shown);
		if (mainWindow == nullptr)
			throw sdl::SDLCoreException();

		sdl::Renderer mainRenderer(mainWindow, sdl::Renderer::defIndex, sdl::Renderer::RendererFlags::accelerated);
		if (mainRenderer == nullptr)
			throw sdl::SDLCoreException();

		vas::Base::getInstance().Window() = std::move(mainWindow);
		vas::Base::getInstance().Renderer() = std::move(mainRenderer);

		vas::SceneManager::getInstance().call(std::make_shared<scene::MainScene>());
		vas::Base::getInstance().startGameLoop();
		vas::Base::getInstance().cleanAndQuit();
	}
	catch (const std::exception& e)
	{
		vas::Base::getInstance().cleanAndQuit();
		MessageBeep(MB_ICONERROR);
		MessageBox(nullptr, vas::TextTools::stows(e.what()).c_str(), L"Unhandled Exception Occur", MB_ICONERROR);
		return -1;
	}

	return 0;
}