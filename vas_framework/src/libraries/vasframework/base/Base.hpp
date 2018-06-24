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

#ifdef VAS_USE_MULTITHREAD
#include <thread>
#include <mutex>
#endif

namespace vas
{
	class VAS_DECLSPEC Base
	{
	public:
		struct SignalsType
		{
			enum class EventProcessor : uint8_t { preEventLoop = 0, PostEventLoop = 1 };
		};

		static Base& getInstance();

		void initAndStartAll(const std::string& windowTitle, const sdl::Point& size, uint32_t flags, std::function<void()> initializer = nullptr);

		void init();
		void init(size_t fps);
		void startGameLoop();
		//clean and exit framework;
		void cleanAndQuit();

		const bool& Exec();
		bool& IgnoreCloseEventOnce();
		bool& DoubleSceneRendering();
		sdl::Window& Window();
		sdl::Renderer& Renderer();
		boost::signals2::signal<void(sdl::Event&)>& EventProcessorSignal(Base::SignalsType::EventProcessor type);
		const Counter& FrameIndex();
		size_t getLastFpsCount();
		size_t getFPS();
		size_t getRefreshRate();
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
		std::array<boost::signals2::signal<void(sdl::Event&)>, 2> eventProcessorSignals;
		sdl::Window mainWindow;
		sdl::Renderer mainRenderer;
		sdl::Event ev;

#ifndef VAS_USE_MULTITHREAD
		size_t fps{ 60 };
#else
		size_t fps{ 0 };
#endif // !VAS_USE_MULTITHREAD
		size_t lastFpsCount{ 0 };
		Counter fpsCounter;
		Counter frameIndex;
		std::chrono::milliseconds frameStayTime{ 0 };

		Clock gameLoopClock;
		Timer frameCounterUpdater;

#ifdef VAS_USE_MULTITHREAD
	private:
		std::thread drawThread;
		size_t tickSpeed{ 60 };
		std::mutex globalResourcesMutex;
	public:
		void setTickSpeed(size_t value);
		size_t getTickSpeed();

		std::mutex& getResourceMutex();
	private:
#endif // VAS_USE_MULTITHREAD
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
