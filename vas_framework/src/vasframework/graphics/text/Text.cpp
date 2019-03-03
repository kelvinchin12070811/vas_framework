//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "Text.hpp"

#ifdef VAS_USE_TTF
#include "../../base/Base.hpp"
#include "../../manager/FontCacheManager.hpp"

namespace vas
{
	Text::Text(const std::string & text, const std::string & font, const Vector2 & position, int fontSize, bool init) :
		text(text), fontPath(font), fontSize(fontSize)
	{
		this->position = position;
		if (init) initText();
	}

	Text::Text(const std::string & text, const std::string & font, const Vector2 & position, int fontSize, const sdl::Colour & textColour, bool init) :
		Text(text, font, position, fontSize, false)
	{
		this->textColour = textColour;
		if (init) initText();
	}

	Text::Text(const std::string & text, const std::string & font, const Vector2 & position, int fontSize, const sdl::Colour & textColour, Text::RenderMode renderMode, bool init) :
		Text(text, font, position, fontSize, textColour, false)
	{
		this->renderMode = renderMode;
		if (init) initText();
	}

	void Text::tick()
	{
		Sprite::tick();
	}

	void Text::draw(sdl::Renderer* renderer, Camera* camera)
	{
		Sprite::draw(renderer, camera);
	}

	void Text::reRender()
	{
		renderTexture();
	}

	void Text::reRenderEverything()
	{
		inited = false;
		initText();
	}

	sdl::ttf::Font Text::getFont() const
	{
		return font;
	}

	int Text::getFontSize() const
	{
		return fontSize;
	}

	void Text::setFontSize(int value, bool update)
	{
		if (fontSize == value) return;
		fontSize = value;
		if (update) reRenderEverything();
	}

	std::string Text::getText() const
	{
		return text;
	}

	void Text::setString(const std::string & value, bool update)
	{
		if (text == value) return;
		text = value;
		if (update) reRender();
	}

	std::string Text::getFontPath() const
	{
		return fontPath;
	}

	void Text::setFontPath(const std::string & value, bool update)
	{
		if (fontPath == value) return;
		fontPath = value;
		if (update) reRenderEverything();
	}

	Text::RenderMode Text::getRenderMode() const
	{
		return renderMode;
	}

	void Text::setRenderMode(Text::RenderMode & value)
	{
		renderMode = value;
	}

	sdl::Colour Text::getTextColour() const
	{
		return textColour;
	}

	void Text::setTextColour(const sdl::Colour & value, bool update)
	{
		if (textColour == value) return;
		textColour = value;
		if (update) reRender();
	}

	sdl::Colour Text::getBackgroundColour() const
	{
		return backgroundColour;
	}

	void Text::setBackgroundColour(const sdl::Colour & value, bool update)
	{
		if (backgroundColour == value) return;
		backgroundColour = value;
		if (update) reRender();
	}

	void Text::initText()
	{
		if (!inited)
		{
			if (FontCacheManager::getInstance().hasFont(fontPath, fontSize))
				font = *FontCacheManager::getInstance().getFont(fontPath, fontSize);
			else
			{
				font.openFont(fontPath, fontSize);
				FontCacheManager::getInstance().insertFont(fontPath, fontSize, font);
			}
			renderTexture();
			inited = true;
		}
	}

	void Text::renderTexture()
	{
		if (font == sdl::nullcomponent)
			throw sdl::SDLCoreException();
		switch (renderMode)
		{
		case vas::Text::RenderMode::solid:
			this->texture = sdl::Texture(Base::getInstance().getRenderer(), font.renderUTF8Solid(text, textColour));
			break;
		case vas::Text::RenderMode::shaded:
			this->texture = sdl::Texture(Base::getInstance().getRenderer(), font.renderUTF8Shaded(text, textColour, backgroundColour));
			break;
		case vas::Text::RenderMode::blended:
			this->texture = sdl::Texture(Base::getInstance().getRenderer(), font.renderUTF8Blended(text, textColour));
			break;
		}
		this->texture.queryTexture(&this->source.w, &this->source.h);
		this->destination = this->source;
	}
}
#endif // VAS_USE_TTF
