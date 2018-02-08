#pragma once
#include <exception>
#include "../sdlcore/SDLCore.hpp"

namespace vas
{
	class InputManager
	{
	public:
		static InputManager& getInstance();

		void init(sdl::Event* ev);
		void tick();

		bool isKeyTriggeredEv(sdl::Scancode key);
		bool isKeyTriggeredEv(sdl::Keycode key);
		bool isKeyTriggered(sdl::Scancode key);
		//TODO: fully implement mouse input stuff
		bool isMouseButtonTriggered();

		sdl::Point getMousePosition();
		uint32_t getMouseState();
	private:
		InputManager();
		~InputManager();
		sdl::Event* ev{ nullptr };
		const uint8_t* keyState{ nullptr };
	};
}