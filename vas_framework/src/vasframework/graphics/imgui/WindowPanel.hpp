//===========================================================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//===========================================================================================================
#pragma once
#include "../../sdlcore/video/Renderer.hpp"
#include "WindowBase.hpp"

namespace vas::imgui
{
	/**
	 * @ingroup imgui
	 * @{
	 */
	/**
	 * @brief Interface of window layer.
	 * 
	 * Tick and draw all windows that stored in this layer. Also determin how windows store and drawn.
	 */
	class WindowPanel
	{ /** @} */
	public:
		virtual ~WindowPanel() = 0 {}
		virtual void tick() = 0; /**< Tick all windows. */
		virtual void draw(sdl::Renderer* renderer) = 0; /**< Draw all windows. */

		virtual void addWindow(imgui::WindowBase* window) = 0; /**< Add window to panel. */
		virtual void removeWindow(imgui::WindowBase* window) = 0; /**< Remove window from panel. */
	};
}