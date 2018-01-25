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

		vas::Switch Font::getFontKerning()
		{
			return TTF_GetFontKerning(&*this->componentInstance);
		}

		void Font::setFontKerning(vas::Switch value)
		{
			TTF_SetFontKerning(&*this->componentInstance, value == on ? 1 : 0);
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