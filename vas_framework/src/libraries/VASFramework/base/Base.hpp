#pragma once
#include <Windows.h>
#include <string>
#include <thread>
#include "../util/SDLFunctionBridge.hpp"

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#ifdef main
#undef main
#endif // main

#ifndef BASE_INIT_SETTINGS
#define BASE_INIT_SETTINGS

#define SETTINGS_INIT_IMAGE
#define SETTINGS_INIT_AUDIO
#define SETTINGS_INIT_TTF

#define SETTINGS_SDL_INIT_FLAGS SDL_INIT_EVERYTHING
#define SETTINGS_IMAGE_INIT_FLAGS IMG_InitFlags::IMG_INIT_JPG | IMG_InitFlags::IMG_INIT_PNG
#define SETTINGS_AUDIO_FREQUENCY 44100
#define SETTINGS_AUDIO_INIT_FLAGS MIX_InitFlags::MIX_INIT_MP3 | MIX_InitFlags::MIX_INIT_OGG
#define SETTINGS_AUDIO_FORMAT MIX_DEFAULT_FORMAT
#define SETTINGS_AUDIO_CHANNEL_COUNT 2
#define SETTINGS_AUDIO_CHUNK_SIZE 10240

#define SETTINGS_DISPLAY_FPS_ON_CONSOLE_TITLE
#define SETTINGS_USE_FADING_MANAGER
//#define SETTINGS_SEPERATE_TICK_AND_DRAW
#endif // !BASE_INIT_SETTINGS

namespace vas
{
	class Base
	{
	public:
		static inline std::wstring frameworkVersion() { return L"0.11 Beta"; }
		static Base& getInstance();
#ifdef SETTINGS_SEPERATE_TICK_AND_DRAW
		static std::exception_ptr __threadExep;
#endif // SETTINGS_SEPERATE_TICK_AND_DRAW

		//Ignore SDL_EventType::SDL_QUIT
		inline void ignoreQuitEvent() { Base::getInstance().__ignoreQuitEvent = true; }
		void init();

		void setMainWindow(const std::shared_ptr<SDL_Window>& instance);
		void setMainWindow(std::shared_ptr<SDL_Window>&& instance);

		void setMainRenderer(const std::shared_ptr<SDL_Renderer>& instance);
		void setMainRenderer(std::shared_ptr<SDL_Renderer>&& instance);

		void setRenderLogicSize(const SDL_Point& size);

		void setFPS(uint32_t fps);

		void startGameLoop();
		void exitFramework();

		void postEvent(SDL_EventType eventType);

		std::wstring getTitle();
		uint32_t getFPS();
		std::shared_ptr<SDL_Renderer> getRenderer();

		const SDL_Point& getRenderLogicSize();

#ifdef SETTINGS_SEPERATE_TICK_AND_DRAW
		void setDrawFrequency(uint32_t fps);
		uint32_t getDrawFrequency();
#endif // SETTINGS_SEPERATE_TICK_AND_DRAW

		bool isRunning = true;
		bool __ignoreQuitEvent = false;
		bool allowDoubleSceneDrawing = false;

		void resizeWindow(int w, int h, SDL_Window* instance = nullptr);
	private:
		Base();
		~Base();

		void tick();
		void draw();

		std::wstring title = L"Untitled";
		SDL_Point renderLogicSize = { 0 };
		uint32_t fps = 60;
		uint32_t tickFrequency = 1000 / fps;
		uint32_t currentFPS = 0;
		SDL_Event mainEventBus;
		std::shared_ptr<SDL_Window> mainWindow = nullptr;
		std::shared_ptr<SDL_Renderer> mainRenderer = nullptr;
#ifdef SETTINGS_SEPERATE_TICK_AND_DRAW
		uint32_t drawFPS = 120;
		uint32_t drawFrequency = 1000 / drawFPS;
		uint32_t currentDrawFPS = 0;
		std::shared_ptr<std::thread> renderingThread = nullptr;
#endif // SETTINGS_SEPERATE_TICK_AND_DRAW
	};
	inline Base& BaseAPI() { return Base::getInstance(); };
}