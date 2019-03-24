#pragma once
#include "../Camera.hpp"
#include "../../sdlcore/video/Renderer.hpp"

namespace vas::imgui
{
	/**
	 * @ingroup imgui
	 * @{
	 */
	/**
	 * @brief Style of Window.
	 *
	 * The WindowStyle abstract class determin how window instance will be drawn.
	 */
	class WindowStyle
	{ /** @} */
	public:
		virtual ~WindowStyle() = 0;
		virtual void tick() = 0; /**< Tick the content of the WindowStyle. */
		virtual void draw(sdl::Renderer* renderer, Camera* camera) = 0; /**< Draw the content of the WindowStyle. */

		void setWinRect(sdl::Rect* winRect) { this->winRect = winRect; }
	protected:
		sdl::Rect* winRect{ nullptr };
	};
}