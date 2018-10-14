#include "Events.hpp"
#include "boolean_cast.hpp"

namespace vas::sdl
{
	const SDL_Event & Event::getInstance() const
	{
		return instance;
	}

	SDL_Event& Event::getInstance()
	{
		return instance;
	}

	EventType::type sdl::Event::type()
	{
		return instance.type;
	}

	sdl::CommonEvent Event::common()
	{
		return sdl::CommonEvent();
	}

	sdl::WindowEvent Event::window()
	{
		return instance.window;
	}

	sdl::KeyboardEvent Event::key()
	{
		return instance.key;
	}

	sdl::TextEditingEvent Event::edit()
	{
		return instance.edit;
	}

	sdl::TextInputEvent Event::text()
	{
		return instance.text;
	}

	sdl::MouseMotionEvent Event::motion()
	{
		return instance.motion;
	}

	sdl::MouseButtonEvent Event::button()
	{
		return instance.button;
	}

	sdl::MouseWheelEvent Event::wheel()
	{
		return instance.wheel;
	}

	sdl::JoyAxisEvent Event::jaxis()
	{
		return instance.jaxis;
	}

	sdl::JoyBallEvent Event::jball()
	{
		return instance.jball;
	}

	sdl::JoyHatEvent Event::jhat()
	{
		return instance.jhat;
	}

	sdl::JoyButtonEvent Event::jbutton()
	{
		return instance.jbutton;
	}

	sdl::JoyDeviceEvent Event::jdevice()
	{
		return instance.jdevice;
	}

	sdl::ControllerAxisEvent Event::caxis()
	{
		return instance.caxis;
	}

	sdl::ControllerButtonEvent Event::cbutton()
	{
		return instance.cbutton;
	}

	sdl::ControllerDeviceEvent Event::cdevice()
	{
		return instance.cdevice;
	}

	sdl::AudioDeviceEvent Event::adevice()
	{
		return instance.adevice;
	}

	sdl::QuitEvent Event::quit()
	{
		return instance.quit;
	}

	sdl::UserEvent Event::user()
	{
		return instance.user;
	}

	sdl::SysWMEvent Event::syswm()
	{
		return instance.syswm;
	}

	sdl::TouchFingerEvent Event::tfinger()
	{
		return instance.tfinger;
	}

	sdl::MultiGestureEvent Event::mgesture()
	{
		return instance.mgesture;
	}

	sdl::DollarGestureEvent Event::dgesture()
	{
		return instance.dgesture;
	}

	sdl::DropEvent Event::drop()
	{
		return instance.drop;
	}

	bool Event::operator==(const EventType::type & type) const
	{
		return this->instance.type == type;
	}

	bool Event::operator!=(const EventType::type & type) const
	{
		return this->instance.type != type;
	}

	Event::operator const EventType::type()
	{
		return this->instance.type;
	}

	bool Event::pollEvent()
	{
		return SDL_PollEvent(&instance) == 1;
	}

	bool Event::is(EventType::type evType)
	{
		return instance.type == evType;
	}

	bool Event::hasEvent(EventType::type type)
	{
		return boolean_cast(SDL_HasEvent(type));
	}

	bool Event::hasEvents(EventType::type minType, EventType::type maxType)
	{
		return boolean_cast(SDL_HasEvents(minType, maxType));
	}

	bool Event::wait()
	{
		return SDL_WaitEvent(&instance) == 1;
	}

	bool Event::waitTimeout(int timeout)
	{
		return SDL_WaitEventTimeout(&instance, timeout) == 1;
	}

	void Event::flushEvent(EventType::type type)
	{
		SDL_FlushEvent(type);
	}

	void Event::flushEvents(EventType::type minType, EventType::type maxType)
	{
		SDL_FlushEvents(minType, maxType);
	}

	int Event::pushEvent(EventType::type type)
	{
		SDL_Event tempEvent;
		tempEvent.type = type;
		return SDL_PushEvent(&tempEvent);
	}

	Event::operator SDL_Event&()
	{
		return getInstance();
	}

	Event::operator const SDL_Event&() const
	{
		return getInstance();
	}
}