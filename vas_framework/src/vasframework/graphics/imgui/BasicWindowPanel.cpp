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

	void BasicWindowPanel::addWindow(imgui::Window * instance)
	{
		windowDeck.push_back(instance);
	}

	void BasicWindowPanel::removeWindow(imgui::Window * instance)
	{
		auto itr = std::find(windowDeck.begin(), windowDeck.end(), instance);
		windowDeck.erase(itr);
	}
	
	const std::vector<imgui::Window*>& BasicWindowPanel::getWindowDeck() const
	{
		return windowDeck;
	}
}