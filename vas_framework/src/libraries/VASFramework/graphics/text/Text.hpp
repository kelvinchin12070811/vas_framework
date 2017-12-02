#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <memory>
#include "../render_item/RenderAbleBase.hpp"
#include "../move_able/MoveAble.hpp"
#include "../../math/Colour.hpp"

namespace vas
{
	class Text : public RenderAbleBase, public MoveAble
	{
	public:
		Text();
		Text(const std::wstring& text, const Vector2& position, const std::wstring& ttfPath, size_t fontSize, const Colour& textColour = ColourPresets::black);
		~Text();

		void initText();

		void tick() override;
		void draw() override;

		void setTextColour(const Colour& value);
		void setOverlayColour(const Colour& value);
		void setText(const std::wstring& value);
		void setFontSize(size_t value);

		const Colour& getTextColour();
		const Colour& getOverlayColour();
		const std::wstring& getText();
		const std::wstring& getTTFPath();
		size_t getFontSize();

		std::shared_ptr<SDL_Texture> getTexture();
	protected:
		Colour textColour;
		Colour overlay = ColourPresets::white;
		std::wstring text;
		std::wstring ttfPath;
		size_t fontSize = 0;
		std::shared_ptr<TTF_Font> font = nullptr;
		std::shared_ptr<SDL_Texture> texture = nullptr;

		void openFont();
		void renderText();
	};
}