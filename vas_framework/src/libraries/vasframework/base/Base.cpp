#include <thread>
#include "Base.hpp"
#include "../util/TextTools.hpp"
#include "../manager/SceneManager.hpp"
#include "../manager/ScreenManager.hpp"
#include "../manager/TextureManager.hpp"
#include "../manager/InputManager.hpp"
#include "../manager/AudioManger.hpp"
#include "../graphics/Camera.hpp"

namespace vas
{
	Base & Base::getInstance()
	{
		static Base instance;
		return instance;
	}

	void Base::initAndStartAll(const std::string & windowTitle, const sdl::Point & size, uint32_t flags, std::function<void()> initializer)
	{
		init();
		mainWindow = sdl::Window(windowTitle, size, flags);
		if (mainWindow == sdl::emptycomponent)
			throw sdl::SDLCoreException();
		mainRenderer = sdl::Renderer(mainWindow, sdl::Renderer::defIndex, sdl::Renderer::RendererFlags::accelerated);
		if (mainRenderer == sdl::emptycomponent)
			throw sdl::SDLCoreException();

		if (initializer != nullptr)
			initializer();

		startGameLoop();
		cleanAndQuit();
	}

	void Base::init()
	{
		using namespace std::chrono_literals;
		if (!sdl::init()) throw sdl::SDLCoreException();
		if (!sdl::image::init()) throw sdl::SDLCoreException();
#ifdef VAS_USE_TTF
		if (!sdl::ttf::init()) throw sdl::SDLCoreException();
#endif // VAS_USE_TTF

#ifdef VAS_USE_MIXER
		if (!sdl::mixer::init()) throw sdl::SDLCoreException();
		if (!sdl::mixer::openAudio()) throw sdl::SDLCoreException();
#endif // VAS_USE_MIXER

		if (fps == 0)
			frameStayTime = std::chrono::milliseconds::zero();
		else
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

		if (!mainRenderer)
			throw std::runtime_error("Unable to start game loop scene renderer instance is nullptr");

		{
			auto canvasSize = mainRenderer.getLogicalSize();
			if (canvasSize.x == 0 && canvasSize.y == 0)
				canvasSize = mainWindow.getSize();

			Camera::getInstance().setSize(canvasSize);
		}
		InputManager::getInstance().init(&ev);

#ifdef VAS_USE_MULTITHREAD
		std::once_flag drawThreadStarted;
		auto drawCallWrapper = [](std::function<void()> drawFunc, const bool* running)
		{
			while (*running)
			{
				drawFunc();
			}
		};
#endif // VAS_USE_MULTITHREAD
		while (exec)
		{
#ifdef VAS_USE_MULTITHREAD
			using namespace std::chrono;
			auto before = steady_clock::now();
			//std::lock_guard<std::mutex> lock(globalResourcesMutex);
#endif // VAS_USE_MULTITHREAD

			gameLoopClock.justReset();
			while (ev.pollEvent())
			{
				eventProcessorSignals[0](ev);
				switch (ev)
				{
				case sdl::EventType::quit:
					if (ignoreCloseEventOnce)
						ignoreCloseEventOnce = false;
					else
						exec = false;
					break;
				case sdl::EventType::keydown:
					InputManager::getInstance().keyPressed(static_cast<sdl::Keycode>(ev.key().keysym.sym));
					break;
				case sdl::EventType::keyup:
					InputManager::getInstance().keyReleased(static_cast<sdl::Keycode>(ev.key().keysym.sym));
					break;
				case sdl::EventType::mousebuttondown:
					InputManager::getInstance().mouseButtonPressed(ev.button().button, ev.button().x, ev.button().y);
					break;
				case sdl::EventType::mousebuttonup:
					InputManager::getInstance().mouseButtonReleased(ev.button().button, ev.button().x, ev.button().y);
					break;
				case sdl::EventType::mousemotion:
					InputManager::getInstance().setMousePosition(sdl::Point(ev.motion().x, ev.motion().y));
					InputManager::getInstance().mouseMoved(ev.motion().x, ev.motion().y);
					break;
				case sdl::EventType::mousewheel:
					InputManager::getInstance().mouseWheelMoved(static_cast<MouseWheelDirection>(ev.wheel().direction), std::abs(ev.wheel().x), std::abs(ev.wheel().y));
					break;
				}
				if (!exec) break;
				eventProcessorSignals[1](ev);
			}
			if (!exec) break;
			tick();

#ifndef VAS_USE_MULTITHREAD
			draw();
			delay();
#else
			std::call_once(drawThreadStarted, [&](std::thread& drawer, std::function<void()> drawFunc, const bool* running)
			{
				drawer = std::thread(drawCallWrapper, drawFunc, running);
			}, drawThread, std::bind(&Base::draw, this), &exec);

			auto ellapse = steady_clock::now() - before;
			nanoseconds totalTickTime = nanoseconds(nanoseconds(1s) / nanoseconds(tickSpeed));
			if (ellapse < totalTickTime)
			{
				std::this_thread::sleep_for(totalTickTime - ellapse);
			}
#endif // !VAS_USE_MULTITHREAD
		}

		mainWindow.destroy();
#ifdef VAS_USE_MIXER
		sdl::mixer::closeAudio();
#endif // VAS_USE_MIXER
		SceneManager::getInstance().clear();
	}

