//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "Font.hpp"

#ifdef VAS_USE_TTF
namespace vas::sdl
{
	namespace ttf
	{
		Font::Font()
		{
		}

		Font::Font(TTF_Font * instance, bool owner)
		{
			if (owner) componentInstance = std::shared_ptr<TTF_Font>{ instance, &TTF_CloseFont };
			else componentInstance = std::shared_ptr<TTF_Font>{ instance, [](TTF_Font* i) { return; } };
		}

		void Font::openFont(const std::string & file, int fontSize)
		{
			this->componentInstance = std::shared_ptr<TTF_Font>{ TTF_OpenFont(file.c_str(), fontSize), &TTF_CloseFont };
		}

		void Font::openFont(const std::string & file, int fontSize, long index)
		{
			this->componentInstance = std::shared_ptr<TTF_Font>{ TTF_OpenFontIndex(file.c_str(), fontSize, index), &TTF_CloseFont };
		}

		void Font::openFontRaw(rwops::RWops * src, int fontSize, bool freeSrc)
		{
			this->componentInstance = std::shared_ptr<TTF_Font>{ TTF_OpenFontRW(src, freeSrc ? 1 : 0, fontSize), &TTF_CloseFont };
		}

		void Font::openFontRaw(rwops::RWops * src, int fontSize, long index, bool freeSrc)
		{
			this->componentInstance = std::shared_ptr<TTF_Font>{ TTF_OpenFontIndexRW(src, freeSrc ? 1 : 0, fontSize, index), &TTF_CloseFont };
		}

		FontStyle::FlagType Font::getFontStyle()
		{
			return TTF_GetFontStyle(&*this->componentInstance);
		}

		void Font::setFontStyle(FontStyle::FlagType style)
		{
			TTF_SetFontStyle(&*this->componentInstance, style);
		}

		int Font::getFontOutlineSize()
		{
			return TTF_GetFontOutline(&*this->componentInstance);
		}

		void Font::setFontOutlineSize(int size)
		{
			TTF_SetFontOutline(&*this->componentInstance, size);
		}

		FontHinting::FlagType Font::getFontHinting()
		{
			return TTF_GetFontHinting(&*this->componentInstance);
		}

		void Font::setFontHinting(FontHinting::FlagType hintingType)
		{
			TTF_SetFontHinting(&*this->componentInstance, hintingType);
		}

		bool Font::getFontKerning()
		{
			return TTF_GetFontKerning(&*this->componentInstance) == 1;
		}

		void Font::setFontKerning(bool value)
		{
			TTF_SetFontKerning(&*this->componentInstance, value ? 1 : 0);
		}

		int Font::fontHeight()
		{
			return TTF_FontHeight(&*this->componentInstance);
		}

		int Font::fontAscent()
		{
			return TTF_FontAscent(&*this->componentInstance);
		}

		int Font::fontDescent()
		{
			return TTF_FontDescent(&*this->componentInstance);
		}

		int Font::fontLineSkip()
		{
			return TTF_FontLineSkip(&*this->componentInstance);
		}

		long Font::fontFaces()
		{
			return TTF_FontFaces(&*this->componentInstance);
		}

		int Font::fontFacelsFixedWidth()
		{
			return TTF_FontFaceIsFixedWidth(&*this->componentInstance);
		}

		std::string Font::fontFaceFamilyName()
		{
			return TTF_FontFaceFamilyName(&*this->componentInstance);
		}

		std::string Font::fontFaceStyleName()
		{
			return TTF_FontFaceStyleName(&*this->componentInstance);
		}

		bool Font::glyphIsProvided(uint16_t ch)
		{
			return TTF_GlyphIsProvided(&*this->componentInstance, ch) == 1;
		}

		int Font::glyphMetrics(uint16_t ch, int * minx, int * maxx, int * miny, int * maxy, int * advance)
		{
			return TTF_GlyphMetrics(&*this->componentInstance, ch, minx, maxx, miny, maxy, advance);
		}

		Point Font::sizeText(const std::string & text)
		{
			Point textDim;
			TTF_SizeText(&*this->componentInstance, text.c_str(), &textDim.x, &textDim.y);
			return textDim;
		}

		Point Font::sizeUTF8(const std::string & text)
		{
			Point textDim;
			TTF_SizeUTF8(&*this->componentInstance, text.c_str(), &textDim.x, &textDim.y);
			return textDim;
		}

		Point Font::sizeUnicode(const std::wstring & text)
		{
			Point textDim;
			TTF_SizeUNICODE(&*this->componentInstance, reinterpret_cast<const uint16_t*>(text.c_str()), &textDim.x, &textDim.y);
			return textDim;
		}

		Surface Font::renderTextSolid(const std::string & text, const Colour & foreground)
		{
			return Surface{ TTF_RenderText_Solid(&*this->componentInstance, text.c_str(),
				static_cast<SDL_Colour>(foreground)), true };
		}

