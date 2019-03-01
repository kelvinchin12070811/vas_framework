#pragma once
#include <map>
#include <string>
#include "../sdlcore/ttf/TTFCore.hpp"
#include "../VASConfig.hpp"

#ifdef VAS_USE_TTF
namespace vas
{
	class FontCacheManager
	{
	public:
		static FontCacheManager& getInstance();

		bool hasFont(const std::string& id, uint32_t size);
		bool insertFont(const std::string& id, uint32_t size);
		bool insertFont(const std::string& id, uint32_t size, sdl::ttf::Font font);
		sdl::ttf::Font getFont(const std::string& id, uint32_t size);
		void clearFont(const std::string& id, uint32_t size);
		void clearFont();
		bool isFontCacheEmpty();
		size_t fontCacheSize();
	private:
		std::map<std::pair<std::string, uint32_t>, sdl::ttf::Font> fonts;
	};
}
#endif