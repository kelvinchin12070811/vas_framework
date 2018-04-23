#include "Text.hpp"

namespace vas
{
	Text::Text()
	{
	}

	Text::Text(const std::string & text, const Vector2 & position, int fontSize):
		text(text), position(position), fontSize(fontSize)
	{
	}

	Text::Text(const std::string & text, const Vector2 & position, int fontSize, const sdl::Colour & textColour):
		Text(text, position, fontSize)
	{
		this->textColour = textColour;
	}

	Text::Text(const std::string & text, const Vector2 & position, int fontSize, const sdl::Colour & textColour, Text::RenderMode renderMode):
		Text(text, position, fontSize, textColour)
	{
		this->renderMode = renderMode;
	}


	Text::~Text()
	{
	}
}