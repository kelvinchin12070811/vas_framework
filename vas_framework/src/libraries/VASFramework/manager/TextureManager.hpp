#pragma once
#include <memory>
#include <map>
#include <string>
#include "../util/SDLFunctionBridge.hpp"

namespace vas
{
	class TextureManager
	{
	public:
		static TextureManager& getInstance();

		bool hasTexture(const std::wstring& path);
		bool empty();
		std::shared_ptr<SDL_Texture> getTexture(const std::wstring& path);
		
		void insertTexture(const std::wstring& path, const std::shared_ptr<SDL_Texture>& instance);
		void insertTexture(const std::wstring& path, std::shared_ptr<SDL_Texture>&& instance);

		void removeTexture(const std::wstring& path);

		size_t getTextureCount();

		std::shared_ptr<SDL_Texture> createTextureFromFile(const std::wstring& path);
		std::shared_ptr<SDL_Texture> createAndInsertTextureFromFileGet(const std::wstring& path);
		void createAndInsertTextureFromFile(const std::wstring& path);
	private:
		TextureManager();
		~TextureManager();

		std::shared_ptr<std::map<std::wstring, std::shared_ptr<SDL_Texture>>> textureCache = nullptr;
	};
	inline TextureManager& TextureManagerAPI() { return TextureManager::getInstance(); };
}