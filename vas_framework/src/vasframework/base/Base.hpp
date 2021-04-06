//===========================================================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//===========================================================================================================
#pragma once
#include <array>
#include <boost/signals2.hpp>
#include <optional>
#include "../VASConfig.hpp"
#include "../util/TextTools.hpp"
#include "../sdlcore/SDLCore.hpp"
#include "../math/Clock.hpp"
#include "../math/Counter.hpp"
#include "../math/Timer.hpp"
#include "../graphics/Camera.hpp"

#ifdef VAS_WINDOWS_MODE
#include <Windows.h>
#endif // VAS_WINDOWS_MODE

#if defined(main) && !defined(VAS_SDL_ENTRY)
#undef main
#define VAS_SDL_MAIN_DEFINED
#endif

namespace vas
{
	/**
	 * @ingroup vas_framework
	 * @{
	 */
	/**
	 * @brief The core object of the framework.
	 *
	 * Base is the singletone class that drived the skeleton of the framework. It controll the main event loop, signaling and
	 * also handle the main game loop and thread.
	 */
	class VAS_DECLSPEC Base
	{
	public:
		/**
		 * Get the singletone instance of Base class
		 * @return Singletone instance of Base class.
		 */
		static Base& getInstance();
		/**
		 * Initialize every component and start main game loop with default fps (60 fps)
		 * @param[in] windowTitle Title of the window.
		 * @param[in] size Size of the window.
		 * @param[in] flags sdl::Window's flags.
		 * @param[in] initializer Things to init before game loop is started but it need to done after initialzation of library.
		 * @throw vas::sdl::SDLCoreException if creation of sdl::Renderer or sdl::Window failed.
		 */
		void initAndStartAll(const std::string& windowTitle, const sdl::Point& size, uint32_t flags, std::function<void()> initializer = nullptr);

		/**
		 * Initialize all library components with default fps (60 fps).
		 * @throw vas::sdl::SDLCoreException if failed to open SDL libraries.
		 */
		void init();
		/**
		 * Initialize all library components with custom fps
		 * @param[in] fps Maximum fps that libaray need to run at.
		 */
		void init(size_t fps);
		/**
		 * Start the game loop of the application.
		 * This will initialize and start event, event callback loop, ticking loop & drawing loop.
		 * @throw std::logic_error if sdl::Renderer or sdl::Window is not initialized.
		 */
		void startGameLoop();
		/** Clean and exit framework, all resources allocated will be free. */
		void cleanAndQuit();
		
		/**
		 * Check if the app is running.
		 * @return state of the app (is running or not)
		 */
		bool isExecuting();

		void setIgnoreCloseEventOnce(bool value);

		void setWindow(sdl::Window value);
		sdl::Window getWindow();

		void setRenderer(sdl::Renderer value);
		sdl::Renderer getRenderer();

		vas::Camera& getCamera();

		void fun20181130T171403(std::vector<std::string> arg1);

		/**
		 * Get the command line arguments that passed by the operating system.
		 * @retval std::optional Constant reference to the command line argument. Empty ```std::optional```
		 * if #VAS_SDL_ENTRY is defined.
		 */
		std::optional<std::reference_wrapper<const std::vector<std::string>>> getArgs();

		/**
		 * Get currnet frame index.
		 * @return current frame index number which less than or equal to fps.
		 */
		size_t getCurFrameIndex();
		size_t getLastFpsCount();
		void setFPS(size_t value);
		size_t getFPS();
		sdl::Event& getEvent();
		double getDeltaTime();
	private:
		Base() = default;
		~Base() = default;

		void tick();
		void draw();

