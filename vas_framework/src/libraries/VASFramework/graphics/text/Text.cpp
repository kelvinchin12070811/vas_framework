#include "Text.hpp"
#include "../../util/SDLFunctionBridge.hpp"
#include "../../util/TextTools.hpp"
#include "../../base/Base.hpp"
#include "../../base/Camera.hpp"

namespace vas
{
	Text::Text()
	{
	}

	Text::Text(const std::wstring & text, const Vector2 & position, const std::wstring & ttfPath, size_t fontSize, const Colour & textColour):
		MoveAble(position), text(text), fontSize(fontSize), ttfPath(ttfPath), textColour(textColour)
	{
		initText();
	}


	Text::~Text()
	{
	}

	void Text::initText()
	{
		openFont();
		renderText();
	}

	void Text::tick()
	{
		this->destination.x = static_cast<int>(this->position.x) + center.x;
		this->destination.y = static_cast<int>(this->position.y) + center.y;
	}

	void Text::draw()
	{
		auto renderer = Base::getInstance().getRenderer().get();
		if (texture)
		{
			SDL_SetTextureAlphaMod(texture.get(), overlay.alpha);
			SDL_SetTextureColorMod(texture.get(), overlay.red, overlay.green, overlay.bule);

			if (this->staticOnCamera)
			{
				if (Camera::getInstance().canSee(destination))
					SDL_RenderCopyEx(renderer, texture.get(), &this->source, &this->destination, this->rotation.get(), &this->center, this->flip);
			}
			else
			{
				SDL_Rect destWithOffset = this->destination;
				destWithOffset.x -= Camera::getInstance().getXOffset();
				destWithOffset.y -= Camera::getInstance().getYOffset();

				if (Camera::getInstance().canSee(destWithOffset))
					SDL_RenderCopyEx(renderer, texture.get(), &this->source, &destWithOffset, this->rotation.get(), &this->center, this->flip);
			}

			SDL_SetTextureAlphaMod(texture.get(), 255);
			SDL_SetTextureColorMod(texture.get(), 255, 255, 255);
		}
	}

	void Text::setTextColour(const Colour & value)
	{
		if (textColour == value) return;
		textColour = value;
		renderText();
	}

	void Text::setOverlayColour(const Colour & value)
	{
		if (overlay != value)
			overlay = value;
	}

	void Text::setText(const std::wstring & value)
	{
		if (text == value) return;
		text = value;
		renderText();
	}

	void Text::setFontSize(size_t value)
	{
		if (fontSize == value) return;
		fontSize = value;
		initText();
	}

	const Colour & Text::getTextColour()
	{
		return textColour;
	}

	const Colour & Text::getOverlayColour()
	{
		return overlay;
	}

	const std::wstring & Text::getText()
	{
		return text;
	}

	const std::wstring & Text::getTTFPath()
	{
		return ttfPath;
	}

	size_t Text::getFontSize()
	{
		return fontSize;
	}

	std::shared_ptr<SDL_Texture> Text::getTexture()
	{
		return texture;
	}

	void Text::openFont()
	{
		font = SDLFunctionBridge::newTTFFont(TTF_OpenFont(TextTools::wstos(ttfPath).c_str(), fontSize));
		if (font == nullptr) throw std::runtime_error(SDL_GetError());
	}

	void Text::renderText()
	{
		auto tempSurface = SDLFunctionBridge::newSDLSurface(TTF_RenderUNICODE_Blended(font.get(), reinterpret_cast<const uint16_t*>(text.c_str()), static_cast<SDL_Colour>(textColour)));
		if (tempSurface == nullptr) throw std::runtime_error(SDL_GetError());

		texture = SDLFunctionBridge::newSDLTexture(SDL_CreateTextureFromSurface(Base::getInstance().getRenderer().get(), tempSurface.get()));
		if (texture == nullptr) throw std::runtime_error(SDL_GetError());

		SDL_QueryTexture(texture.get(), nullptr, nullptr, &this->source.w, &this->source.h);

		destination = source;
	}
}