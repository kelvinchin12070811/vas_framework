#include "Base.hpp"
#include "../manager/SceneManager.hpp"

namespace vas
{
	Base & Base::getInstance()
	{
		static Base instance;
		return instance;
	}

	void Base::init()
	{
		if (!sdl::init()) throw sdl::SDLCoreException();
		if (!sdl::ttf::init()) throw sdl::SDLCoreException();
		if (!sdl::image::init()) throw sdl::SDLCoreException();
		if (!sdl::mixer::init()) throw sdl::SDLCoreException();

		if (!sdl::mixer::openAudio()) throw sdl::SDLCoreException();
	}

	void Base::startGameLoop()
	{
		if (!mainWindow)
			throw std::runtime_error("Unable to start game loop scene window instance is nullptr");
		mainWindow.show();

		sdl::Event ev;
		while (exec)
		{
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
		}
		mainWindow.destroy();
		sdl::mixer::closeAudio();
		SceneManager::getInstance().clear();
	}

	void Base::cleanAndQuit()
	{
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
}