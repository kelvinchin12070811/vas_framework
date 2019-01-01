//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <chrono>
#include <boost/signals2.hpp>
#include "../sdlcore/video/Renderer.hpp"
#include "../graphics/sprites/Sprite.hpp"
#include "../graphics/layer/Layers.hpp"

namespace vas
{
	/** @addtogroup managers
		  @{
	*/
	/** @brief The screen controller.
		  
		  ScreenManager is the manager object that control the state of the screen. This included all textures that will
		  be drawn on top of all sceen. The ScreenManager managing a set of DrawAble objects that will be draw on
		  top of all objects and also manage the master overlay which is the screen object.

		  The master overlay is a generated texture with black background colour which typicaly transperent (with the
		  opacity of 0). The opacity of the screen object is inverted compare to other textures' colour mod. For example,
		  when the screen have the opacity of 255, the master overlay's opacity will be set to 0.

		  The ScreenManager are able to accept and manage two seperated layers of DrawAble object which will be
		  draw on top of everything which is screen overlays and screen above overlays. The screen overlays' object will
		  drawn on top of all scene and bellow the master overlay, however screen above overlays will be draw on top
		  of all object included master overlay.
	*/
	class VAS_DECLSPEC ScreenManager
	{ /** @} */
	public:
		/** Fadding state of the screen. */
		enum class FadingState : uint8_t {
			none, /**< No fadding effect */
			fade_in, /**< Fadding screen in (alpha 0 -> 255) */
			fade_out /**< Fadding screen out (alpha 255 -> 0) */
		};
	public:
		static ScreenManager& getInstance();

		void tick();
		void draw();

		/** DrawAble object that will render on top of screen but bellow master overlay. */
		vas::Layers screenOverlays;
		/** DrawAble object that will render on top of everything include master overlay. */
		vas::Layers screenAboveOverlays;

		sdl::Colour getMasterOverlayColour(); /**< Get the colour of master overlay. */
		void setMasterOverlayColour(sdl::Colour colour); /**< Set the colour of master overlay. */

		uint8_t getScreenOpacity(); /**< Get the screen opacity. */
		void setScreenOpacity(uint8_t value); /**< Set the screen opacity. */

		/** Fade the screen.
			  @param fadeType Type of fading.
			  @param time Duration of fading in miliseconds.
		*/
		void fadeScreen(ScreenManager::FadingState fadeType, const std::chrono::milliseconds& time);

		ScreenManager::FadingState getCurrentFadingState(); /**< Get current fading state. */
	public:
		bool WaitFadingCompleate{ false }; /**< Halt the ticking process untill the fadding process compleate if true. */
		/** @name Signals
			  @{
		*/
		/** Fired when screen fading begin.
				
			Arguments:
			-# __ScreenManager::FadingState__\n
				State of the fading process.
		*/
		boost::signals2::signal<void(ScreenManager::FadingState)> FadeBegin;
		/** Fired when screen fading end.

			Arguments:
			-# __ScreenManager::FadingState__\n
				State of the fading process.
		*/
		boost::signals2::signal<void(ScreenManager::FadingState)> FadeEnd;
		/** @} */
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