//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <map>
#include <string>
#include "../VASConfig.hpp"
#include "../sdlcore/SDLCore.hpp"

namespace vas
{
	/** @addtogroup managers
		  @{
	*/
	/** @brief The texture management object.

		  The TextureManager manage all the cache of the texture. It cached all texture that need to be cached and return it
		  whenever the application request for the same texture. The texture cache is managed automaticaly by the framework
		  but users are able to manually controll it too.
	*/
	class VAS_DECLSPEC TextureManager
	{/** @} */
	public:
		/** Get the unique instance of TextureManager. */
		static TextureManager& getInstance();

		/** Get a cached textrue via it's assigned id.
			  @param id Pre-assigned id that represent a texture.
			  @return Cached instance if success, sdl::nullcomponent if failed.
		*/
		sdl::Texture get(const std::string& id);
		/** Insert an instance of texture into the texture cache.
			  @param id Unique id of the texture.
			  @param instance Instance of the texture.
			  @return true if success, false otherwise.
		*/
		bool insert(const std::string& id, const sdl::Texture& instance);
		/** Insert an instance of texture into the texture cache.
			  @param id Unique id of the texture.
			  @param instance Instance of the texture, instance is moved.
			  @return true if success, false otherwise.
		*/
		bool insert(const std::string& id, sdl::Texture&& instance);
		/** Check if the instance is cached.
			  @param id Unique id of the instance.
			  @return true if instance is cached.
		*/
		bool has(const std::string& id);

		/** Clear the texture cache. */
		void clear();
		/** Number of cache stored. */
		size_t cacheCount();
		/** Check if the cache is empty. */
		bool isEmpty();

		std::map<std::string, sdl::Texture>& getCache();
	private:
		TextureManager();
		~TextureManager();

		/** [Read & Write] The textue cache.
			  - __accessors__
					-# std::map<std::string, sdl::Texture>& getCache()\n
						 This function also act as mutator since it return a reference.
		*/
		std::map<std::string, sdl::Texture> cache;
	};
}