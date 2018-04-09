#pragma once
#include "../sdlcore/video/Renderer.hpp"
#include "../graphics/sprites/Sprite.hpp"
#include "../graphics/layer/Layers.hpp"

namespace vas
{
	class ScreenManager
	{
	public:
		enum class FadingState : uint8_t { none, fade_in, fade_out };
		static ScreenManager& getInstance();

		void tick();
		void draw();

		//IRenderAble object that will render on top of screen but bellow master overlay
		vas::Layers screenOverlays;
		//IRenderAble object that will render on top of every thing include master overlay
		vas::Layers screenAboveOverlays;

		sdl::Colour getMasterOverlayColour();
		void setMasterOverlayColour(const sdl::Colour& colour);

		uint8_t getScreenOpacity();
		void setScreenOpacity(uint8_t value);

		ScreenManager::FadingState getCurrentFadingState();
	private:
		ScreenManager();
		~ScreenManager();

		sdl::Texture screenMasterOverlay;
		sdl::Renderer masterRenderer;
		sdl::Colour masterOverlayColour{ 255, 255, 255, 255};
		FadingState currentState = FadingState::none;
	};
}