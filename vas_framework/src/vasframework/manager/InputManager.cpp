//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include <algorithm>
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

	bool InputManager::isKeysTriggered(std::initializer_list<sdl::Scancode> keys)
	{
		for (auto itr = keys.begin(); itr != keys.end(); itr++)
			if (!isKeyTriggered(*itr)) return false;

		return true;
	}

	void InputManager::__setMousePosition(sdl::Point value)
	{
		currentMousePosition = std::move(value);
	}

	void InputManager::__setRealMousePosition(sdl::Point value)
	{
		currentRealMousePosition = std::move(value);
	}

	sdl::Point InputManager::getMousePosition()
	{
		return currentMousePosition;
	}

	sdl::Point InputManager::getRealMousePosition()
	{
		return currentRealMousePosition;
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