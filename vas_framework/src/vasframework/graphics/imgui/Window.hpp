#pragma once
#include <memory>
#include "WindowStyle.hpp"
#include "../Camera.hpp"
#include "../../sdlcore/video/Renderer.hpp"
#include "../../sdlcore/Math.hpp"
#include "../scene/Scene.hpp"

/**
 * @ingroup graphics
 * @{
 */
/**
 * @defgroup imgui Basic IMGUI Library
 * @brief The basic implementation of IMGUI.
 */
/** @} */
namespace vas::imgui
{
	/**
	 * @ingroup imgui
	 * @{
	 */
	/**
	 * @brief Abstract class of all Window objects.
	 *	 
	 * Window is an non-copyable and non-movealbe objcet that drawn on top of all content of screen but bellow
	 * above screen overlay layer.
	 */
	class Window
	{ /** @} */
	public:
		/**
		 * Create window
		 * @param[in] winRect Rect of the window.
		 * @param[in] winStyle Style of the window.
		 * @param[in] parentScene Scene that contain this window, use current scene if nullptr.
		 * @throw std::logic_error if unable to locate parent scene.
		 * @note This constructor will open a new vas::imgui::BasicWindowPanel if no WindowPanel is opened on the
		 * parent scene.
		 */
		Window(sdl::Rect winRect, std::unique_ptr<WindowStyle> winStyle, Scene* parentScene = nullptr);
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		virtual ~Window();
		virtual void tick(); /**<Tick window contents.*/
		virtual void draw(sdl::Renderer* renderer, Camera* camera); /**< Draw window contents. */

		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;
	protected:
		std::unique_ptr<WindowStyle> winStyle; /**< Style of the window use to draw. */
		sdl::Rect winRect; /**< Rect of the window. */
		Scene* sceneBasedOn{ nullptr };
	};
}