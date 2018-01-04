#include <iostream>
#include "../libraries/VASFramework/base/Base.hpp"
#include "../libraries/VASFramework/util/CommonTools.hpp"
#include "../libraries/VASFramework/util/TextTools.hpp"
#include "../libraries/VASFramework/manager/SceneManager.hpp"
#include "../libraries/sreflex/IObjectFactory.hpp"

using namespace  std::string_literals;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR cmdLine, int cmdShow)
{
	try
	{
		vas::BaseAPI().init();
		vas::CommonToolsAPI().createConsole();
		
		vas::CommonToolsAPI().setAssistanceName(L"宮本サクラ"s);
		vas::CommonToolsAPI().messenger(L"你好"s);

		SDL_Point windowsize = vas::SDLFunctionBridge::newSDLPoint(640, 480);
		std::shared_ptr<SDL_Window> window = vas::SDLFunctionBridge::newSDLWindow(
			SDL_CreateWindow(
				u8"你好! SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowsize.x, windowsize.y, SDL_WINDOW_SHOWN
			)
		);

		if (window == nullptr) throw std::runtime_error(SDL_GetError());

		std::shared_ptr<SDL_Renderer> renderer = vas::SDLFunctionBridge::newSDLRenderer(
			SDL_CreateRenderer(window.get(), -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED)
		);
		if (renderer == nullptr) throw std::runtime_error(SDL_GetError());

		vas::CommonToolsAPI().messenger(L"正在初始化框架"s);
		vas::BaseAPI().setMainWindow(std::move(window));
		vas::BaseAPI().setMainRenderer(std::move(renderer));
		vas::BaseAPI().setRenderLogicSize(windowsize);
		vas::CommonToolsAPI().messenger(L"初始化完毕，正在启动框架"s);

		std::shared_ptr<sreflex::IObjectFactory> objectFactory = std::make_shared<sreflex::IObjectFactory>();
		vas::SceneManagerAPI().call(std::dynamic_pointer_cast<vas::SceneBase>(objectFactory->createObject("scene::TiledMapTest")));
		
		vas::BaseAPI().startGameLoop();
		vas::CommonToolsAPI().messenger(L"执行完毕，退出\n拜拜"s);
		vas::BaseAPI().exitFramework();
	}
	catch (const std::exception& e)
	{
		vas::CommonToolsAPI().messenger(vas::str_cast<std::wstring>(e.what()), vas::CommonTools::Messtype::error);
		vas::BaseAPI().exitFramework();
		return -1;
	}

	return NULL;
}