#pragma once
#include <vector>
#include "WindowPanel.hpp"
#include "Window.hpp"

namespace vas::imgui
{
	/**
	 * @ingroup imgui
	 * @{
	 */

	/**
	 * @brief Basic implementation of WindowPanel.
	 */
	class BasicWindowPanel : public WindowPanel
	{ /**@} */
	public:
		/**
		 * Create new instance.
		 */
		BasicWindowPanel();

		void tick() override;
		void draw(sdl::Renderer* renderer = nullptr) override;

		void addWindow(imgui::Window* instance) override;
		void removeWindow(imgui::Window* instance) override;

		const std::vector<imgui::Window*>& getWindowDeck() const;
	private:
		/**
		 * An array of vas::imgui::Window stroed.
		 * 
		 * ####Accessors
		 * -# const std::vector<imgui::Window*>& getWindowDeck() const
		 */
		std::vector<imgui::Window*> windowDeck;
	};
}