#pragma once
#include <exception>
#include <boost/signals2.hpp>
#include "../sdlcore/SDLCore.hpp"

namespace vas
{
	using MouseButtonIndex = uint8_t;
	using MouseWheelDirection = SDL_MouseWheelDirection;
	class InputManager
	{
	public:
		static InputManager& getInstance();

		void init(sdl::Event* ev);
		void tick();

		bool isKeyTriggered(sdl::Scancode key);
		
	public: //Setters
		void setMousePosition(sdl::Point&& value);
	public: //Getters
		sdl::Point getMousePosition();
		sdl::Point getMousePositionRaw();
		uint32_t getMouseState();

	public: // Public members
		boost::signals2::signal<void(sdl::Keycode)> keyPressed;
		boost::signals2::signal<void(sdl::Keycode)> keyReleased;

		boost::signals2::signal<void(MouseButtonIndex, int, int)> mouseButtonPressed;
		boost::signals2::signal<void(MouseButtonIndex, int, int)> mouseButtonReleased;
		boost::signals2::signal<void(int, int)> mouseMoved;
		boost::signals2::signal<void(MouseWheelDirection, int, int)> mouseWheelMoved;
	private:
		InputManager();
		~InputManager();
		sdl::Event* ev{ nullptr };
		const uint8_t* keyState{ nullptr };
		sdl::Point currentMousePosition;
	};
}