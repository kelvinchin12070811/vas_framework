//===========================================================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//===========================================================================================================
#include "BasicWindowPanel.hpp"

namespace vas::imgui
{
	BasicWindowPanel::BasicWindowPanel()
	{
	}

	void BasicWindowPanel::tick()
	{
		for (auto&& itr : windowDeck)
			if (itr != nullptr) itr->tick();
	}

	void BasicWindowPanel::draw(sdl::Renderer * renderer)
	{
		for (auto&& itr : windowDeck)
			if (itr != nullptr) itr->draw(renderer, nullptr);
	}

	void BasicWindowPanel::addWindow(imgui::WindowBase * instance)
	{
		windowDeck.push_back(instance);
	}

	void BasicWindowPanel::removeWindow(imgui::WindowBase * instance)
	{
		auto itr = std::find(windowDeck.begin(), windowDeck.end(), instance);
		windowDeck.erase(itr);
	}
	
	const std::vector<imgui::WindowBase*>& BasicWindowPanel::getWindowDeck() const
	{
		return windowDeck;
	}
}