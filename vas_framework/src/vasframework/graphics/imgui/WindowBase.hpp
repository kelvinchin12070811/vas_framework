//===========================================================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//===========================================================================================================
#pragma once
#include <memory>
#include "WindowStyle.hpp"
#include "../Camera.hpp"
#include "../../sdlcore/video/Renderer.hpp"
#include "../../sdlcore/Math.hpp"

namespace vas
{
	class Scene;
}

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
	 * @brief Abstract class of all WindowBase objects.
	 *	 
	 * WindowBase is an non-copyable and non-movealbe objcet that drawn on top of all content of screen but
	 * bellow above screen overlay layer.
	 */
	class VAS_DECLSPEC WindowBase
	{ /** @} */
	public:
		/**
		 * Create window
		 * @param[in] winRect Rect of the window.
		 * @param[in] winStyle Style of the window.
		 * @param[in] parentScene Scene that contain this window, use current scene if nullptr.
		 * @throw std::logic_error if unable to locate parent scene.
		 * @note This constructor will open a new vas::imgui::BasicWindowPanel if no WindowPanel is opened on
		 * the parent scene.
		 */
		WindowBase(sdl::Rect winRect, std::unique_ptr<WindowStyle> winStyle, Scene* parentScene = nullptr);
		WindowBase(const WindowBase&) = delete;
		WindowBase(WindowBase&&) = delete;
		virtual ~WindowBase();
		virtual void tick(); /**<Tick window contents.*/
		virtual void draw(sdl::Renderer* renderer, Camera* camera); /**< Draw window contents. */

		const sdl::Rect& getWinRect() const; /**< Get the rect of the window. */
		void setWinRect(sdl::Rect rect);  /**< Set the rect of the window. */

		Scene* getSceneBasedOn(); /**< Get parent scene. */

		WindowBase& operator=(const WindowBase&) = delete;
		WindowBase& operator=(WindowBase&&) = delete;
	protected:
		std::unique_ptr<WindowStyle> winStyle; /**< Style of the window use to draw. */
		sdl::Rect winRect; /**< Rect of the window. */
		Scene* sceneBasedOn{ nullptr };
	};
}