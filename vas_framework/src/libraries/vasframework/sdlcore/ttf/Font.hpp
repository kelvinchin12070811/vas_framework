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
		class VAS_DECLSPEC Font : public SDLComponentBase<TTF_Font, Font>
		{
		public:
			Font();
			Font(const Font& rhs);
			Font(Font&& rhs);
			explicit Font(TTF_Font* instance, SDLComponentBase::DeleterType deleter = &notDeleteDeleter);
			~Font();

			void openFont(const std::string& file, int fontSize);
			void openFont(const std::string& file, int fontSize, long index);

			void openFontRaw(rwops::RWops* src, int fontSize, bool freeSrc = true);
			void openFontRaw(rwops::RWops* src, int fontSize, long index, bool freeSrc = true);

			FontStyle::FlagType getFontStyle();
			void setFontStyle(FontStyle::FlagType style);

			int getFontOutlineSize();
			void setFontOutlineSize(int size);

			FontHinting::FlagType getFontHinting();
			void setFontHinting(FontHinting::FlagType hintingType);

			bool getFontKerning();
			void setFontKerning(bool value);

			int fontHeight();
			int fontAscent();
			int fontDescent();
			int fontLineSkip();
			long fontFaces();
			int fontFacelsFixedWidth();
			std::string fontFaceFamilyName();
			std::string fontFaceStyleName();
			bool glyphIsProvided(uint16_t ch);
			int glyphMetrics(uint16_t ch, int* minx, int* maxx, int* miny, int* maxy, int* advance);

			Point sizeText(const std::string& text);
			Point sizeUTF8(const std::string& text);
			Point sizeUnicode(const std::wstring& text);

			Surface renderTextSolid(const std::string& text, const Colour& foreground);
			Surface renderTextShaded(const std::string& text, const Colour& foreground, const Colour& background);
			Surface renderTextBlended(const std::string& text, const Colour& foreground);
			Surface renderTextBlended(const std::string& text, const Colour& foreground, uint32_t warpLength);

			Surface renderUTF8Solid(const std::string& text, const Colour& foreground);
			Surface renderUTF8Shaded(const std::string& text, const Colour& foreground, const Colour& background);
			Surface renderUTF8Blended(const std::string& text, const Colour& foreground);
			Surface renderUTF8Blended(const std::string& text, const Colour& foreground, uint32_t warpLength);

			Surface renderUnicodeSolid(const std::wstring& text, const Colour& foreground);
			Surface renderUnicodeShaded(const std::wstring& text, const Colour& foreground, const Colour& background);
			Surface renderUnicodeBlended(const std::wstring& text, const Colour& foreground);
			Surface renderUnicodeBlended(const std::wstring& text, const Colour& foreground, uint32_t warpLength);

			Surface renderGlyphSolid(uint16_t ch, const Colour& foreground);
			Surface renderGlyphShaded(uint16_t ch, const Colour& foreground, const Colour& background);
			Surface renderGlyphBlended(uint16_t ch, const Colour& foreground);

			Font& operator=(const Font& rhs);
			Font& operator=(Font&& rhs);
			Font& operator=(std::nullptr_t);

			static void VAS_PROTOTYPE_DEFINE_DEF_DELETER(TTF_Font);
		};
	}
}
#endif // VAS_USE_TTF
