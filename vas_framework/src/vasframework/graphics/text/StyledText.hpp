//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include "Text.hpp"

#ifdef VAS_USE_TTF
namespace vas
{
	/** @addtogroup graphics
		  @{
	*/
	/** @brief A version of Text with styles.

		  The StyledText contain a pair of Text which act as the foreground and background. The background text are reflected
		  as the foreground with black colour by defalut.
	*/
	class VAS_DECLSPEC StyledText : public DrawAble
	{ /** @} */
	public:
		StyledText() = default;
		/** Construct new StyledText.
			  @param text String of text that need to render.
			  @param font Font type file's name that use to render the text, ttf and otf are supported.
			  @param position Position of the text.
			  @param fontSize Size of the font.
			  @param init Determin if init and pre-render the text to texture after the creation of the text or not.
		*/
		StyledText(const std::string& text, const std::string& font, const Vector2& position, int fontSize, bool init = true);
		/** Create new instance of Text.
			  @param text String of text that need to render.
			  @param font Font type file's name that use to render the text, ttf and otf are supported.
			  @param position Position of the text.
			  @param fontSize Size of the font.
			  @param textColour Colour of the text.
			  @param init Determin if init and pre-render the text to texture after the creation of the text or not.
		*/
		StyledText(const std::string& text, const std::string& font, const Vector2& position, int fontSize, const sdl::Colour& textColour, bool init = true);
		/** Create new instance of Text.
			  @param text String of text that need to render.
			  @param font Font type file's name that use to render the text, ttf and otf are supported.
			  @param position Position of the text.
			  @param fontSize Size of the font.
			  @param textColour Colour of the text.
			  @param renderMode Text render mode of the text.
			  @param init Determin if init and pre-render the text to texture after the creation of the text or not.
		*/
		StyledText(const std::string& text, const std::string& font, const Vector2& position, int fontSize, const sdl::Colour& textColour, Text::RenderMode renderMode, bool init = true);

		void tick() override;
		void draw(sdl::Renderer* renderer = nullptr, Camera* camera = nullptr) override;

		/** Move the text to a new position
			  @param movement Steps that text moved.
		*/
		void move(const Vector2& movement);
		/** Set the position of the text
			  @param position New position of the text.
		*/
		void setPosition(const Vector2& position);

		/** Reflect same modifier on to both foreground and background
			  @param action Function pointer of a text modifier.
			  @param value Value that passed into the modifier.
		*/
		template <typename Value>
		void reflectSetAction(void (Text::*action)(const Value&), const Value& value) const
		{
			(foreground.get()->*action)(value);
			(background.get()->*action)(value);
		}
		/** Reflect same modifier on to both foreground and background, rerendr text if update is true.

			  Only apply to some function with rerender support.
			  @param action Function pointer of a text modifier.
			  @param value Value that passed into the modifier.
			  @param update Determine weather rerender the txt or not.
		*/
		template <typename Value>
		void reflectSetAction(void (Text::*action)(const Value&, bool), const Value& value, bool update) const
		{
			(foreground.get()->*action)(value, update);
			(background.get()->*action)(value, update);
		}
	public: //properties
		const Vector2& getBackgroundOffset() const; /**< Get the offset of background. */
		void setBackgroundOffset(const Vector2& value); /**< Set the offset of background. */

		int getOutlineSize() const; /**< Get text outline size. */
		void setOutlineSize(int value); /**< Set text outline size. */

		sdl::Colour getColour() const; /**< Get colour of foreground text. */
		void setColour(const sdl::Colour& value, bool update = true); /**< Set colour of foreground text. */

		sdl::Colour getBackgroundColour() const; /**< Get colour of background text. */
		void setBackgroundColour(const sdl::Colour& value, bool update = true); /**< Set colour of background text. */

		std::string getText() const; /**< Get text to render. */
		void setString(const std::string& value, bool update = true); /**< Set text to render. */

		bool isStaticOnCamera() const; /**< Is this DrawAble object static on camera? */
		void setStaticOnCamera(bool value); /**< Set if this DrawAble object static on camera. */
	public:
		std::unique_ptr<Text> foreground{ nullptr }; /**< Foreground text.*/
		std::unique_ptr<Text> background{ nullptr }; /**< Background text. */
	private:
		void applyBackgroundOffset();
	private:
		Vector2 backgroundOffset;
	};
}
#endif // VAS_USE_TTF
