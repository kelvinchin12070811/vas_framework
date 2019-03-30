//===========================================================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//===========================================================================================================
#pragma once
#include "../Camera.hpp"
#include "../../sdlcore/video/Renderer.hpp"

namespace vas::imgui
{
	class WindowBase;
	/**
	 * @ingroup imgui
	 * @{
	 */
	/**
	 * @brief Style of WindowBase.
	 *
	 * The WindowStyle abstract class determin how window instance will be drawn.
	 */
	class WindowStyle
	{ /** @} */
	public:
		virtual ~WindowStyle() = 0 {}
		/**
		 * Apply window style to the selected window
		 * @param[in] win WindowBase instance to apply.
		 */
		virtual void applyStyle(WindowBase* win) { this->win = win; }
		virtual void tick() = 0; /**< Tick the content of the WindowStyle. */
		virtual void draw(sdl::Renderer* renderer, Camera* camera) = 0; /**< Draw the content of the WindowStyle. */

	protected:
		WindowBase* win{ nullptr };
	};
}