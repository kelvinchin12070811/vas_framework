#pragma once
#include <SDL.h>

namespace vas
{
	class InputManager
	{
	public:
		static InputManager& getInstance();
		//Key triggered by event
		bool keyTriggered(SDL_Scancode code);
		//Key triggered by tick
		bool keyTriggeredLive(SDL_Scancode code);
		void setEventBus(SDL_Event* eventBus);

		void tick();
	private:
		InputManager();
		~InputManager();
		SDL_Event* mainEventBus = nullptr;
		const uint8_t* keyState = nullptr;
	};
	//Return instance of input manager
	inline InputManager& InputManagerAPI() { return InputManager::getInstance(); };
}