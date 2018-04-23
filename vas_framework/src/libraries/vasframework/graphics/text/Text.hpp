#pragma once
#include "../sprites/Sprite.hpp"

namespace vas
{
	class Text : public Sprite
	{
	public:
		enum class RenderMode : uint8_t { solid, shaded, blended };
	public:
		Text();
		Text(const std::string& text, const Vector2& position, int fontSize);
		Text(const std::string& text, const Vector2& position, int fontSize, const sdl::Colour& textColour);
		Text(const std::string& text, const Vector2& position, int fontSize, const sdl::Colour& textColour, Text::RenderMode renderMode);
		~Text();

	private:
		std::string text;
		Vector2 position;
		int fontSize{ 0 };
		Text::RenderMode renderMode{ Text::RenderMode::blended };
		sdl::Colour textColour{ sdl::ColourPresets::black };
		sdl::Colour backgroundColour{ sdl::ColorPresets::black };
	};
}