//===========================================================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//===========================================================================================================
#pragma once
#include <vector>
#include "WindowPanel.hpp"
#include "WindowBase.hpp"

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

		void addWindow(imgui::WindowBase* instance) override;
		void removeWindow(imgui::WindowBase* instance) override;

		const std::vector<imgui::WindowBase*>& getWindowDeck() const;
	private:
		/**
		 * An array of vas::imgui::Window stroed.
		 * 
		 * ####Accessors
		 * -# const std::vector<imgui::Window*>& getWindowDeck() const
		 */
		std::vector<imgui::WindowBase*> windowDeck;
	};
}