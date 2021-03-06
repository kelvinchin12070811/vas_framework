//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include <boost/algorithm/clamp.hpp>
#include "ScreenManager.hpp"
#include "SceneManager.hpp"
#include "../base/Base.hpp"

namespace vas
{
	ScreenManager & ScreenManager::getInstance()
	{
		static ScreenManager instance;
		return instance;
	}

	void ScreenManager::tick()
	{
		if (currentState != ScreenManager::FadingState::none) fader();

		if (!screenOverlays.isEmpty())
			for (auto& itr : screenOverlays)
			{
				if (itr.instance != nullptr)
					itr.instance->tick();
			}

		if (auto scene = SceneManager::getInstance().current(); scene != nullptr)
		{
			if (auto gui = scene->getGuiPanel(); gui != nullptr)
				gui->tick();
		}

		if (!screenAboveOverlays.isEmpty())
			for (auto& itr : screenAboveOverlays)
			{
				if (itr.instance != nullptr)
					itr.instance->tick();
			}
	}

	void ScreenManager::draw()
	{
		if (!screenOverlays.isEmpty())
			for (auto& itr : screenOverlays)
			{
				if (itr.instance != nullptr)
					itr.instance->draw();
			}

		if (masterOverlayColour.alpha != 0 && screenMasterOverlay != sdl::nullcomponent)
			masterRenderer.copy(screenMasterOverlay, nullptr, nullptr);

		if (auto scene = SceneManager::getInstance().current(); scene != nullptr)
		{
			if (auto gui = scene->getGuiPanel(); gui != nullptr)
				gui->draw(&masterRenderer);
		}

		if (!screenAboveOverlays.isEmpty())
			for (auto& itr : screenAboveOverlays)
			{
				if (itr.instance != nullptr)
					itr.instance->draw();
			}
	}

	sdl::Colour ScreenManager::getMasterOverlayColour()
	{
		return masterOverlayColour;
	}

	void ScreenManager::setMasterOverlayColour(sdl::Colour colour)
	{
		if (masterOverlayColour != colour)
		{
			masterOverlayColour = std::move(colour);
			screenMasterOverlay.setColorMod(masterOverlayColour.red, masterOverlayColour.green, masterOverlayColour.bule);
			screenMasterOverlay.setAlphaMod(255 - masterOverlayColour.alpha);
		}
	}

	uint8_t ScreenManager::getScreenOpacity()
	{
		return 255 - masterOverlayColour.alpha;
	}

	void ScreenManager::setScreenOpacity(uint8_t value)
	{
		masterOverlayColour.alpha = 255 - value;
		screenMasterOverlay.setAlphaMod(masterOverlayColour.alpha);
	}

	void ScreenManager::fadeScreen(ScreenManager::FadingState fadeType, const std::chrono::milliseconds & time)
	{
		using namespace std::chrono_literals;
		fadingDuration = time;
		currentState = fadeType;
		screenOpacityBuffer = static_cast<double>(getScreenOpacity());
		screenOpacityDelta = 255.0 / static_cast<double>(
			std::chrono::duration_cast<std::chrono::seconds>(time).count() * Base::getInstance().getFPS()
			);
		FadeBegin(fadeType);
	}

	ScreenManager::FadingState ScreenManager::getCurrentFadingState()
	{
		return currentState;
	}

	ScreenManager::ScreenManager()
	{
		masterRenderer = Base::getInstance().getRenderer();

		screenMasterOverlay = sdl::Texture(masterRenderer, sdl::Surface(0, sdl::Point(32, 32), 32, 0, 0, 0, 0));
		screenMasterOverlay.setBlendMod(sdl::BlendMode::blend);
		screenMasterOverlay.setAlphaMod(255);
		setScreenOpacity(255);
	}

	ScreenManager::~ScreenManager()
	{
	}

	void ScreenManager::fader()
	{
		using namespace std::chrono_literals;
		
		switch (currentState)
		{
		case vas::ScreenManager::FadingState::fade_in:
			if (screenOpacityBuffer == 255.0f)
				setScreenOpacity(0);

			screenOpacityBuffer += screenOpacityDelta;
			screenOpacityBuffer = boost::algorithm::clamp(screenOpacityBuffer, 0.0f, 255.0f);
			setScreenOpacity(static_cast<uint8_t>(screenOpacityBuffer));
			if (screenOpacityBuffer == 255.0f)
			{
				currentState = ScreenManager::FadingState::none;
				FadeEnd(ScreenManager::FadingState::fade_in);
			}
			break;
		case vas::ScreenManager::FadingState::fade_out:
			if (screenOpacityBuffer == 0)
				setScreenOpacity(255);

			screenOpacityBuffer -= screenOpacityDelta;
			screenOpacityBuffer = boost::algorithm::clamp(screenOpacityBuffer, 0.0f, 255.0f);
			setScreenOpacity(static_cast<uint8_t>(screenOpacityBuffer));
			if (screenOpacityBuffer == 0.0f)
			{
				currentState = ScreenManager::FadingState::none;
				FadeEnd(ScreenManager::FadingState::fade_out);
			}
			break;
		}
	}
}