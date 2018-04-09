#include "ScreenManager.hpp"
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
		if (!screenOverlays.isEmpty())
			for (auto& itr : screenOverlays)
			{
				if (itr.second != nullptr)
					itr.second->tick();
			}

		if (!screenAboveOverlays.isEmpty())
			for (auto& itr : screenAboveOverlays)
			{
				if (itr.second != nullptr)
					itr.second->tick();
			}
	}

	void ScreenManager::draw()
	{
		if (!screenOverlays.isEmpty())
			for (auto& itr : screenOverlays)
			{
				if (itr.second != nullptr)
					itr.second->tick();
			}

		if (masterOverlayColour.alpha != 0 && screenMasterOverlay != nullptr)
			masterRenderer.copy(screenMasterOverlay, nullptr, nullptr);

		if (!screenAboveOverlays.isEmpty())
			for (auto& itr : screenAboveOverlays)
			{
				if (itr.second != nullptr)
					itr.second->draw();
			}
	}

	sdl::Colour ScreenManager::getMasterOverlayColour()
	{
		return masterOverlayColour;
	}

	void ScreenManager::setMasterOverlayColour(const sdl::Colour & colour)
	{
		if (masterOverlayColour != colour)
		{
			masterOverlayColour = colour;
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

	ScreenManager::FadingState ScreenManager::getCurrentFadingState()
	{
		return currentState;
	}

	ScreenManager::ScreenManager()
	{
		masterRenderer = Base::getInstance().Renderer();

		screenMasterOverlay = sdl::Texture(masterRenderer, sdl::Surface(0, sdl::Point(32, 32), 32, 0, 0, 0, 0));
		screenMasterOverlay.setBlendMod(sdl::BlendMode::blend);
		screenMasterOverlay.setAlphaMod(255);
		setScreenOpacity(130);
	}

	ScreenManager::~ScreenManager()
	{
	}
}