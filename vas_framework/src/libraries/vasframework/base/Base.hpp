#pragma once
#include <boost/signals2.hpp>
#include "../VASConfig.hpp"
#include "../sdlcore/SDLCore.hpp"
#include "../container/Switch.hpp"

#ifdef main
#undef main
#endif // main

namespace vas
{
	class VAS_DECLSPEC Base
	{
	public:
		static Base& getInstance();

		void init();
		void startGameLoop();
		void clean();

		void setWindow(const sdl::Window& instance);
		void setWindow(sdl::Window&& instance);
		
		void setRenderer(const sdl::Renderer& instance);
		void setRenderer(sdl::Renderer&& instance);
	private:
		Base();
		~Base();

		void tick();
		void draw();

		Switch exec{ on };
		Switch doubleSceneRendering{ off };
		sdl::Window mainWindow;
		sdl::Renderer mainRenderer;
	};
}