	void Base::cleanAndQuit()
	{
#ifdef VAS_USE_MULTITHREAD
		if (drawThread.joinable()) drawThread.join();
#endif // VAS_USE_MULTITHREAD

		SceneManager::getInstance().clear();
		ScreenManager::getInstance().screenAboveOverlays.clear();
		ScreenManager::getInstance().screenOverlays.clear();

		frameCounterUpdater.stop();
		frameCounterUpdater.TimedOutSignal().disconnect_all_slots();
		TextureManager::getInstance().clear();
#ifdef VAS_USE_MIXER
		AudioManger::getInstance().clear();
		sdl::mixer::quit();
#endif // VAS_USE_MIXER

#ifdef VAS_USE_TTF
		sdl::ttf::quit();
#endif // VAS_USE_TTF

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

	size_t Base::getFPS()
	{
		return fps;
	}

	size_t Base::getRefreshRate()
	{
#ifndef VAS_USE_MULTITHREAD
		return getFPS();
#else
		return getTickSpeed();
#endif // !VAS_USE_MULTITHREAD
}

	sdl::Event & Base::getEvent()
	{
		return ev;
	}

	Base::Base()
	{
	}

	Base::~Base()
	{
	}

	void Base::tick()
	{
		InputManager::getInstance().tick();
		if (!SceneManager::getInstance().isEmpty())
		{
			if (ScreenManager::getInstance().WaitFadingCompleate) // If waiting ScreenManager to compleate fading
			{
				if (ScreenManager::getInstance().getCurrentFadingState() == ScreenManager::FadingState::none)
					SceneManager::getInstance().current()->tick();
			}
			else // if not wait for ScreenManager conpleate fading
				SceneManager::getInstance().current()->tick();
		}
		ScreenManager::getInstance().tick();
	}

	void Base::draw()
	{
#ifdef VAS_USE_MULTITHREAD
		std::lock_guard<std::mutex> locker(globalResourcesMutex);
#endif // VAS_USE_MULTITHREAD

		mainRenderer.clear();
		if (!SceneManager::getInstance().isEmpty())
		{
			if (doubleSceneRendering && SceneManager::getInstance().atleast2Scene())
				SceneManager::getInstance().previous()->draw();
			SceneManager::getInstance().current()->draw();
		}
		ScreenManager::getInstance().draw();
		mainRenderer.present();

#ifdef VAS_USE_MULTITHREAD
		delay();
#endif // VAS_USE_MULTITHREAD
	}

	void Base::delay()
	{
		using namespace std::chrono_literals;
		//current loop's used time
		auto crLoopDuration = std::chrono::duration_cast<std::chrono::milliseconds>(gameLoopClock.currentTick());

		frameIndex++;
		fpsCounter++;

		if (frameStayTime != frameStayTime.zero() && crLoopDuration < frameStayTime)
		{
			std::this_thread::sleep_for(frameStayTime - crLoopDuration - 1ms);
		}
	}

	void Base::frameCounter()
	{
		lastFpsCount = fpsCounter;
		fpsCounter.reset();
	}

#ifdef VAS_USE_MULTITHREAD
	void Base::setTickSpeed(size_t value)
	{
		this->tickSpeed = value;
	}

	size_t Base::getTickSpeed()
	{
		return tickSpeed;
	}

	std::mutex & Base::getResourceMutex()
	{
		return globalResourcesMutex;
	}
#endif // VAS_USE_MULTITHREAD

}