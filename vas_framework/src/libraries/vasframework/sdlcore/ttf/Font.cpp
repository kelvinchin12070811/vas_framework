#include "Font.hpp"

namespace sdl
{
	namespace ttf
	{
		Font::Font()
		{
		}

		Font::Font(const Font & rhs):
			SDLComponentBase(rhs.componentInstance)
		{
		}

		Font::Font(Font && rhs):
			SDLComponentBase(std::move(rhs.componentInstance))
		{
		}

		Font::Font(TTF_Font * instance, SDLComponentBase::DeleterType deleter):
			SDLComponentBase(instance, deleter)
		{
		}

		Font::~Font()
		{
		}

		void Font::openFont(const std::string & file, int fontSize)
		{
			TTF_OpenFont(file.c_str(), fontSize);
		}

		void Font::openFont(const std::string & file, int fontSize, long index)
		{
			TTF_OpenFontIndex(file.c_str(), fontSize, index);
		}

		void Font::openFontRaw(rwops::RWops * src, int fontSize, bool freeSrc)
		{
			TTF_OpenFontRW(src, freeSrc ? 1 : 0, fontSize);
		}

		void Font::openFontRaw(rwops::RWops * src, int fontSize, long index, bool freeSrc)
		{
			TTF_OpenFontIndexRW(src, freeSrc ? 1 : 0, fontSize, index);
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
			return createComponent<Surface>(TTF_RenderText_Solid(&*this->componentInstance, text.c_str(),
				static_cast<SDL_Colour>(foreground)));
		}

		Surface Font::renderTextShaded(const std::string & text, const Colour & foreground, const Colour & background)
		{
			return createComponent<Surface>(TTF_RenderText_Shaded(&*this->componentInstance, text.c_str(),
				static_cast<SDL_Colour>(foreground), static_cast<SDL_Colour>(background)));
		}

		Surface Font::renderTextBlended(const std::string & text, const Colour & foreground)
		{
			return createComponent<Surface>(TTF_RenderText_Blended(&*this->componentInstance, text.c_str(),
				static_cast<SDL_Colour>(foreground)));
		}

		Surface Font::renderTextBlended(const std::string & text, const Colour & foreground, uint32_t warpLength)
		{
			return createComponent<Surface>(TTF_RenderText_Blended_Wrapped(&*this->componentInstance, text.c_str(),
				static_cast<SDL_Colour>(foreground), warpLength));
		}

		Surface Font::renderUTF8Solid(const std::string & text, const Colour & foreground)
		{
			return createComponent<Surface>(TTF_RenderUTF8_Solid(&*this->componentInstance, text.c_str(),
				static_cast<SDL_Colour>(foreground)));
		}

		Surface Font::renderUTF8Shaded(const std::string & text, const Colour & foreground, const Colour & background)
		{
			return createComponent<Surface>(TTF_RenderUTF8_Shaded(&*this->componentInstance, text.c_str(),
				static_cast<SDL_Colour>(foreground), static_cast<SDL_Colour>(background)));
		}

		Surface Font::renderUTF8Blended(const std::string & text, const Colour & foreground)
		{
			return createComponent<Surface>(TTF_RenderUTF8_Blended(&*this->componentInstance, text.c_str(),
				static_cast<SDL_Colour>(foreground)));
		}

		Surface Font::renderUTF8Blended(const std::string & text, const Colour & foreground, uint32_t warpLength)
		{
			return createComponent<Surface>(TTF_RenderUTF8_Blended_Wrapped(&*this->componentInstance, text.c_str(),
				static_cast<SDL_Colour>(foreground), warpLength));
		}

		Surface Font::renderUnicodeSolid(const std::wstring & text, const Colour & foreground)
		{
			return createComponent<Surface>(TTF_RenderUNICODE_Solid(&*this->componentInstance, reinterpret_cast<const uint16_t*>(text.c_str()),
				static_cast<SDL_Colour>(foreground)));
		}

		Surface Font::renderUnicodeShaded(const std::wstring & text, const Colour & foreground, const Colour & background)
		{
			return createComponent<Surface>(TTF_RenderUNICODE_Shaded(&*this->componentInstance, reinterpret_cast<const uint16_t*>(text.c_str()),
				static_cast<SDL_Colour>(foreground), static_cast<SDL_Colour>(background)));
		}

		Surface Font::renderUnicodeBlended(const std::wstring & text, const Colour & foreground)
		{
			return createComponent<Surface>(TTF_RenderUNICODE_Blended(&*this->componentInstance, reinterpret_cast<const uint16_t*>(text.c_str()),
				static_cast<SDL_Colour>(foreground)));
		}

		Surface Font::renderUnicodeBlended(const std::wstring & text, const Colour & foreground, uint32_t warpLength)
		{
			return createComponent<Surface>(TTF_RenderUNICODE_Blended_Wrapped(&*this->componentInstance, reinterpret_cast<const uint16_t*>(text.c_str()),
				static_cast<SDL_Colour>(foreground), warpLength));
		}

		Surface Font::renderGlyphSolid(uint16_t ch, const Colour & foreground)
		{
			return createComponent<Surface>(TTF_RenderGlyph_Solid(&*this->componentInstance, ch, static_cast<SDL_Colour>(foreground)));
		}

		Surface Font::renderGlyphShaded(uint16_t ch, const Colour & foreground, const Colour & background)
		{
			return createComponent<Surface>(TTF_RenderGlyph_Shaded(&*this->componentInstance, ch, static_cast<SDL_Colour>(foreground), static_cast<SDL_Colour>(background)));
		}

		Surface Font::renderGlyphBlended(uint16_t ch, const Colour & foreground)
		{
			return createComponent<Surface>(TTF_RenderGlyph_Blended(&*this->componentInstance, ch, static_cast<SDL_Colour>(foreground)));
		}

		Font & Font::operator=(const Font & rhs)
		{
			this->componentInstance = rhs.componentInstance;
			return *this;
		}

		Font & Font::operator=(Font && rhs)
		{
			this->componentInstance = std::move(rhs.componentInstance);
			return *this;
		}

		Font & Font::operator=(std::nullptr_t)
		{
			this->componentInstance = nullptr;
			return *this;
		}

		void Font::VAS_PROTOTYPE_DEFINE_DEF_DELETER(TTF_Font)
		{
			TTF_CloseFont(instance);
		}
	}
}