#pragma once
#include "Sprite.hpp"

namespace vas
{
	class SpriteSheet : public Sprite
	{
	public:
		SpriteSheet();
		SpriteSheet(const std::string& file, const sdl::Point& tileSize, const Vector2& position = Vector2(),
			const sdl::Point& origin = sdl::Point(), BufferMode bfMode = BufferMode::buffered);
		SpriteSheet(const SpriteSheet&) = delete;
		SpriteSheet(SpriteSheet&&) = delete;
		~SpriteSheet();

		void tick() override;
		void draw() override;

		void drawTile(size_t index, const Vector2& position, bool staticOnCamera = false, const sdl::Point& origin = sdl::Point(),
			const vas::Angle& angle = vas::Angle(), sdl::Renderer::Flip flip = sdl::Renderer::Flip::none);

		SpriteSheet& operator=(const SpriteSheet&) = delete;
		SpriteSheet& operator=(SpriteSheet&&) = delete;
	protected:
		sdl::Point tileSize;
		sdl::Point tileSheetDimension;
		sdl::Rect tileSource;
		sdl::Rect tileDest;
	};
}