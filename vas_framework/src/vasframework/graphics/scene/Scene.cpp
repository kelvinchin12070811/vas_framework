//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "Scene.hpp"
#include "../../manager/ScreenManager.hpp"

namespace vas
{
	void Scene::tick()
	{
		layer.tick();
	}

	void Scene::draw()
	{
		layer.draw();
	}

	void Scene::beforeTerminate()
	{
		return;
	}

	void Scene::afterTerminate()
	{
		return;
	}

	void Scene::beforeSceneCall()
	{
		return;
	}

	void Scene::afterSceneCall()
	{
		return;
	}

	void Scene::closeGuiPanel()
	{
		if (!guiPanel) return;
		guiPanel = nullptr;
	}

	imgui::WindowPanel * Scene::getGuiPanel()
	{
		return guiPanel.get();
	}

	bool Scene::isGUIPanelOpened() const
	{
		return guiPanel != nullptr;
	}

	void Scene::pause()
	{
		paused = true;
	}
	
	void Scene::resume()
	{
		paused = false;
	}
	
	bool Scene::isPaused()
	{
		return paused;
	}
}