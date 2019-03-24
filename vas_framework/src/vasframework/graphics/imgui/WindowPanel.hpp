#pragma once
#include "../../sdlcore/video/Renderer.hpp"
#include "Window.hpp"

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
		virtual ~WindowPanel() = 0;
		virtual void tick() = 0; /**< Tick all windows. */
		virtual void draw(sdl::Renderer* renderer) = 0; /**< Draw all windows. */

		virtual void addWindow(imgui::Window* window) = 0; /**< Add window to panel. */
		virtual void removeWindow(imgui::Window* window) = 0; /**< Remove window from panel. */
	};
}