//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "ResourceMetatype.hpp"
#include "../base/Base.hpp"
#include "../manager/AudioManger.hpp"
#include "../manager/TextureManager.hpp"
#include "../manager/FontCacheManager.hpp"

namespace vas
{
	namespace resource_type
	{
		ResourceMetatype::ResourceMetatype(const std::string & path, const std::string & id,
			std::function<void(ResourceMetatype*)> customLoader) :
			path(path), id(id.empty() ? path : id), customLoader(std::move(customLoader))
		{
		}

		Music::Music(const std::string & path, const std::string & id,
			std::function<void(ResourceMetatype*)> customLoader) :
			ResourceMetatype(path, id, std::move(customLoader))
		{
		}

		void Music::load()
		{
			if (this->customLoader)
			{
				this->customLoader(this);
				return;
			}
			sdl::mixer::Music cache;
			cache.load(path);
			if (cache == sdl::nullcomponent) throw sdl::SDLCoreException();
			AudioManager::getInstance().cacheMusic(id, std::move(cache));
		}

		void Music::unload()
		{
			AudioManager::getInstance().removeMusicFromCache(id);
		}

		Chunk::Chunk(const std::string & path, const std::string & id,
			std::function<void(ResourceMetatype*)> customLoader) :
			ResourceMetatype(path, id, std::move(customLoader))
		{
		}

		void Chunk::load()
		{
			if (this->customLoader)
			{
				this->customLoader(this);
				return;
			}
			sdl::mixer::Chunk cache;
			cache.load(path);
			if (cache == sdl::nullcomponent) throw sdl::SDLCoreException();
			AudioManager::getInstance().cacheChunk(id, std::move(cache));
		}

		void Chunk::unload()
		{
			AudioManager::getInstance().removeChunkFromCache(id);
		}

		Texture::Texture(const std::string & path, const std::string & id,
			std::function<void(ResourceMetatype*)> customLoader) :
			ResourceMetatype(path, id, std::move(customLoader))
		{
		}

		void Texture::load()
		{
			if (this->customLoader)
			{
				this->customLoader(this);
				return;
			}
			sdl::Texture cache;
			cache.loadImage(Base::getInstance().getRenderer(), path);
			if (cache == sdl::nullcomponent) throw sdl::SDLCoreException();
			TextureManager::getInstance().insert(id, std::move(cache));
		}

		void Texture::unload()
		{
			TextureManager::getInstance().getCache().erase(this->id);
		}
		
		Fonts::Fonts(const std::string & path, uint32_t size, const std::string & id,
			std::function<void(ResourceMetatype*)> customLoader):
			ResourceMetatype(path, id, std::move(customLoader)), size(size)
		{
		}
		
		void Fonts::load()
		{
			if (this->customLoader)
			{
				this->customLoader(this);
				return;
			}
			sdl::ttf::Font font;
			font.openFont(this->path, size);
			FontCacheManager::getInstance().insertFont(this->id, size, std::move(font));
		}
		
		void Fonts::unload()
		{
			FontCacheManager::getInstance().clearFont(this->id, size);
		}
	}
}