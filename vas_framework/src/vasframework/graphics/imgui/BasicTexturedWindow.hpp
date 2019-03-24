#pragma once
#include <string>
#include "WindowStyle.hpp"
#include "../sprites/Sprite.hpp"

namespace vas::imgui
{
	/**
	 * @ingroup imgui
	 * @{
	 */

	/**
	  * @brief Simple texturlized window style
	 * 	  
	 * BasicTexturedWindow is one of the WindowStyle that draw a single texture of background as window. All of
	 * window border and panel are determined by the texture.
	 */
	class BasicTexturedWindow : public WindowStyle
	{ /** @} */
	public:
		/**
		 * Create new instance
		 * @param[in] spriteId Id of sprite to use, use as file path if texture not exist in cache.
		 * @param[in] offset Offset of the texture from the top-left position of the window.
		 * @throw vas::sdl::SDLCoreException if creation of sprite failed.
		 */
		BasicTexturedWindow(const std::string& spriteId, sdl::Point offset);
		void tick() override;
		void draw(sdl::Renderer* renderer, Camera* camera) override;
	private:
		std::unique_ptr<Sprite> background;
		sdl::Point offset;
	};
}