		bool exec{ true };
		/**
		 * Ignore close event at once, application will ignore sdl::quit event at once if this attribute is true.
		 * This attribute will be reseted if sdl::quit event is fired and if it's true.
		 * ####Mutators
		 * -# void setIgnoreCloseEventOnce(bool value)
		 */
		bool ignoreCloseEventOnce{ false };
		/**
		 * Main window that all main elements to display on.
		 * ####Mutators
		 * -# void setWindow(sdl::Window value)
		 * 
		 * ####Accessors
		 * -# sdl::Window getWindow()
		 */
		sdl::Window window;
		/**
		 * Main render that render all main elements to `window`.
		 * 
		 * ####Mutators
		 * -# void setRenderer(sdl::Renderer value)
		 * 
		 * ####Accessors
		 * -# sdl::Renderer getRenderer()
		 */
		sdl::Renderer renderer;
		/**
		 * Main camera that tell which elements are spoted on the screen.
		 * 
		 * ####Accessors
		 * -# vas::Camera& getCamera()
		 */
		vas::Camera camera;
		/**
		 * Main event loop that handle all of the event from SDL.
		 * 
		 * ####Accessors
		 * -# sdl::Event& getEvent()
		 */
		sdl::Event ev;

		/**
		 * Frame per Seconds (FPS) that VAS Framework will run.
		 * 
		 * ####Mutators
		 * -# void setFPS(size_t value)
		 * 
		 * ####Accessors
		 * -# size_t getFPS()
		 */
		size_t fps{ 60 };
		/**
		 * Get last second's realtime fps count.
		 * 
		 * ####Accessors
		 * -# size_t getLastFpsCount()
		 */
		size_t lastFpsCount{ 0 };
		/**
		 * Get difference in time between last frame and current frame.
		 * 
		 * ####Accessors
		 * -# size_t getDeltaTime()
		 */
		double deltaTime{ 0 };

		std::vector<std::string> args;

		Counter fpsCounter;
		Counter frameIndex;
		double timePerTick{ 0 };
	public: //signals
		/**
		 * @name Signals
		 * @{
		 */
		/**
		 * Fire when an event is started to be processed by the event loop. This is the main signal that use to handle input.
		 * @param sdl::Event& Event loop that used by the main game loop.
		 */
		boost::signals2::signal<void(sdl::Event&)> EventBeginProcessed;
		/**
		 * Fire after an event is processed by the event loop.
		 * @param sdl::Event& Event loop that used by the main game loop.
		 */
		boost::signals2::signal<void(sdl::Event&)> EventCompleateProcessed;
		/**
		 * Fire when the attribute "fps" is changed by using it's mutator.
		 * @param size_t New fps.
		 */
		boost::signals2::signal<void(size_t)> FPSChanged;
		/** @} */
	};

#if defined(VAS_USE_OOENTRY) || defined(DOXYGEN)
	/**
	 * @brief Manage and load the launcher class.
	 * 
	 * The ClassLoader is the utility that load and execute the main member function of the launcher class.
	 */
	class VAS_DECLSPEC ClassLoader
	{ /** @} */
	public:
		/**
		 * Load the launcher class. Use to initialize the static bool member to make sure it run before main function of
		 * C++ run.
		 * @tparam Launcher Launcher class variant
		 */
		template <class Launcher>
		static bool load()
		{
			gt5d_acfg = &Launcher::main;
			return true;
		}

		static int(*gt5d_acfg)(const std::vector<std::string>&);
	};
#endif // VAS_USE_OOENTRY
}

#ifdef VAS_USE_OOENTRY
int VAS_DECLSPEC SDL_main(int argc, char** argv); //Redefined SDL_main
#endif

#if defined(VAS_WINDOWS_MODE) || defined(DOXYGEN)
/**
 * Allocate console window on Windows subsystem, empty macro on other operating system.
 * 
 * Defined in: vasframework/base/Base.hpp
 */
#define VAS_ALLOCATE_CONSOLE \
static_cast<void>(AllocConsole());\
static_cast<void>(freopen("CONIN$", "r+t", stdin));\
static_cast<void>(freopen("CONIN$", "w+t", stdout));\
static_cast<void>(freopen("CONIN$", "w+t", stderr));\
vas::CommonTools::getInstance().hasConsole = true

/** @} */
#else
#define VAS_ALLOCATE_CONSOLE
#endif // VAS_WINDOWS_MODE