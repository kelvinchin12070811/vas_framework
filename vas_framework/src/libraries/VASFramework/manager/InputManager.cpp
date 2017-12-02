#include "InputManager.hpp"

namespace vas
{
	InputManager & InputManager::getInstance()
	{
		static InputManager instance;
		return instance;
	}

	bool InputManager::keyTriggered(SDL_Scancode code)
	{
		return mainEventBus !=nullptr && mainEventBus->key.keysym.scancode == code;
	}

	bool InputManager::keyTriggeredLive(SDL_Scancode code)
	{
		return keyState[code] != 0 ? true : false;
	}

	void InputManager::setEventBus(SDL_Event * eventBus)
	{
		mainEventBus = eventBus;
	}

	void InputManager::tick()
	{
		keyState = SDL_GetKeyboardState(nullptr);
	}

	InputManager::InputManager()
	{
	}


	InputManager::~InputManager()
	{
	}
}