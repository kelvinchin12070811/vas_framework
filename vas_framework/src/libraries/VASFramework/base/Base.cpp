#include "Base.hpp"
#include "EventHandler.hpp"
#include "../util/TextTools.hpp"
#include "../manager/SceneManager.hpp"
#include "../math/Clock.hpp"
#include "../manager/InputManager.hpp"
#include "../manager/AudioManager.hpp"

#ifdef SETTINGS_USE_FADING_MANAGER
#include "../manager/FadingManager.hpp"  
#endif // SETTINGS_USE_FADING_MANAGER

namespace vas
{
#ifdef SETTINGS_SEPERATE_TICK_AND_DRAW
	std::exception_ptr Base::__threadExep = nullptr;
#endif // SETTINGS_SEPERATE_TICK_AND_DRAW

	Base & Base::getInstance()
	{
		static Base instance;
		return instance;
	}

	void Base::init()
	{
		if (SDL_Init(SETTINGS_SDL_INIT_FLAGS) < 0) throw std::runtime_error(SDL_GetError());
#ifdef SETTINGS_INIT_IMAGE
		if (IMG_Init(SETTINGS_IMAGE_INIT_FLAGS) == 0) throw std::runtime_error(SDL_GetError());
#endif // SETTINGS_INIT_IMAGE
#ifdef SETTINGS_INIT_AUDIO
		if (Mix_Init(SETTINGS_AUDIO_INIT_FLAGS) == 0) throw std::runtime_error(SDL_GetError());
		if (Mix_OpenAudio(SETTINGS_AUDIO_FREQUENCY, SETTINGS_AUDIO_FORMAT, SETTINGS_AUDIO_CHANNEL_COUNT, SETTINGS_AUDIO_CHUNK_SIZE) < 0) throw std::runtime_error(SDL_GetError());
#endif // SETTINGS_INIT_AUDIO
#ifdef SETTINGS_INIT_TTF
		if (TTF_Init() < 0) throw std::runtime_error(SDL_GetError());
#endif // SETTINGS_INIT_TTF
	}

	void Base::setMainWindow(const std::shared_ptr<SDL_Window>& instance)
	{
		if (mainWindow == instance) return;
		mainWindow = instance;
		title = TextTools::stows(SDL_GetWindowTitle(mainWindow.get()));
	}

	void Base::setMainWindow(std::shared_ptr<SDL_Window>&& instance)
	{
		if (mainWindow == instance) return;
		mainWindow = std::move(instance);
		title = TextTools::stows(SDL_GetWindowTitle(mainWindow.get()));
	}

	void Base::setMainRenderer(const std::shared_ptr<SDL_Renderer>& instance)
	{
		if (mainRenderer == instance) return;
		mainRenderer = instance;
	}

	void Base::setMainRenderer(std::shared_ptr<SDL_Renderer>&& instance)
	{
		if (mainRenderer == instance) return;
		mainRenderer = std::move(instance);
	}

	void Base::setRenderLogicSize(const SDL_Point& size)
	{
		renderLogicSize = size;
		SDL_RenderSetLogicalSize(mainRenderer.get(), renderLogicSize.x, renderLogicSize.y);
	}

	void Base::setFPS(uint32_t fps)
	{
		this->fps = fps;
		tickFrequency = 1000 / this->fps;
	}

	void Base::startGameLoop()
	{
		Clock clock;
		Clock clock2;
		uint32_t currentFrame = 0;
		InputManager::getInstance().setEventBus(&mainEventBus);

#ifdef SETTINGS_SEPERATE_TICK_AND_DRAW
		renderingThread = std::make_shared<std::thread>(std::bind(&Base::draw, this));
#endif // SETTINGS_SEPERATE_TICK_AND_DRAW

		while (isRunning)
		{
#ifdef SETTINGS_SEPERATE_TICK_AND_DRAW
			if (Base::__threadExep != nullptr) std::rethrow_exception(Base::__threadExep);
#endif // SETTINGS_SEPERATE_TICK_AND_DRAW

			clock.reset();
			currentFrame++;
			while (SDL_PollEvent(&mainEventBus) != 0)
			{
				if (__ignoreQuitEvent) __ignoreQuitEvent = false;
				// scene event handaller
				if (!SceneManager::getInstance().isEmpty())
				{
					EventHandler* eventHandler = dynamic_cast<EventHandler*>(SceneManager::getInstance().get().get());
					if (eventHandler != nullptr) eventHandler->eventSlot(mainEventBus);
				}
				//main event loop
				if (mainEventBus.type == SDL_EventType::SDL_QUIT && !__ignoreQuitEvent)
				{
					isRunning = false;
					return;
				}
			}

			//tick and draw
#ifdef SETTINGS_INIT_AUDIO
			AudioManager::getInstance().tick();
#endif // SETTINGS_INIT_AUDIO
			InputManager::getInstance().tick();
			tick();
#ifndef SETTINGS_SEPERATE_TICK_AND_DRAW
			SDL_RenderClear(mainRenderer.get());
			draw();
			SDL_RenderPresent(mainRenderer.get());
#endif // !SETTINGS_SEPERATE_TICK_AND_DRAW

			uint32_t ticks = clock.getTicks();
			if (ticks < tickFrequency)
				SDL_Delay(tickFrequency - ticks);

#ifdef SETTINGS_DISPLAY_FPS_ON_CONSOLE_TITLE
			if (clock2.getTicks() >= 1000)
			{
				currentFPS = currentFrame;
#ifdef SETTINGS_SEPERATE_TICK_AND_DRAW
				SetConsoleTitle((L"FPS: " + std::to_wstring(currentFrame) + L" / " + std::to_wstring(currentDrawFPS)).c_str());
#else
				SetConsoleTitle((L"FPS: " + std::to_wstring(currentFrame)).c_str());
#endif // SETTINGS_SEPERATE_TICK_AND_DRAW
				clock2.reset();
				currentFrame = 0;
			}
#endif // SETTINGS_DISPLAY_FPS_ON_CONSOLE_TITLE
		}
	}

