//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "TextureManager.hpp"

namespace vas
{
	TextureManager & TextureManager::getInstance()
	{
		static TextureManager instance;
		return instance;
	}

	sdl::Texture TextureManager::get(const std::string & id)
	{
		auto result = cache.find(id);
		if (result == cache.end()) return sdl::Texture{};
		return result->second;
	}

	bool TextureManager::insert(const std::string & id, const sdl::Texture & instance)
	{
		auto result = cache.insert({ id, instance });
		return result.second;
	}

	bool TextureManager::insert(const std::string & id, sdl::Texture && instance)
	{
		auto result = cache.insert({ id, std::move(instance) });
		return result.second;
	}

	bool TextureManager::has(const std::string & id)
	{
		auto result = cache.find(id);
		return result != cache.end();
	}

	void TextureManager::clear()
	{
		cache.clear();
	}

	size_t TextureManager::cacheCount()
	{
		return cache.size();
	}

	bool TextureManager::isEmpty()
	{
		return cache.empty();
	}

	std::map<std::string, sdl::Texture>& TextureManager::getCache()
	{
		return cache;
	}

	TextureManager::TextureManager()
	{
	}

	TextureManager::~TextureManager()
	{
	}
}