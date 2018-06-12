#pragma once
#include "../../VASConfig.hpp"


#ifdef VAS_USE_TTF
#include "../sprites/Sprite.hpp"

namespace vas
{
	class VAS_DECLSPEC Text : public Sprite
	{
	public:
		enum class RenderMode : uint8_t { solid, shaded, blended };
	public:
		Text();
		Text(const std::string& text, const std::string& font, const Vector2& position, int fontSize, bool init = true);
		Text(const std::string& text, const std::string& font, const Vector2& position, int fontSize, const sdl::Colour& textColour, bool init = true);
		Text(const std::string& text, const std::string& font, const Vector2& position, int fontSize, const sdl::Colour& textColour, Text::RenderMode renderMode, bool init = true);
		~Text();

		void tick() override;
		void draw(sdl::Renderer* renderer = nullptr, Camera* camera = nullptr) override;

		void reRender();
		void reRenderEverything();
	public: //properties
		sdl::ttf::Font getFont() const;

		int getFontSize() const;
		void setFontSize(int value, bool update = true);

		std::string getText() const;
		void setString(const std::string& value, bool update = true);

		std::string getFontPath() const;
		void setFontPath(const std::string& value, bool update = true);

		Text::RenderMode getRenderMode() const;
		void setRenderMode(Text::RenderMode& value);

		sdl::Colour getTextColour() const;
		void setTextColour(const sdl::Colour& value, bool update = true);

		sdl::Colour getBackgroundColour() const;
		void setBackgroundColour(const sdl::Colour& value, bool update = true);
	private:
		void initText();
		void renderTexture();
	private:
		bool inited{ false };
		std::string text;
		std::string fontPath;
		int fontSize{ 0 };
		Text::RenderMode renderMode{ Text::RenderMode::blended };
		sdl::Colour textColour{ sdl::ColourPresets::black };
		sdl::Colour backgroundColour{ sdl::ColorPresets::black };
		sdl::ttf::Font font;
	};
}
#endif // VAS_USE_TTF
