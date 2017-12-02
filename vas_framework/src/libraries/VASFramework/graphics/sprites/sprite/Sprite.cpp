#include "Sprite.hpp"
#include "../../../base/Base.hpp"
#include "../../../manager/TextureManager.hpp"

namespace vas
{
	Sprite::Sprite()
	{
	}

	Sprite::Sprite(const std::wstring & path, const Vector2 & position, bool buffer)
	{
		createSprite(path, position, buffer);
	}

	Sprite::~Sprite()
	{
	}

	void Sprite::tick()
	{
		this->destination.x = static_cast<int>(this->position.x) + center.x;
		this->destination.y = static_cast<int>(this->position.y) + center.y;
	}

	void Sprite::draw()
	{
		if (texture != nullptr)
		{
			SDL_SetTextureAlphaMod(texture.get(), colourOverlay.alpha);
			SDL_SetTextureColorMod(texture.get(), colourOverlay.red, colourOverlay.green, colourOverlay.bule);

			if (staticOnCamera)
			{
				if (Camera::getInstance().canSee(this->destination))
					SDL_RenderCopyEx(Base::getInstance().getRenderer().get(), texture.get(), &this->source, &this->destination, this->rotation.get(), &this->center, this->flip);
			}
			else
			{
				SDL_Rect destinationWithOffset = destination;

				destinationWithOffset.x = destination.x - Camera::getInstance().getXOffset();
				destinationWithOffset.y = destination.y - Camera::getInstance().getYOffset();
				if (Camera::getInstance().canSee(destinationWithOffset))
					SDL_RenderCopyEx(Base::getInstance().getRenderer().get(), texture.get(), &this->source, &destinationWithOffset, this->rotation.get(), &this->center, this->flip);
			}

			SDL_SetTextureAlphaMod(texture.get(), 0xff);
			SDL_SetTextureColorMod(texture.get(), 0xff, 0xff, 0xff); 
		}
	}

	void Sprite::createSprite(const std::wstring & path, const Vector2 & position, bool buffer)
	{
		key = path;
		if (this->position != position)
			this->position = position;
		this->_isBuffered = buffer;
		if (buffer)
			texture = TextureManager::getInstance().createAndInsertTextureFromFileGet(path);
		else
			texture = TextureManager::getInstance().createTextureFromFile(path);

		SDL_QueryTexture(texture.get(), nullptr, nullptr, &source.w, &source.h);
		destination = source;
		SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_BLEND);
	}

	void Sprite::setColour(const Colour & colour)
	{
		this->colourOverlay = colour;
	}

	std::shared_ptr<SDL_Texture> Sprite::getTexture()
	{
		return texture;
	}

	const std::shared_ptr<SDL_Texture> Sprite::getTexture() const
	{
		return texture;
	}

	const Colour & Sprite::getColour()
	{
		return colourOverlay;
	}

	bool Sprite::isBuffered() const
	{
		return _isBuffered;
	}
}