#include <thread>
#include "Base.hpp"
#include "../util/TextTools.hpp"
#include "../manager/SceneManager.hpp"
#include "../manager/TextureManager.hpp"

namespace vas
{
	Base & Base::getInstance()
	{
		static Base instance;
		return instance;
	}

	void Base::init()
	{
		using namespace std::chrono_literals;
		if (!sdl::init()) throw sdl::SDLCoreException();
		if (!sdl::ttf::init()) throw sdl::SDLCoreException();
		if (!sdl::image::init()) throw sdl::SDLCoreException();
		if (!sdl::mixer::init()) throw sdl::SDLCoreException();

		if (!sdl::mixer::openAudio()) throw sdl::SDLCoreException();

		frameStayTime = 1000ms / fps;
		frameIndex.setAutoResetLimit(fps);

		frameCounterUpdater.TimedOutSignal().connect(boost::bind(&Base::frameCounter, this));
		frameCounterUpdater.setInterval(1s);
	}

	void Base::init(size_t fps)
	{
		this->fps = fps;
		init();
	}

	void Base::startGameLoop()
	{
		if (!mainWindow)
			throw std::runtime_error("Unable to start game loop scene window instance is nullptr");
		mainWindow.show();

		frameCounterUpdater.start();

		sdl::Event ev;
		while (exec)
		{
			gameLoopClock.justReset();
			while (ev.pollEvent())
			{
				eventProcessorSignals[0](ev);
				switch (ev)
				{
				case sdl::EventType::quit:
					if (ignoreCloseEventOnce)
					{
						ignoreCloseEventOnce = false;
					}
					else
					{
						exec = false;
					}
					break;
				}
				if (!exec) break;
				eventProcessorSignals[1](ev);
			}
			if (!exec) break;

			tick();
			draw();
			delay();
		}

		mainWindow.destroy();
		sdl::mixer::closeAudio();
		SceneManager::getInstance().clear();
	}

	void Base::cleanAndQuit()
	{
		frameCounterUpdater.stop();
		frameCounterUpdater.TimedOutSignal().disconnect_all_slots();
		TextureManager::getInstance().clear();
		sdl::mixer::quit();
		sdl::ttf::quit();
		sdl::image::quit();
		sdl::quit();
	}

	const bool & Base::Exec()
	{
		return exec;
	}

	bool & Base::IgnoreCloseEventOnce()
	{
		return ignoreCloseEventOnce;
	}

	bool & Base::DoubleSceneRendering()
	{
		return doubleSceneRendering;
	}

	sdl::Window & Base::Window()
	{
		return mainWindow;
	}

	sdl::Renderer & Base::Renderer()
	{
		return mainRenderer;
	}

	boost::signals2::signal<void(sdl::Event&)>& Base::EventProcessorSignal(Base::SignalsType::EventProcessor type)
	{
		return eventProcessorSignals[static_cast<uint8_t>(type)];
	}

	const Counter & Base::FrameIndex()
	{
		return frameIndex;
	}

	size_t Base::getLastFpsCount()
	{
		return lastFpsCount;
	}

	Base::Base()
	{
	}

	Base::~Base()
	{
	}

	void Base::tick()
	{
		if (!SceneManager::getInstance().isEmpty())
		{
			SceneManager::getInstance().current()->tick();
		}
	}

	void Base::draw()
	{
		if (!SceneManager::getInstance().isEmpty())
		{
			mainRenderer.clear();
			if (doubleSceneRendering && SceneManager::getInstance().atleast2Scene())
				SceneManager::getInstance().previous()->draw();
			SceneManager::getInstance().current()->draw();
			mainRenderer.present();
		}
	}

	void Base::delay()
	{
		using namespace std::chrono_literals;
		//current loop's used time
		auto crLoopDuration = std::chrono::duration_cast<std::chrono::milliseconds>(gameLoopClock.currentTick());

		frameIndex++;
		fpsCounter++;

		if (crLoopDuration < frameStayTime)
		{
			std::this_thread::sleep_for(frameStayTime - crLoopDuration - 1ms);
		}
	}

	void Base::frameCounter()
	{
		lastFpsCount = fpsCounter;
		fpsCounter.reset();
	}
}