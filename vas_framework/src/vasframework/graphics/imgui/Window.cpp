#include "Window.hpp"
#include "../../manager/SceneManager.hpp"

namespace vas::imgui
{
	Window::Window(sdl::Rect winRect, std::unique_ptr<WindowStyle> winStyle, Scene* parentScene):
		winRect(std::move(winRect)), winStyle(std::move(winStyle)), sceneBasedOn(parentScene)
	{
		if (sceneBasedOn == nullptr)
		{
			sceneBasedOn = SceneManager::getInstance().current().get();
			if (sceneBasedOn == nullptr)
				throw std::logic_error{ "Assertion failed: Parrent scene was not initialized." };
		}
		if (!sceneBasedOn->isGUIPanelOpened())
			sceneBasedOn->openGuiPanel();

		sceneBasedOn->getGuiPanel()->addWindow(this);
		this->winStyle->setWinRect(&this->winRect);
	}

	Window::~Window()
	{
		sceneBasedOn->getGuiPanel()->removeWindow(this);
	}

	void Window::tick()
	{
		if (winStyle) winStyle->tick();
	}

	void Window::draw(sdl::Renderer* renderer, Camera* camera)
	{
		if (winStyle) winStyle->draw(renderer, camera);
	}
}