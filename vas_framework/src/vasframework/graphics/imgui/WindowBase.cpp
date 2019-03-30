//===========================================================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//===========================================================================================================
#include "WindowBase.hpp"
#include "../../manager/SceneManager.hpp"
#include "../scene/Scene.hpp"

namespace vas::imgui
{
	WindowBase::WindowBase(sdl::Rect winRect, std::unique_ptr<WindowStyle> winStyle, Scene* parentScene):
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

		this->winStyle->applyStyle(this);
		sceneBasedOn->getGuiPanel()->addWindow(this);
	}

	WindowBase::~WindowBase()
	{
		sceneBasedOn->getGuiPanel()->removeWindow(this);
	}

	void WindowBase::tick()
	{
		if (winStyle) winStyle->tick();
	}

	void WindowBase::draw(sdl::Renderer* renderer, Camera* camera)
	{
		if (winStyle) winStyle->draw(renderer, camera);
	}

	const sdl::Rect & WindowBase::getWinRect() const
	{
		return winRect;
	}

	void WindowBase::setWinRect(sdl::Rect rect)
	{
		winRect = std::move(rect);
	}

	Scene * WindowBase::getSceneBasedOn()
	{
		return sceneBasedOn;
	}
}