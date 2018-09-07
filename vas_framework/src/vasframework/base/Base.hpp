#pragma once
#include <array>
#include <boost/signals2.hpp>
#include "../VASConfig.hpp"
#include "../util/TextTools.hpp"
#include "../sdlcore/SDLCore.hpp"
#include "../math/Clock.hpp"
#include "../math/Counter.hpp"
#include "../math/Timer.hpp"

#ifdef VAS_WINDOWS_MODE
#include <Windows.h>
#endif // VAS_WINDOWS_MODE

#ifndef VAS_SDL_ENTRY
#ifdef main
#undef main
#endif // main
#endif // !VAS_SDL_ENTRY

namespace vas
{
	/*! \addtogroup vas_framework
		@{
	*/
	/*! \brief The basic class of the framework.

		 | Header | Namespace |
		 | : --- : | : --- : |
		 | vasframework/base/Base.hpp | vas |

		 Base is the singletone class that drived the skeleton of the framework. It controll the main event loop, signaling and
		 also handle the main game loop and thread.
	*/
	class VAS_DECLSPEC Base
	{
	public:
		static Base& getInstance();

		void initAndStartAll(const std::string& windowTitle, const sdl::Point& size, uint32_t flags, std::function<void()> initializer = nullptr);

		void init();
		void init(size_t fps);
		void startGameLoop();
		//clean and exit framework;
		void cleanAndQuit();

		const bool& Exec();

		void setIgnoreCloseEventOnce(bool value);
		bool& getIgnoreCloseEventOnce();

		void setDoubleSceneRendering(bool value);
		bool& getDoubleSceneRendering();

		void setWindow(sdl::Window value);
		sdl::Window& getWindow();

		void setRenderer(sdl::Renderer value);
		sdl::Renderer& getRenderer();

		size_t getCurFrameIndex();
		size_t getLastFpsCount();
		void setFPS(size_t value);
		size_t getFPS();
		sdl::Event& getEvent();
	private:
		Base();
		~Base();

		void tick();
		void draw();
		void delay();
		void frameCounter();

		bool exec{ true };
		bool ignoreCloseEventOnce{ false };
		bool doubleSceneRendering{ false };
		sdl::Window window;
		sdl::Renderer renderer;
		sdl::Event ev;

		size_t fps{ 60 };
		size_t lastFpsCount{ 0 };
		Counter fpsCounter;
		Counter frameIndex;
		std::chrono::milliseconds frameStayTime{ 0 };

		Clock gameLoopClock;
		Timer frameCounterUpdater;

	public: //signals
		boost::signals2::signal<void(sdl::Event&)> EventBeginProcessed;
		boost::signals2::signal<void(sdl::Event&)> EventCompleateProcessed;
		boost::signals2::signal<void(size_t)> FPSChanged;
	};
}

#ifdef VAS_USE_UNIENTRY
#ifndef VAS_WINDOWS_MODE
#define VAS_CLASSLOADER_LOAD(launcher) \
int main(int argc, char** argv)\
{\
	std::vector<std::string> args;\
	args.reserve(argc);\
	for (int itr = 0; itr < argc; itr++)\
		args.push_back(argv[itr]);\
	return launcher::main(std::move(args));\
}

#define VAS_ALLOCATE_CONSOLE
#else

#ifdef _CONSOLE
#define VAS_CLASSLOADER_LOAD(launcher) \
int wmain(int argc, wchar_t** argv)\
{\
	std::vector<std::string> args;\
	args.reserve(argc);\
	for (int itr = 0; itr < argc; itr++)\
		args.push_back(vas::TextTools::wstos(argv[itr]));\
	return launcher::main(std::move(args));\
}
#else
#define VAS_CLASSLOADER_LOAD(launcher)\
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR cmdLine, int cmdShow)\
{\
	std::vector<std::string> args;\
	{\
		int argc = 0;\
		LPWSTR* argv = CommandLineToArgvW(cmdLine, &argc);\
		args.reserve(argc);\
		for (int itr = 0; itr < argc; itr++)\
			args.push_back(vas::TextTools::wstos(argv[itr]));\
	}\
	return launcher::main(std::move(args));\
}
#endif //_CONSOLE

#define VAS_ALLOCATE_CONSOLE \
AllocConsole();\
freopen("CONIN$", "r+t", stdin);\
freopen("CONIN$", "w+t", stdout);\
freopen("CONIN$", "w+t", stderr)

#endif // !VAS_WINDOWS_MODE
#endif // VAS_USE_UNIENTRY

/*! @} */ // addtogroup vas_framework