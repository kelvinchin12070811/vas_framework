//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include "Sprite.hpp"

namespace vas
{
	/**
	 * @ingroup graphics
	 * @{
	 */
	/**
	 * @brief A set of sprites in a collection of a single texture.
	 * 
	 * The SpriteSheet is a set of sprites located in a single texture with specified size (width and height).
	 */
	class VAS_DECLSPEC SpriteSheet : public Sprite
	{ /** @} */
	public:
		SpriteSheet() = default;
		/**
		 * Create an new SpriteSheet.
		 * @param[in] file Unique ID or file name of the texture.
		 * @param[in] tileSize Size of the individual tile.
		 * @param[in] position Position of the tilesets, not used.
		 * @param[in] origin Origin (center point) of the tilesets, not used.
		 * @param[in] bfMode BufferMode that used.
		 * @throw vas::sdl::SDLCoreException if creation of texture failed.
		 */
		SpriteSheet(const std::string& file, const sdl::Point& tileSize, const Vector2& position = Vector2(),
			const sdl::Point& origin = sdl::Point(), BufferMode bfMode = BufferMode::buffered);
		SpriteSheet(const SpriteSheet&) = delete;
		SpriteSheet(SpriteSheet&&) = delete;

		/**
		 * tick this DrawAble object.
		 * @note this function have no function since ticking the entire sprite sheets make no sense.
		 */
		void tick() override;
		/**
		 * draw this DrawAble object.
		 * @note this function have no use since drawing the entire sprite sheets make no sense.
		 */
		void draw(sdl::Renderer* renderer = nullptr, Camera* camera = nullptr) override;

		/**
		 * Draw a specified tile to the renderer.
		 * @param[in] index index of the tile, counting from the top-left, toward bottom-right.
		 * @param[in] position Position of the tile will be drawn.
		 * @param[in] renderer Renderer use to draw, default renderer if nullptr.
		 * @param[in] camera Camera use to draw, defalut camera if nullptr.
		 * @param[in] staticOnCamera Determine if the tile position is affected by Camera or not.
		 * @param[in] origin Origin (center point of rotation) of the tile.
		 * @param[in] angle Rotation angle of the tile.
		 * @param[in] flip Flipping state of the tile.
		 */
		void drawTile(size_t index, const Vector2& position, sdl::Renderer* renderer = nullptr, Camera* camera = nullptr,
			bool staticOnCamera = false, const sdl::Point& origin = sdl::Point(),
			const vas::Angle& angle = vas::Angle(), sdl::Renderer::Flip flip = sdl::Renderer::Flip::none);

		SpriteSheet& operator=(const SpriteSheet&) = delete;
		SpriteSheet& operator=(SpriteSheet&&) = delete;

		/** Get the number of tiles. */
		size_t getTileCount() const;
		/** Get the size of the tile. */
		sdl::Point getTileSize() const;
	protected:
		sdl::Point tileSize;
		sdl::Point tileSheetDimension;
		sdl::Rect tileSource;
		sdl::Rect tileDest;
	};
}