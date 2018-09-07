#pragma once
#include <exception>
#include <boost/signals2.hpp>
#include "../sdlcore/SDLCore.hpp"

namespace vas
{
	class VAS_DECLSPEC InputManager
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
		boost::signals2::signal<void(sdl::Keycode)> KeyPressed;
		boost::signals2::signal<void(sdl::Keycode)> KeyReleased;

		boost::signals2::signal<void(sdl::MouseButtonIndex, sdl::Point)> MouseButtonPressed;
		boost::signals2::signal<void(sdl::MouseButtonIndex, sdl::Point)> MouseButtonReleased;
		boost::signals2::signal<void(int, int)> MouseMoved;
		boost::signals2::signal<void(sdl::MouseWheelDirection, sdl::Point)> MouseWheelMoved;
	private:
		InputManager();
		~InputManager();
		sdl::Event* ev{ nullptr };
		const uint8_t* keyState{ nullptr };
		sdl::Point currentMousePosition;
	};
}