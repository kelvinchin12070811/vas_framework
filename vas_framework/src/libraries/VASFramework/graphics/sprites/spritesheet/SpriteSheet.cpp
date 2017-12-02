#include "SpriteSheet.hpp"
#include "../../../base/Base.hpp"
#include "../../../base/Camera.hpp"

namespace vas
{
	SpriteSheet::SpriteSheet()
	{
	}

	SpriteSheet::SpriteSheet(const std::wstring & path, const Vector2 & position, unsigned int spriteWidth, unsigned int spriteHeight, bool buffer) :
		Sprite(path, position, buffer), spriteWidth(spriteWidth), spriteHeight(spriteHeight)
	{
		count = (this->source.w / spriteWidth) * (this->source.h / spriteHeight);
	}


	SpriteSheet::~SpriteSheet()
	{
	}

	void SpriteSheet::tick()
	{
		Sprite::tick();
	}

	void SpriteSheet::draw()
	{
		Sprite::draw();
	}

	void SpriteSheet::drawTileAt(size_t tileIndex, const Vector2 & position, float scale, const Angle & rotation, const SDL_Point & origin, SDL_RendererFlip flip)
	{
		if (this->texture == nullptr) return;
		if (tileIndex >= count)
			throw std::logic_error(u8"This spritesheet has only contain " + std::to_string(count) + u8" tile but required tile at index of " + std::to_string(tileIndex));

		SDL_Rect tileRect = { 0, 0, static_cast<int>(spriteWidth), static_cast<int>(spriteHeight) };
		tileRect.y = tileIndex / (this->source.w / spriteWidth);
		tileRect.x = tileIndex - (this->source.w / spriteWidth) * tileRect.y;

		tileRect.x = static_cast<int>(tileRect.x * spriteWidth);
		tileRect.y = static_cast<int>(tileRect.y * spriteHeight);
		SDL_Rect tilePositionRect = { static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(tileRect.w * scale), static_cast<int>(tileRect.h * scale) };

		SDL_SetTextureAlphaMod(this->texture.get(), this->colourOverlay.alpha);
		SDL_SetTextureColorMod(this->texture.get(), this->colourOverlay.red, this->colourOverlay.green, this->colourOverlay.bule);
		if (!this->staticOnCamera)
		{
			tilePositionRect.x -= Camera::getInstance().getXOffset();
			tilePositionRect.y -= Camera::getInstance().getYOffset();
		}

		if (Camera::getInstance().canSee(tilePositionRect))
			SDL_RenderCopyEx(Base::getInstance().getRenderer().get(), this->texture.get(), &tileRect, &tilePositionRect, rotation.get(), &origin, flip);

		SDL_SetTextureAlphaMod(this->texture.get(), 255);
		SDL_SetTextureColorMod(this->texture.get(), 255, 255, 255);
	}

	size_t SpriteSheet::getCount()
	{
		return count;
	}
}