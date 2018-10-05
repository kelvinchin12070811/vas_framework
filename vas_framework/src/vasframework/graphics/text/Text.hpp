#pragma once
#include "../../VASConfig.hpp"


#ifdef VAS_USE_TTF
#include "../sprites/Sprite.hpp"

namespace vas
{
	/** @addtogroup graphics
		  @{
	*/
	/** @brief The text that shown on the screen that tell you your score.

		  Text convert a string of text into a sprite and then render it to the renderer. Text is the communication channel that
		  the creator of the game communicate with the player.
	*/
	class VAS_DECLSPEC Text : public Sprite
	{ /** @} */
	public:
		/** Render mode of the text, visit the following SDL_ttf official documentation for more information.
			  
			   - [TTF_RenderUTF8_Solid](http://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf_44.html#SEC44)
			   - [TTF_RenderUTF8_Shaded](http://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf_48.html#SEC48)
			   - [TTF_RenderUTF8_Blended](http://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf_52.html#SEC52)
		*/
		enum class RenderMode : uint8_t {
			solid, /**< Solid text. */
			shaded, /**< Shaded text. */
			blended /**< Blended text. */
		};
	public:
		Text();
		/** Create new instance of Text.
			  @param text String of text that need to render.
			  @param font Font type file's name that use to render the text, ttf and otf are supported.
			  @param position Position of the text.
			  @param fontSize Size of the font.
			  @param init Determin if init and pre-render the text to texture after the creation of the text or not.
		*/
		Text(const std::string& text, const std::string& font, const Vector2& position, int fontSize, bool init = true);
		/** Create new instance of Text.
			  @param text String of text that need to render.
			  @param font Font type file's name that use to render the text, ttf and otf are supported.
			  @param position Position of the text.
			  @param fontSize Size of the font.
			  @param textColour Colour of the text.
			  @param init Determin if init and pre-render the text to texture after the creation of the text or not.
		*/
		Text(const std::string& text, const std::string& font, const Vector2& position, int fontSize, const sdl::Colour& textColour, bool init = true);
		/** Create new instance of Text.
			  @param text String of text that need to render.
			  @param font Font type file's name that use to render the text, ttf and otf are supported.
			  @param position Position of the text.
			  @param fontSize Size of the font.
			  @param textColour Colour of the text.
			  @param renderMode Text render mode of the text.
			  @param init Determin if init and pre-render the text to texture after the creation of the text or not.
		*/
		Text(const std::string& text, const std::string& font, const Vector2& position, int fontSize, const sdl::Colour& textColour, Text::RenderMode renderMode, bool init = true);
		~Text();

		void tick() override;
		void draw(sdl::Renderer* renderer = nullptr, Camera* camera = nullptr) override;

		/** Rerender the text texture. */
		void reRender();
		/** Rerender the text texture with new font size. */
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
		/** [Read & Write] String of text that need to draw.\n
				- __mutators__
					-# void setString(const std::string& value, bool update = true)\n
						 This function will rerender the text if update is true.
				- __accessors__
					-# std::string getText() const
		*/
		std::string text;
		std::string fontPath;
		/** [Read & Write] Font size of the text.
				- __mutators__
					-# void setFontSize(int value, bool update = true)\n
						 This function will rerender the text if update is true.
				- __accessors__
					-# int getFontSize() const
		*/
		int fontSize{ 0 };
		/** [Read & Write] Render mode of the text.
				- __mutators__
					-# void setRenderMode(Text::RenderMode& value)\n
						 This function will not rerender the text untill reRender() or reRenderEverything() is called.
				- __accessors__
					-# Text::RenderMode getRenderMode() const
		*/
		Text::RenderMode renderMode{ Text::RenderMode::blended };
		/** [Read & Write] Foreground colour of the text.
				- __mutators__
					-# void setTextColour(const sdl::Colour& value, bool update = true)\n
						 This function will rerender the text if update is true.
				- __accessors__
					-# void setTextColour(const sdl::Colour& value, bool update = true)
		*/
		sdl::Colour textColour{ sdl::ColourPresets::black };
		/** [Read & Write] Background colour of the text.
				- __mutators__
					-# void setBackgroundColour(const sdl::Colour& value, bool update = true)\n
						 This function will rerender the text if update is true.
				- __accessors__
					-# void setBackgroundColour(const sdl::Colour& value, bool update = true)
		*/
		sdl::Colour backgroundColour{ sdl::ColorPresets::black };
		/** [Read Only] Font defination use to render the text.\n
				- __accessors__
					-# sdl::ttf::Font getFont() const
		*/
		sdl::ttf::Font font;
	};
}
#endif // VAS_USE_TTF
