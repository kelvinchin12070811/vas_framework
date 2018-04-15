#pragma once
#include <array>
#include <boost/signals2.hpp>
#include "../VASConfig.hpp"
#include "../sdlcore/SDLCore.hpp"
#include "../math/Clock.hpp"
#include "../math/Counter.hpp"
#include "../math/Timer.hpp"

#ifdef main
#undef main
#endif // main

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
		size_t getRefreshRate();
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

		size_t fps{ 60 };
		size_t lastFpsCount{ 0 };
		Counter fpsCounter;
		Counter frameIndex;
		std::chrono::milliseconds frameStayTime{ 0 };

		Clock gameLoopClock;
		Timer frameCounterUpdater;
	};
}