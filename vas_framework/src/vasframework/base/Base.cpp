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
		window = sdl::Window(windowTitle, size, flags);
		if (window == sdl::emptycomponent)
			throw sdl::SDLCoreException();
		renderer = sdl::Renderer(window, sdl::Renderer::defIndex, sdl::Renderer::RendererFlags::accelerated);
		if (renderer == sdl::emptycomponent)
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
		if (!window)
			throw std::runtime_error("Unable to start game loop scene window instance is nullptr");
		window.show();

		frameCounterUpdater.start();

		if (!renderer)
			throw std::runtime_error("Unable to start game loop scene renderer instance is nullptr");

		{
			auto canvasSize = renderer.getLogicalSize();
			if (canvasSize.x == 0 && canvasSize.y == 0)
				canvasSize = window.getSize();

			Camera::getInstance().setSize(canvasSize);
		}
		InputManager::getInstance().init(&ev);
		while (exec)
		{
			gameLoopClock.justReset();
			while (ev.pollEvent())
			{
				EventBeginProcessed(ev);
				switch (ev)
				{
				case sdl::EventType::quit:
					if (ignoreCloseEventOnce)
						ignoreCloseEventOnce = false;
					else
						exec = false;
					break;
				case sdl::EventType::keydown:
					InputManager::getInstance().KeyPressed(static_cast<sdl::Keycode>(ev.key().keysym.sym));
					break;
				case sdl::EventType::keyup:
					InputManager::getInstance().KeyReleased(static_cast<sdl::Keycode>(ev.key().keysym.sym));
					break;
				case sdl::EventType::mousebuttondown:
					InputManager::getInstance().MouseButtonPressed(static_cast<sdl::MouseButtonIndex>(ev.button().button), sdl::Point(ev.button().x, ev.button().y));
					break;
				case sdl::EventType::mousebuttonup:
					InputManager::getInstance().MouseButtonReleased(static_cast<sdl::MouseButtonIndex>(ev.button().button), sdl::Point(ev.button().x, ev.button().y));
					break;
				case sdl::EventType::mousemotion:
					InputManager::getInstance().setMousePosition(sdl::Point(ev.motion().x, ev.motion().y));
					InputManager::getInstance().MouseMoved(ev.motion().x, ev.motion().y);
					break;
				case sdl::EventType::mousewheel:
					InputManager::getInstance().MouseWheelMoved(static_cast<sdl::MouseWheelDirection>(ev.wheel().direction), sdl::Point(std::abs(ev.wheel().x), std::abs(ev.wheel().y)));
					break;
				}
				if (!exec) break;
				EventCompleateProcessed(ev);
			}
			if (!exec) break;

			tick();
			draw();
			delay();
		}

		window.destroy();
#ifdef VAS_USE_MIXER
		sdl::mixer::closeAudio();
#endif // VAS_USE_MIXER
		SceneManager::getInstance().clear();
	}

	void Base::cleanAndQuit()
	{
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

	bool Base::isExecuting()
	{
		return exec;
	}

	void Base::setIgnoreCloseEventOnce(bool value)
	{
		ignoreCloseEventOnce = value;
	}

	void Base::setDoubleSceneRendering(bool value)
	{
		doubleSceneRendering = value;
	}

	bool & Base::getDoubleSceneRendering()
	{
		return doubleSceneRendering;
	}

	void Base::setWindow(sdl::Window value)
	{
		if (this->window != value)
			window = std::move(value);
	}

	sdl::Window Base::getWindow()
	{
		return window;
	}

	void Base::setRenderer(sdl::Renderer value)
	{
		if (renderer != value)
			renderer = std::move(value);
	}

	sdl::Renderer Base::getRenderer()
	{
		return renderer;
	}

	size_t Base::getCurFrameIndex()
	{
		return static_cast<size_t>(frameIndex);
	}

	size_t Base::getLastFpsCount()
	{
		return lastFpsCount;
	}

	void Base::setFPS(size_t value)
	{
		using namespace std::chrono_literals;
		if (fps == value) return;
		fps = value;
		frameStayTime = 1000ms / fps;
		frameIndex.setAutoResetLimit(fps);

		FPSChanged(value);
	}

	size_t Base::getFPS()
	{
		return fps;
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
		renderer.clear();
		if (!SceneManager::getInstance().isEmpty())
		{
			if (doubleSceneRendering && SceneManager::getInstance().atleast2Scene())
				SceneManager::getInstance().previous()->draw();
			SceneManager::getInstance().current()->draw();
		}
		ScreenManager::getInstance().draw();
		renderer.present();
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