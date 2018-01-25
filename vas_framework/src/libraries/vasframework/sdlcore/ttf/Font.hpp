#pragma once
#include <SDL_ttf.h>
#include "../../VASConfig.hpp"
#include "../SDLComponentBase.hpp"
#include "../RWops.hpp"
#include "Flags.hpp"
#include "../../container/Switch.hpp"

namespace sdl
{
	namespace ttf
	{
		class Font : public SDLComponentBase<TTF_Font, Font>
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

			vas::Switch getFontKerning();
			void setFontKerning(vas::Switch value);

			int fontHeight();
			int fontAscent();
			int fontDescent();
			int fontLineSkip();

			Font& operator=(const Font& rhs);
			Font& operator=(Font&& rhs);
			Font& operator=(std::nullptr_t);

			static void VAS_PROTOTYPE_DEFINE_DEF_DELETER(TTF_Font);
		};
	}
}