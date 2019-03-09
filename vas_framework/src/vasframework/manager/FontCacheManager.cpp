//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "FontCacheManager.hpp"
#include "../sdlcore/SDLCoreException.hpp"

#ifdef VAS_USE_TTF
namespace vas
{
	FontCacheManager & FontCacheManager::getInstance()
	{
		static FontCacheManager instance;
		return instance;
	}

	bool FontCacheManager::hasFont(const std::string & id, uint32_t size)
	{
		return fonts.find({ id, size }) != fonts.end();
	}

	bool FontCacheManager::insertFont(const std::string & id, uint32_t size)
	{
		sdl::ttf::Font font;
		font.openFont(id, size);
		if (font == sdl::nullcomponent) throw sdl::SDLCoreException{};
		return insertFont(id, size, std::move(font));
	}

	bool FontCacheManager::insertFont(const std::string & id, uint32_t size, sdl::ttf::Font font)
	{
		return fonts.insert({ { id, size }, std::move(font) }).second;
	}

	std::optional<sdl::ttf::Font> FontCacheManager::getFont(const std::string & id, uint32_t size)
	{
		auto result = fonts.find({ id, size });
		if (result == fonts.end()) return std::nullopt;
		return result->second;
	}

	void FontCacheManager::clearFont(const std::string & id, uint32_t size)
	{
		fonts.erase({ id, size });
	}

	void FontCacheManager::clearFont()
	{
		fonts.clear();
	}

	bool FontCacheManager::isFontCacheEmpty()
	{
		return fonts.empty();
	}

	size_t FontCacheManager::fontCacheSize()
	{
		return fonts.size();
	}
}
#endif