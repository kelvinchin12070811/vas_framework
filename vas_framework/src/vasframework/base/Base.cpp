//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include <boost/assert.hpp>
#include <thread>
#include "Base.hpp"
#include "../util/TextTools.hpp"
#include "../manager/SceneManager.hpp"
#include "../manager/ScreenManager.hpp"
#include "../manager/TextureManager.hpp"
#include "../manager/InputManager.hpp"
#include "../manager/AudioManger.hpp"
#include "../manager/FontCacheManager.hpp"
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
		window = sdl::Window{ windowTitle, size, flags };
		if (window == sdl::nullcomponent)
			throw sdl::SDLCoreException{};
		renderer = sdl::Renderer{ window, sdl::Renderer::defIndex, sdl::Renderer::RendererFlags::accelerated };
		if (renderer == sdl::nullcomponent)
			throw sdl::SDLCoreException{};

		if (initializer != nullptr)
			initializer();

		startGameLoop();
		cleanAndQuit();
	}

	void Base::init()
	{
		using namespace std::chrono_literals;
		if (!sdl::init()) throw sdl::SDLCoreException{};
		if (!sdl::image::init()) throw sdl::SDLCoreException{};
#ifdef VAS_USE_TTF
		if (!sdl::ttf::init()) throw sdl::SDLCoreException{};
#endif // VAS_USE_TTF

#ifdef VAS_USE_MIXER
		if (!sdl::mixer::init()) throw sdl::SDLCoreException{};
		if (!sdl::mixer::openAudio()) throw sdl::SDLCoreException{};
#endif // VAS_USE_MIXER

		timePerTick = 1000000000.0 / fps;
		frameIndex.setAutoResetLimit(fps);
	}

	void Base::init(size_t fps)
	{
		this->fps = fps;
		init();
	}

	void Base::startGameLoop()
	{
		using namespace std::chrono_literals;
		if (window == sdl::nullcomponent)
			throw std::logic_error{ "Unable to start game loop scene window instance is nullptr" };
		window.show();

		if (renderer == sdl::nullcomponent)
			throw std::logic_error{ "Unable to start game loop scene renderer instance is nullptr" };
		{
			auto canvasSize = renderer.getLogicalSize();
			if (canvasSize.x == 0 && canvasSize.y == 0)
				canvasSize = window.getSize();

			Camera::getInstance().setSize(canvasSize);
		}
		InputManager::getInstance().init(&ev);
		Clock gameLoopClock;
		std::chrono::nanoseconds timer{ 0 };

		while (exec)
		{
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
					InputManager::getInstance().MouseButtonPressed(static_cast<sdl::MouseButtonIndex>(ev.button().button),
						sdl::Point{ ev.button().x, ev.button().y });
					break;
				case sdl::EventType::mousebuttonup:
					InputManager::getInstance().MouseButtonReleased(static_cast<sdl::MouseButtonIndex>(ev.button().button),
						sdl::Point{ ev.button().x, ev.button().y });
					break;
				case sdl::EventType::mousemotion:
					InputManager::getInstance().__setMousePosition({ ev.motion().x, ev.motion().y });
					InputManager::getInstance().__setRealMousePosition({ ev.motion().xrel, ev.motion().yrel });
					InputManager::getInstance().MouseMoved(ev.motion().x, ev.motion().y);
					break;
				case sdl::EventType::mousewheel:
					InputManager::getInstance().MouseWheelMoved(static_cast<sdl::MouseWheelDirection>(ev.wheel().direction),
						sdl::Point{ ev.wheel().x, ev.wheel().y });
					break;
				}
				if (!exec) break;
				EventCompleateProcessed(ev);
			}
			if (!exec) break;

			auto curTicks = gameLoopClock.reset();
			deltaTime += curTicks.count() / timePerTick;
			timer += curTicks;

			if (deltaTime >= 1.0)
			{
				tick();
				draw();
				frameIndex++;
				fpsCounter++;
#ifdef VAS_AUTO_FRAME_PATCH
				deltaTime--;
#else
				deltaTime = 0.0;
#endif // VAS_AUTO_FRAME_RECOVER
			}
			if (timer >= 1s)
			{
				lastFpsCount = static_cast<size_t>(fpsCounter);
				fpsCounter.reset();
				timer = 0s;
			}
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

		TextureManager::getInstance().clear();
#ifdef VAS_USE_MIXER
		AudioManager::getInstance().clear();
		sdl::mixer::quit();
#endif // VAS_USE_MIXER

#ifdef VAS_USE_TTF
		if (!FontCacheManager::getInstance().isFontCacheEmpty())
			FontCacheManager::getInstance().clearFont();
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

	vas::Camera & Base::getCamera()
	{
		return camera;
	}

	void Base::fun20181130T171403(std::vector<std::string> arg1)
	{
		args = std::move(arg1);
	}

	std::optional<std::reference_wrapper<const std::vector<std::string>>> Base::getArgs()
	{
#ifdef VAS_USE_OOENTRY
		return args;
#else
		return std::nullopt;
#endif
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
		if (fps == value) return;
		fps = value;
		timePerTick =  1000000000.0 / fps;
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

	double Base::getDeltaTime()
	{
		return deltaTime;
	}

	void Base::tick()
	{
		InputManager::getInstance().tick();
		
		if (!SceneManager::getInstance().isEmpty())
		{
			auto scene = SceneManager::getInstance().current();
			if (!scene->isPaused()) //Tick only if scene is not paused for ticking.
			{
				if (ScreenManager::getInstance().WaitFadingCompleate) // If waiting ScreenManager to compleate fading
				{
					if (ScreenManager::getInstance().getCurrentFadingState() == ScreenManager::FadingState::none)
						scene->tick();
				}
				else // if not wait for ScreenManager conpleate fading
					scene->tick();
			}
		}
		ScreenManager::getInstance().tick();
	}

	void Base::draw()
	{
		renderer.clear();
		if (!SceneManager::getInstance().isEmpty())
		{
			SceneManager::getInstance().current()->draw();
		}
		ScreenManager::getInstance().draw();
		renderer.present();
	}
}

#ifdef VAS_USE_OOENTRY
int(*vas::ClassLoader::gt5d_acfg)(const std::vector<std::string>&);

#ifdef VAS_SDL_MAIN_DEFINED
int SDL_main(int argc, char ** argv)
#else
int main(int argc, char** argv)
#endif // VAS_SDL_MAIN_DEFINED
{
	BOOST_ASSERT_MSG(vas::ClassLoader::gt5d_acfg != nullptr, "Unable to locate launcher class, launcher class not defined.");

	std::vector<std::string> args;
	args.reserve(argc);
	for (int itr{ 0 }; itr < argc; itr++)
		args.push_back(argv[itr]);

	vas::Base::getInstance().fun20181130T171403(std::move(args));
	return vas::ClassLoader::gt5d_acfg(vas::Base::getInstance().getArgs()->get());
}
#endif // VAS_USE_OOENTRY