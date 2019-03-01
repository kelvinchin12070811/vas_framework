//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "ResourceMetatype.hpp"
#include "../base/Base.hpp"
#include "../manager/AudioManger.hpp"
#include "../manager/TextureManager.hpp"

namespace vas
{
	namespace resource_type
	{
		ResourceMetatype::ResourceMetatype(const std::string & path, const std::string & id) :
			path(path), id(id.empty() ? path : id)
		{
		}

		Music::Music(const std::string & path, const std::string & id) :
			ResourceMetatype(path, id)
		{
		}

		void Music::load()
		{
			sdl::mixer::Music cache;
			cache.load(path);
			if (cache == sdl::nullcomponent) throw sdl::SDLCoreException();
			AudioManager::getInstance().cacheMusic(id, std::move(cache));
		}

		void Music::unload()
		{
			AudioManager::getInstance().removeMusicFromCache(id);
		}

		Chunk::Chunk(const std::string & path, const std::string & id) :
			ResourceMetatype(path, id)
		{
		}

		void Chunk::load()
		{
			sdl::mixer::Chunk cache;
			cache.load(path);
			if (cache == sdl::nullcomponent) throw sdl::SDLCoreException();
			AudioManager::getInstance().cacheChunk(id, std::move(cache));
		}

		void Chunk::unload()
		{
			AudioManager::getInstance().removeChunkFromCache(id);
		}

		Texture::Texture(const std::string & path, const std::string & id) :
			ResourceMetatype(path, id)
		{
		}

		void Texture::load()
		{
			sdl::Texture cache;
			cache.loadImage(Base::getInstance().getRenderer(), path);
			if (cache == sdl::nullcomponent) throw sdl::SDLCoreException();
			TextureManager::getInstance().insert(id, std::move(cache));
		}

		void Texture::unload()
		{
			TextureManager::getInstance().getCache().erase(this->id);
		}
	}
}