	void Base::exitFramework()
	{
		if (isRunning) isRunning = false;
		if (!SceneManager::getInstance().isEmpty()) SceneManager::getInstance().clearAll();
#ifdef SETTINGS_SEPERATE_TICK_AND_DRAW
		if (renderingThread && renderingThread->joinable())
			renderingThread->join();
#endif // SETTINGS_SEPERATE_TICK_AND_DRAW

		mainWindow = nullptr;
		mainRenderer = nullptr;

#ifdef SETTINGS_INIT_IMAGE
		IMG_Quit();
#endif // SETTINGS_INIT_IMAGE

#ifdef SETTINGS_INIT_TTF
		TTF_Quit();
#endif // SETTINGS_INIT_TTF
		SDL_Quit();
	}

	void Base::postEvent(SDL_EventType eventType)
	{
		SDL_Event temp;
		temp.type = eventType;
		SDL_PushEvent(&temp);
	}

	std::wstring Base::getTitle()
	{
		return title;
	}

	uint32_t Base::getFPS()
	{
		return fps;
	}

	std::shared_ptr<SDL_Renderer> Base::getRenderer()
	{
		return mainRenderer;
	}

	const SDL_Point & Base::getRenderLogicSize()
	{
		return renderLogicSize;
	}

#ifdef SETTINGS_SEPERATE_TICK_AND_DRAW
	void Base::setDrawFrequency(uint32_t fps)
	{
		this->drawFPS = fps;
		this->drawFrequency = 1000 / this->drawFPS;
	}

	uint32_t Base::getDrawFrequency()
	{
		return drawFPS;
	}
#endif // SETTINGS_SEPERATE_TICK_AND_DRAW

	void Base::resizeWindow(int w, int h, SDL_Window * instance)
	{
		SDL_Window* windowToResize = instance == nullptr ? mainWindow.get() : instance;
		int prevW = 0;
		int prevH = 0;
		int prevX = 0;
		int prevY = 0;
		SDL_GetWindowSize(windowToResize, &prevW, &prevH);
		SDL_GetWindowPosition(windowToResize, &prevX, &prevY);

		int newW = w;
		int newH = h;
		int newX = 0;
		int newY = 0;
		if (newW > prevW)
		{
			newX = prevX - ((newW / 2) - (prevW / 2));
		}
		else if (newW < prevW)
		{
			newX = prevX + ((prevW / 2) - (newW / 2));
		}

		if (newH > prevH)
		{
			newY = prevY - ((newH / 2) - (prevH / 2));
		}
		else if (newH < prevH)
		{
			newY = prevY + ((prevH / 2) - (newH / 2));
		}
		if (newX < 0)
			newX = 0;
		if (newY < 0)
			newY = 0;

		SDL_SetWindowPosition(windowToResize, newX, newY);
		SDL_SetWindowSize(windowToResize, newW, newH);
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
			SceneManager::getInstance().get()->tick();
		}

#ifdef SETTINGS_USE_FADING_MANAGER
		if (FadingManager::getInstance().isFading())
			FadingManager::getInstance().tick();
#endif // SETTINGS_USE_FADING_MANAGER

	}

#ifdef SETTINGS_SEPERATE_TICK_AND_DRAW
	void Base::draw()
	{
		Clock threadClock;
		Clock threadClock2;
		uint32_t frameCount = 0;
		while (this->isRunning)
		{
			threadClock2.reset();
			try
			{
				SDL_RenderClear(this->mainRenderer.get());
				if (!SceneManager::getInstance().isEmpty())
				{
					if (SceneManager::getInstance().isDoubleSceneDrawingReady() && allowDoubleSceneDrawing)
						SceneManager::getInstance().getPrev()->draw();
					SceneManager::getInstance().get()->draw();
				}

				SDL_RenderPresent(this->mainRenderer.get());
			}
			catch (...)
			{
				std::this_thread::yield();
				Base::__threadExep = std::current_exception();
			}
			uint32_t deltaTime = threadClock2.getTicks();
			if (deltaTime < this->drawFrequency)
			{
				int sleepTime = this->drawFrequency - deltaTime;
				std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime <= 0 ? 1 : sleepTime));
			}

			frameCount++;
			if (threadClock.getTicks() >= 1000)
			{
				this->currentDrawFPS = frameCount;
				frameCount = 0;
				threadClock.reset();
			}
		}
	}
#else
	void Base::draw()
	{

		if (!SceneManager::getInstance().isEmpty())
		{
			if (SceneManager::getInstance().isDoubleSceneDrawingReady() && allowDoubleSceneDrawing)
				SceneManager::getInstance().getPrev()->draw();
			SceneManager::getInstance().get()->draw();
		}

#ifdef SETTINGS_USE_FADING_MANAGER
		FadingManager::getInstance().draw();
#endif // SETTINGS_USE_FADING_MANAGER
	}
#endif // SETTINGS_SEPERATE_TICK_AND_DRAW
}