//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include "../../VASConfig.hpp"

#ifdef VAS_USE_TTF
#include <SDL_ttf.h>
#include "../SDLComponentBase.hpp"
#include "../RWops.hpp"
#include "Flags.hpp"
#include "../math/Point.hpp"
#include "../math/Colour.hpp"
#include "../video/Surface.hpp"

namespace vas::sdl
{
	namespace ttf
	{
		/** @addtogroup sdl_ttf
			  @{
		*/
		/** @brief The internal structure containing font information. */
		class VAS_DECLSPEC Font : public SDLComponentBase<TTF_Font, Font>
		{ /** @} */
		public:
			Font(); /**< Create empty font. */
			Font(const Font& rhs);
			Font(Font&& rhs);
			/** Reference from TTF_Font. */
			explicit Font(TTF_Font* instance, SDLComponentBase::DeleterType deleter = &notDeleteDeleter);
			~Font();

			/** Load font from file.
				  @param file File name of file to load.
				  @param fontSize Size of the font.
			*/
			void openFont(const std::string& file, int fontSize);
			/** Load font from file.
				  @param file File name of file to load.
				  @param fontSize Size of the font.
				  @param index Index of the font sheet.
			*/
			void openFont(const std::string& file, int fontSize, long index);

			/** Load font from memory.
				  @param src Binary data of font to load.
				  @param fontSize Size of the font.
				  @param freeSrc Free the resource after done loading.
			*/
			void openFontRaw(rwops::RWops* src, int fontSize, bool freeSrc = true);
			/** Load font from memory.
				  @param src Binary data of font to load.
				  @param fontSize Size of the font.
				  @param index Index of font sheet.
				  @param freeSrc Free the resource after done loading.
			*/
			void openFontRaw(rwops::RWops* src, int fontSize, long index, bool freeSrc = true);

			FontStyle::FlagType getFontStyle(); /**< Get font style. */
			void setFontStyle(FontStyle::FlagType style); /**< Set font style. */

			int getFontOutlineSize(); /**< Get font outline size. */
			void setFontOutlineSize(int size); /**< Set font outline size. */

			FontHinting::FlagType getFontHinting(); /**< Get font hinting. */
			void setFontHinting(FontHinting::FlagType hintingType); /**< Set font hinting. */

			bool getFontKerning(); /**< Get font kerning. */
			void setFontKerning(bool value); /**< Set font kerning. */

			int fontHeight(); /**< Get font height. */
			int fontAscent(); /**< Get font ascent. */
			int fontDescent(); /**< Get font descent. */
			int fontLineSkip(); /**< Get font line skip. */
			long fontFaces(); /**< Get font faces. */
			int fontFacelsFixedWidth(); /**< Get font facels fixed width. */
			std::string fontFaceFamilyName(); /**< Get font face family name. */
			std::string fontFaceStyleName(); /**< Get font face style name. */
			bool glyphIsProvided(uint16_t ch); /**< Check wether a glyph is provided by the font or not. @return true if success. */
			int glyphMetrics(uint16_t ch, int* minx, int* maxx, int* miny, int* maxy, int* advance);

			Point sizeText(const std::string& text); /**< Get the dimensions of a rendered string of text. */
			Point sizeUTF8(const std::string& text); /**< Get the dimensions of a rendered string of UTF-8 text. */
			Point sizeUnicode(const std::wstring& text); /**< Get the dimensions of a rendered string of UTF-16 text. */

			Surface renderTextSolid(const std::string& text, const Colour& foreground); /**< Render solid text. */
			Surface renderTextShaded(const std::string& text, const Colour& foreground, const Colour& background); /**< Render shaded text. */
			Surface renderTextBlended(const std::string& text, const Colour& foreground); /**< Render blended text. */
			Surface renderTextBlended(const std::string& text, const Colour& foreground, uint32_t warpLength); /**< Render blended text with auto warp. */

			Surface renderUTF8Solid(const std::string& text, const Colour& foreground); /**< Render solid UTF-8 text. */
			Surface renderUTF8Shaded(const std::string& text, const Colour& foreground, const Colour& background); /**< Render shaded UTF-8 text. */
			Surface renderUTF8Blended(const std::string& text, const Colour& foreground); /**< Render blended UTF-8 text. */
			Surface renderUTF8Blended(const std::string& text, const Colour& foreground, uint32_t warpLength); /**< Render blended UTF-8 text with auto warp. */

			Surface renderUnicodeSolid(const std::wstring& text, const Colour& foreground); /**< Render solid UTF-16 text. */
			Surface renderUnicodeShaded(const std::wstring& text, const Colour& foreground, const Colour& background); /**< Render shaded UTF-16 text. */
			Surface renderUnicodeBlended(const std::wstring& text, const Colour& foreground); /**< Render blended UTF-16 text. */
			Surface renderUnicodeBlended(const std::wstring& text, const Colour& foreground, uint32_t warpLength); /**< Render blended UTF-16 text with auto warp. */

			/** Create an 8-bit palettized surface and render the given glyph at
				  fast quality with the given font and color.  The 0 pixel is the
				  colorkey, giving a transparent background, and the 1 pixel is set
				  to the text color.  The glyph is rendered without any padding or
				  centering in the X direction, and aligned normally in the Y direction.
				  This function returns the new surface, or vas::sdl::nullcomponent if there was an error.
			*/
			Surface renderGlyphSolid(uint16_t ch, const Colour& foreground);
			/** Create an 8-bit palettized surface and render the given glyph at
				  fast quality with the given font and color.  The 0 pixel is the
				  colorkey, giving a transparent background, and the 1 pixel is set
				  to the text color.  The glyph is rendered without any padding or
				  centering in the X direction, and aligned normally in the Y direction.
				  This function returns the new surface, or vas::sdl::nullcomponent if there was an error.
			*/
			Surface renderGlyphShaded(uint16_t ch, const Colour& foreground, const Colour& background);
			/** Create an 8-bit palettized surface and render the given glyph at
				  fast quality with the given font and color.  The 0 pixel is the
				  colorkey, giving a transparent background, and the 1 pixel is set
				  to the text color.  The glyph is rendered without any padding or
				  centering in the X direction, and aligned normally in the Y direction.
				  This function returns the new surface, or vas::sdl::nullcomponent if there was an error.
			*/
			Surface renderGlyphBlended(uint16_t ch, const Colour& foreground);

			Font& operator=(const Font& rhs);
			Font& operator=(Font&& rhs);
			Font& operator=(std::nullptr_t);

			static void VAS_PROTOTYPE_DEFINE_DEF_DELETER(TTF_Font);
		};
	}
}
#endif // VAS_USE_TTF
