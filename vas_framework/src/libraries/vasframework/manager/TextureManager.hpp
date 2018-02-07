#pragma once
#include <map>
#include <string>
#include "../VASConfig.hpp"
#include "../sdlcore/SDLCore.hpp"

namespace vas
{
	class VAS_DECLSPEC TextureManager
	{
	public:
		static TextureManager& getInstance();

		sdl::Texture get(const std::string& id);
		bool insert(const std::string& id, const sdl::Texture& instance);
		bool insert(const std::string& id, sdl::Texture&& instance);
		bool has(const std::string& id);

		void clear();
		size_t cacheCount();
		bool isEmpty();

		std::map<std::string, sdl::Texture>& getCache();
	private:
		TextureManager();
		~TextureManager();

		std::map<std::string, sdl::Texture> cache;
	};
}