		Surface Font::renderTextShaded(const std::string & text, const Colour & foreground, const Colour & background)
		{
			return Surface{ TTF_RenderText_Shaded(&*this->componentInstance, text.c_str(),
				static_cast<SDL_Colour>(foreground), static_cast<SDL_Colour>(background)), true };
		}

		Surface Font::renderTextBlended(const std::string & text, const Colour & foreground)
		{
			return Surface{ TTF_RenderText_Blended(&*this->componentInstance, text.c_str(),
				static_cast<SDL_Colour>(foreground)), true };
		}

		Surface Font::renderTextBlended(const std::string & text, const Colour & foreground, uint32_t warpLength)
		{
			return Surface{ TTF_RenderText_Blended_Wrapped(&*this->componentInstance, text.c_str(),
				static_cast<SDL_Colour>(foreground), warpLength), true };
		}

		Surface Font::renderUTF8Solid(const std::string & text, const Colour & foreground)
		{
			return Surface{ TTF_RenderUTF8_Solid(&*this->componentInstance, text.c_str(),
				static_cast<SDL_Colour>(foreground)), true };
		}

		Surface Font::renderUTF8Shaded(const std::string & text, const Colour & foreground, const Colour & background)
		{
			return Surface{ TTF_RenderUTF8_Shaded(&*this->componentInstance, text.c_str(),
				static_cast<SDL_Colour>(foreground), static_cast<SDL_Colour>(background)), true };
		}

		Surface Font::renderUTF8Blended(const std::string & text, const Colour & foreground)
		{
			return Surface{ TTF_RenderUTF8_Blended(&*this->componentInstance, text.c_str(),
				static_cast<SDL_Colour>(foreground)), true };
		}

		Surface Font::renderUTF8Blended(const std::string & text, const Colour & foreground, uint32_t warpLength)
		{
			return Surface{ TTF_RenderUTF8_Blended_Wrapped(&*this->componentInstance, text.c_str(),
				static_cast<SDL_Colour>(foreground), warpLength), true };
		}

		Surface Font::renderUnicodeSolid(const std::wstring & text, const Colour & foreground)
		{
			return Surface{ TTF_RenderUNICODE_Solid(&*this->componentInstance, reinterpret_cast<const uint16_t*>(text.c_str()),
				static_cast<SDL_Colour>(foreground)), true };
		}

		Surface Font::renderUnicodeShaded(const std::wstring & text, const Colour & foreground, const Colour & background)
		{
			return Surface{ TTF_RenderUNICODE_Shaded(&*this->componentInstance, reinterpret_cast<const uint16_t*>(text.c_str()),
				static_cast<SDL_Colour>(foreground), static_cast<SDL_Colour>(background)), true };
		}

		Surface Font::renderUnicodeBlended(const std::wstring & text, const Colour & foreground)
		{
			return Surface{ TTF_RenderUNICODE_Blended(&*this->componentInstance, reinterpret_cast<const uint16_t*>(text.c_str()),
				static_cast<SDL_Colour>(foreground)), true };
		}

		Surface Font::renderUnicodeBlended(const std::wstring & text, const Colour & foreground, uint32_t warpLength)
		{
			return Surface{ TTF_RenderUNICODE_Blended_Wrapped(&*this->componentInstance, reinterpret_cast<const uint16_t*>(text.c_str()),
				static_cast<SDL_Colour>(foreground), warpLength), true };
		}

		Surface Font::renderGlyphSolid(uint16_t ch, const Colour & foreground)
		{
			return Surface{ TTF_RenderGlyph_Solid(&*this->componentInstance, ch, static_cast<SDL_Colour>(foreground)), true };
		}

		Surface Font::renderGlyphShaded(uint16_t ch, const Colour & foreground, const Colour & background)
		{
			return Surface{ TTF_RenderGlyph_Shaded(&*this->componentInstance, ch, static_cast<SDL_Colour>(foreground), static_cast<SDL_Colour>(background)), true };
		}

		Surface Font::renderGlyphBlended(uint16_t ch, const Colour & foreground)
		{
			return Surface{ TTF_RenderGlyph_Blended(&*this->componentInstance, ch, static_cast<SDL_Colour>(foreground)), true };
		}
		
		void Font::destroy()
		{
			componentInstance = nullptr;
		}
		
		bool Font::isNull()
		{
			return componentInstance == nullptr;
		}
		
		Font::operator TTF_Font*()
		{
			return componentInstance.get();
		}
		
		Font & Font::operator=(NullComponent_t)
		{
			destroy();
			return *this;
		}
		
		bool Font::operator==(const Font & rhs)
		{
			return componentInstance == rhs.componentInstance;
		}
		
		bool Font::operator!=(const Font & rhs)
		{
			return !operator==(rhs);
		}
		
		bool Font::operator==(NullComponent_t)
		{
			return isNull();
		}
		
		bool Font::operator!=(NullComponent_t)
		{
			return !operator==(nullcomponent);
		}
	}
}
#endif // VAS_USE_TTF
