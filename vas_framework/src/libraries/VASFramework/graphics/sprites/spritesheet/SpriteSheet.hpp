#pragma once
#include "../sprite/Sprite.hpp"

namespace vas
{
	class VAS_FRAMEWORK_DLLEXPORT SpriteSheet : public Sprite
	{
	public:
		SpriteSheet();
		SpriteSheet(const std::wstring& path, const Vector2& position, unsigned int spriteWidth, unsigned int spriteHeight, bool buffer = true);
		~SpriteSheet();

		void tick() override;
		void draw() override;
		void drawTileAt(size_t tileIndex, const Vector2& position, float scale = 1, const Angle& rotation = Angle(0), const SDL_Point& origin = { 0 }, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE);

		size_t getCount();
	protected:
		unsigned int spriteWidth = 0;
		unsigned int spriteHeight = 0;
		size_t count = 0;
	};
}