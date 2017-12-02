#pragma once
#include <SDL.h>
#include <memory>
#include "../math/Colour.hpp"

namespace vas
{
	class FadingManager
	{
	public:
		enum class FadingType : uint8_t { nofading, fadeIn, fadeOut };
		static FadingManager& getInstance();

		void createTexture();

		void tick();
		void draw();

		void fadeInScreen(float time = 0);
		void fadeOutScreen(float time = 0);
		void forceComplete();

		void setScreenOpacity(uint8_t opacity = 0);
		uint8_t getScreenOpacity();

		bool isFading();

		Colour& getColourBlend();
	private:
		FadingManager();
		~FadingManager();

		void fadeIn();
		void fadeOut();

		Colour colourBlend = ColourPresets::white;
		FadingType effect = FadingType::nofading;
		uint32_t fadingTime = 0;
		uint32_t frameCounter = 0;
		std::shared_ptr<SDL_Texture> background = nullptr;
	};
	inline FadingManager& FadingManagerAPI() { return FadingManager::getInstance(); };
}