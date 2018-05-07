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

	bool InputManager::isKeyTriggered(sdl::Scancode key)
	{
		return keyState[static_cast<SDL_Scancode>(key)] != 0;
	}

	void InputManager::setMousePosition(sdl::Point && value)
	{
		currentMousePosition = std::move(value);
	}

	sdl::Point InputManager::getMousePosition()
	{
		return currentMousePosition;
	}

	sdl::Point InputManager::getMousePositionRaw()
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