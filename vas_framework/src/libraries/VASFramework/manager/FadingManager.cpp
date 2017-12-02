#include "FadingManager.hpp"
#include "../util/SDLFunctionBridge.hpp"
#include "../base/Base.hpp"
#include <stdexcept>

namespace vas
{
	FadingManager & FadingManager::getInstance()
	{
		static FadingManager instance;
		return instance;
	}

	void FadingManager::createTexture()
	{
		std::shared_ptr<SDL_Surface> backgroundSurface = SDLFunctionBridge::newSDLSurface(SDL_CreateRGBSurface(0, 256, 256, 32, 0, 0, 0, 0));
		if (backgroundSurface == nullptr)
			throw std::runtime_error(SDL_GetError());

		background = SDLFunctionBridge::newSDLTexture(SDL_CreateTextureFromSurface(Base::getInstance().getRenderer().get(), backgroundSurface.get()));
		if (background == nullptr)
			throw std::runtime_error(SDL_GetError());

		SDL_SetTextureBlendMode(background.get(), SDL_BlendMode::SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(background.get(), this->colourBlend.alpha);
		setScreenOpacity(255);
	}

	void FadingManager::tick()
	{
		switch (effect)
		{
		case FadingType::fadeIn:
			fadeIn();
			break;
		case FadingType::fadeOut:
			fadeOut();
			break;
		}
	}

	void FadingManager::draw()
	{
		if (background != nullptr)
			if (SDL_RenderCopy(Base::getInstance().getRenderer().get(), background.get(), nullptr, nullptr) != 0)
				throw std::runtime_error(SDL_GetError());
	}

	void FadingManager::fadeInScreen(float time)
	{
		effect = FadingType::fadeIn;
		fadingTime = static_cast<uint32_t>(time * Base::getInstance().getFPS());
		if (fadingTime == 0) fadingTime = 1;
	}

	void FadingManager::fadeOutScreen(float time)
	{
		effect = FadingType::fadeOut;
		fadingTime = static_cast<int32_t>(time * Base::getInstance().getFPS());
		if (fadingTime == 0) fadingTime = 1;
	}

	void FadingManager::forceComplete()
	{
		if (effect == FadingType::nofading) return;
		effect = FadingType::nofading;
		frameCounter = 0;
		fadingTime = 0;
	}

	void FadingManager::setScreenOpacity(uint8_t opacity)
	{
		colourBlend.alpha = 255 - opacity;
		SDL_SetTextureAlphaMod(background.get(), colourBlend.alpha);
	}

	uint8_t FadingManager::getScreenOpacity()
	{
		return 255 - colourBlend.alpha;
	}

	bool FadingManager::isFading()
	{
		return effect != FadingType::nofading;
	}

	Colour & FadingManager::getColourBlend()
	{
		return colourBlend;
	}

	FadingManager::FadingManager()
	{
		if (background == nullptr)
			createTexture();
	}


	FadingManager::~FadingManager()
	{
	}

	void FadingManager::fadeIn()
	{
		colourBlend.alpha = 0;
		if (frameCounter == 0)
			colourBlend.alpha = 255 - static_cast<uint8_t>((1.0f / fadingTime) * 255.0f);
		else
			colourBlend.alpha = 255 - static_cast<uint8_t>((static_cast<float>(frameCounter) / static_cast<float>(fadingTime)) * 255.0f);

		SDL_SetTextureAlphaMod(background.get(), colourBlend.alpha);
		SDL_SetTextureColorMod(background.get(), colourBlend.red, colourBlend.green, colourBlend.bule);

		if (frameCounter == fadingTime)
		{
			effect = FadingType::nofading;
			frameCounter = 0;
			fadingTime = 0;
		}
		else frameCounter++;
	}

	void FadingManager::fadeOut()
	{
		colourBlend.alpha = 0;
		if (frameCounter == 0)
			colourBlend.alpha = static_cast<uint8_t>((1.0f / fadingTime) * 255.0f);
		else
			colourBlend.alpha = static_cast<uint8_t>((static_cast<float>(frameCounter) / static_cast<float>(fadingTime)) * 255.0f);

		SDL_SetTextureAlphaMod(background.get(), colourBlend.alpha);
		SDL_SetTextureColorMod(background.get(), colourBlend.red, colourBlend.green, colourBlend.bule);

		if (frameCounter == fadingTime)
		{
			effect = FadingType::nofading;
			frameCounter = 0;
			fadingTime = 0;
		}
		else frameCounter++;
	}
}