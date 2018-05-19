#include <cmath>
#include "StyledText.hpp"

#ifdef VAS_USE_TTF
namespace vas
{
	StyledText::StyledText()
	{
	}

	StyledText::StyledText(const std::string & text, const std::string & font, const Vector2 & position, int fontSize, bool init)
	{
		foreground = std::make_unique<Text>(text, font, position, fontSize, init);
		background = std::make_unique<Text>(text, font, position, fontSize, init);
	}

	StyledText::StyledText(const std::string & text, const std::string & font, const Vector2 & position, int fontSize, const sdl::Colour & textColour, bool init)
	{
		foreground = std::make_unique<Text>(text, font, position, fontSize, textColour, init);
		background = std::make_unique<Text>(text, font, position, fontSize, sdl::ColourPresets::black, init);
	}

	StyledText::StyledText(const std::string & text, const std::string & font, const Vector2 & position, int fontSize, const sdl::Colour & textColour, Text::RenderMode renderMode, bool init)
	{
		foreground = std::make_unique<Text>(text, font, position, fontSize, textColour, renderMode, init);
		background = std::make_unique<Text>(text, font, position, fontSize, sdl::ColourPresets::black, renderMode, init);
	}


	StyledText::~StyledText()
	{
	}

	void StyledText::tick()
	{
		background->tick();
		foreground->tick();
	}

	void StyledText::draw()
	{
		background->draw();
		foreground->draw();
	}

	void StyledText::move(const Vector2 & movement)
	{
		reflectSetAction(&Text::move, movement);
	}

	void StyledText::setPosition(const Vector2 & position)
	{
		foreground->setPosition(position);
		applyBackgroundOffset();
	}

	void StyledText::setBackgroundOffset(const Vector2 & value)
	{
		if (backgroundOffset != value)
		{
			backgroundOffset = value;
			applyBackgroundOffset();
		}
	}

	int StyledText::getOutlineSize() const
	{
		return background->getFont().getFontOutlineSize();
	}

	void StyledText::setOutlineSize(int value)
	{
		if (getOutlineSize() == value) return;
		background->getFont().setFontOutlineSize(value);
		background->reRender();
		setBackgroundOffset(vas::Vector2(static_cast<float>(-value), static_cast<float>(-value)));
	}

	sdl::Colour StyledText::getColour() const
	{
		return foreground->getTextColour();
	}

	void StyledText::setColour(const sdl::Colour & value, bool update)
	{
		foreground->setTextColour(value, update);
	}

	sdl::Colour StyledText::getBackgroundColour() const
	{
		return background->getTextColour();
	}

	void StyledText::setBackgroundColour(const sdl::Colour & value, bool update)
	{
		background->setTextColour(value, update);
	}

	std::string StyledText::getText() const
	{
		return foreground->getText();
	}

	void StyledText::setString(const std::string & value, bool update)
	{
		reflectSetAction(&Text::setString, value, update);
		if (update) applyBackgroundOffset();
	}

	bool StyledText::isStaticOnCamera() const
	{
		return foreground->isStaticOnCamera();
	}

	void StyledText::setStaticOnCamera(bool value)
	{
		foreground->setStaticOnCamera(value);
		background->setStaticOnCamera(value);
	}

	void StyledText::applyBackgroundOffset()
	{
		auto newPos = foreground->getPosition() + backgroundOffset;
		background->setPosition(newPos);
	}

	const Vector2 & StyledText::getBackgroundOffset() const
	{
		return backgroundOffset;
	}
}
#endif // VAS_USE_TTF
