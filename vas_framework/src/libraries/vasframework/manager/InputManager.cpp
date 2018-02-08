#include "InputManager.hpp"

namespace vas
{
	InputManager & InputManager::getInstance()
	{
		static InputManager instance;
		return instance;
	}

	void InputManager::init(sdl::Event * ev)
	{
		this->ev = ev;
	}

	void InputManager::tick()
	{
		keyState = sdl::getKeyboardState();
	}

	bool InputManager::isKeyTriggeredEv(sdl::Scancode key)
	{
		return ev->key().keysym.scancode == key;
	}

	bool InputManager::isKeyTriggeredEv(sdl::Keycode key)
	{
		return ev->key().keysym.sym == key;
	}

	bool InputManager::isKeyTriggered(sdl::Scancode key)
	{
		return keyState[static_cast<SDL_Scancode>(key)] != 0;
	}

	bool InputManager::isMouseButtonTriggered()
	{
		return false;
	}

	sdl::Point InputManager::getMousePosition()
	{
		sdl::Point mousePos;
		SDL_GetMouseState(&mousePos.x, &mousePos.y);
		return mousePos;
	}

	uint32_t InputManager::getMouseState()
	{
		return SDL_GetMouseState(nullptr, nullptr);
	}
	
	InputManager::InputManager()
	{
	}

	InputManager::~InputManager()
	{
	}
}