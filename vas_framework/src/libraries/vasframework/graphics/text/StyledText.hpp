#pragma once
#include "Text.hpp"

#ifdef VAS_USE_TTF
namespace vas
{
	class StyledText : public IRendererAble
	{
	public:
		StyledText();
		StyledText(const std::string& text, const std::string& font, const Vector2& position, int fontSize, bool init = true);
		StyledText(const std::string& text, const std::string& font, const Vector2& position, int fontSize, const sdl::Colour& textColour, bool init = true);
		StyledText(const std::string& text, const std::string& font, const Vector2& position, int fontSize, const sdl::Colour& textColour, Text::RenderMode renderMode, bool init = true);
		~StyledText();

		void tick() override;
		void draw() override;

		void move(const Vector2& movement);
		void setPosition(const Vector2& position);

		template <typename Value>
		void reflectSetAction(void (Text::*action)(const Value&), const Value& value) const
		{
			(foreground.get()->*action)(value);
			(background.get()->*action)(value);
		}

		template <typename Value>
		void reflectSetAction(void (Text::*action)(const Value&, bool), const Value& value, bool update) const
		{
			(foreground.get()->*action)(value, update);
			(background.get()->*action)(value, update);
		}
	public: //properties
		const Vector2& getBackgroundOffset() const;
		void setBackgroundOffset(const Vector2& value);

		int getOutlineSize() const;
		void setOutlineSize(int value);

		sdl::Colour getColour() const;
		void setColour(const sdl::Colour& value, bool update = true);

		sdl::Colour getBackgroundColour() const;
		void setBackgroundColour(const sdl::Colour& value, bool update = true);

		std::string getText() const;
		void setString(const std::string& value, bool update = true);
	public:
		std::unique_ptr<Text> foreground{ nullptr };
		std::unique_ptr<Text> background{ nullptr };
	private:
		void applyBackgroundOffset();
	private:
		Vector2 backgroundOffset;
	};
}
#endif // VAS_USE_TTF
