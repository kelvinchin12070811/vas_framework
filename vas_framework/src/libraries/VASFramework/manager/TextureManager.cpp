#include "TextureManager.hpp"
#include "../util/TextTools.hpp"
#include "../base/Base.hpp"

namespace vas
{
	TextureManager & TextureManager::getInstance()
	{
		static TextureManager instance;
		return instance;
	}

	bool TextureManager::hasTexture(const std::wstring & path)
	{
		try
		{
			return textureCache->at(path) == nullptr ? false : true;
		}
		catch (std::out_of_range)
		{
			return false;
		}
	}

	bool TextureManager::empty()
	{
		return textureCache->empty();
	}

	std::shared_ptr<SDL_Texture> TextureManager::getTexture(const std::wstring & path)
	{
		try
		{
			return textureCache->at(path);
		}
		catch (std::out_of_range)
		{
			return nullptr;
		}
	}

	void TextureManager::insertTexture(const std::wstring & path, const std::shared_ptr<SDL_Texture>& instance)
	{
		if (!hasTexture(path))
			textureCache->insert(std::make_pair(path, instance));
	}

	void TextureManager::insertTexture(const std::wstring & path, std::shared_ptr<SDL_Texture>&& instance)
	{
		if (!hasTexture(path))
			textureCache->insert(std::make_pair(path, std::move(instance)));
	}

	void TextureManager::removeTexture(const std::wstring & path)
	{
		textureCache->erase(path);
	}

	size_t TextureManager::getTextureCount()
	{
		return textureCache->size();
	}

	std::shared_ptr<SDL_Texture> TextureManager::createTextureFromFile(const std::wstring & path)
	{
#ifndef SETTINGS_INIT_IMAGE
		throw std::runtime_error(u8"Cannot create texture from file scene image module not inited yet");
#endif // !SETTINGS_INIT_IMAGE

		std::shared_ptr<SDL_Surface> buffer = nullptr;
		buffer = SDLFunctionBridge::newSDLSurface(IMG_Load(str_cast<std::string>(path).c_str()));
		if (buffer == nullptr)
			throw std::runtime_error(SDL_GetError());

		std::shared_ptr<SDL_Texture> tempTexture = nullptr;
		tempTexture = SDLFunctionBridge::newSDLTexture(SDL_CreateTextureFromSurface(Base::getInstance().getRenderer().get(), buffer.get()));
		if (tempTexture == nullptr)
			throw std::runtime_error(SDL_GetError());

		return tempTexture;
	}

	std::shared_ptr<SDL_Texture> TextureManager::createAndInsertTextureFromFileGet(const std::wstring & path)
	{
		if (hasTexture(path))
			return getTexture(path);
		std::shared_ptr<SDL_Texture> temp = createTextureFromFile(path);
		insertTexture(path, temp);
		return temp;
	}

	void TextureManager::createAndInsertTextureFromFile(const std::wstring & path)
	{
		if (hasTexture(path)) return;
		insertTexture(path, createTextureFromFile(path));
	}

	TextureManager::TextureManager()
	{
		textureCache = std::make_shared<std::map<std::wstring, std::shared_ptr<SDL_Texture>>>();
	}

	TextureManager::~TextureManager()
	{
	}
}