#pragma once
#include <chrono>
#include <boost/signals2.hpp>
#include "../sdlcore/video/Renderer.hpp"
#include "../graphics/sprites/Sprite.hpp"
#include "../graphics/layer/Layers.hpp"

namespace vas
{
	class VAS_DECLSPEC ScreenManager
	{
	public:
		enum class FadingState : uint8_t { none, fade_in, fade_out };
	public:
		static ScreenManager& getInstance();

		void tick();
		void draw();

		//DrawAble object that will render on top of screen but bellow master overlay
		vas::Layers screenOverlays;
		//DrawAble object that will render on top of every thing include master overlay
		vas::Layers screenAboveOverlays;

		sdl::Colour getMasterOverlayColour();
		void setMasterOverlayColour(const sdl::Colour& colour);

		uint8_t getScreenOpacity();
		void setScreenOpacity(uint8_t value);

		void fadeScreen(ScreenManager::FadingState fadeType, const std::chrono::milliseconds& time);

		ScreenManager::FadingState getCurrentFadingState();
	public:
		bool WaitFadingCompleate{ false };
		boost::signals2::signal<void(ScreenManager::FadingState)> Signal_FadeBegin;
		boost::signals2::signal<void(ScreenManager::FadingState)> Signal_FadeEnd;
	private:
		ScreenManager();
		~ScreenManager();

		void fader();
	private:
		sdl::Texture screenMasterOverlay;
		sdl::Renderer masterRenderer;
		sdl::Colour masterOverlayColour{ 255, 255, 255, 255};
		FadingState currentState{ FadingState::none };
		std::chrono::milliseconds fadingDuration;
		double screenOpacityBuffer{ 0.0f };
		double screenOpacityDelta{ 0.0f };
	};
}