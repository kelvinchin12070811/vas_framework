#include "Events.hpp"
#include "boolean_cast.hpp"

namespace sdl
{
	const uint32_t EventType::firstevent = SDL_FIRSTEVENT;
	const uint32_t EventType::quit = SDL_QUIT;
	const uint32_t EventType::app_terminating = SDL_APP_TERMINATING;
	const uint32_t EventType::app_lowmemory = SDL_APP_LOWMEMORY;
	const uint32_t EventType::app_willenterbackground = SDL_APP_WILLENTERBACKGROUND;
	const uint32_t EventType::app_didenterbackground = SDL_APP_DIDENTERBACKGROUND;
	const uint32_t EventType::app_willenterforeground = SDL_APP_WILLENTERFOREGROUND;
	const uint32_t EventType::app_didenterforeground = SDL_APP_DIDENTERFOREGROUND;
	const uint32_t EventType::windowevent = SDL_WINDOWEVENT;
	const uint32_t EventType::syswmevent = SDL_SYSWMEVENT;
	const uint32_t EventType::keydown = SDL_KEYDOWN;
	const uint32_t EventType::keyup = SDL_KEYUP;
	const uint32_t EventType::textediting = SDL_TEXTEDITING;
	const uint32_t EventType::textinput = SDL_TEXTINPUT;
	const uint32_t EventType::keymapchanged = SDL_KEYMAPCHANGED;
	const uint32_t EventType::mousemotion = SDL_MOUSEMOTION;
	const uint32_t EventType::mousebuttondown = SDL_MOUSEBUTTONDOWN;
	const uint32_t EventType::mousebuttonup = SDL_MOUSEBUTTONUP;
	const uint32_t EventType::mousewheel = SDL_MOUSEWHEEL;
	const uint32_t EventType::joyaxismotion = SDL_JOYAXISMOTION;
	const uint32_t EventType::joyballmotion = SDL_JOYBALLMOTION;
	const uint32_t EventType::joyhatmotion = SDL_JOYHATMOTION;
	const uint32_t EventType::joybuttondown = SDL_JOYBUTTONDOWN;
	const uint32_t EventType::joybuttonup = SDL_JOYBUTTONUP;
	const uint32_t EventType::joydeviceadded = SDL_JOYDEVICEADDED;
	const uint32_t EventType::joydeviceremoved = SDL_JOYDEVICEREMOVED;
	const uint32_t EventType::controlleraxismotion = SDL_CONTROLLERAXISMOTION;
	const uint32_t EventType::controllerbuttondown = SDL_CONTROLLERBUTTONDOWN;
	const uint32_t EventType::controllerbuttonup = SDL_CONTROLLERBUTTONUP;
	const uint32_t EventType::controllerdeviceadded = SDL_CONTROLLERDEVICEADDED;
	const uint32_t EventType::controllerdeviceremoved = SDL_CONTROLLERDEVICEREMOVED;
	const uint32_t EventType::controllerdeviceremapped = SDL_CONTROLLERDEVICEREMAPPED;
	const uint32_t EventType::fingerdown = SDL_FINGERDOWN;
	const uint32_t EventType::fingerup = SDL_FINGERUP;
	const uint32_t EventType::fingermotion = SDL_FINGERMOTION;
	const uint32_t EventType::dollargesture = SDL_DOLLARGESTURE;
	const uint32_t EventType::dollarrecord = SDL_DOLLARRECORD;
	const uint32_t EventType::multigesture = SDL_MULTIGESTURE;
	const uint32_t EventType::clipboardupdate = SDL_CLIPBOARDUPDATE;
	const uint32_t EventType::dropfile = SDL_DROPFILE;
	const uint32_t EventType::droptext = SDL_DROPTEXT;
	const uint32_t EventType::dropbegin = SDL_DROPBEGIN;
	const uint32_t EventType::dropcomplete = SDL_DROPCOMPLETE;
	const uint32_t EventType::audiodeviceadded = SDL_AUDIODEVICEADDED;
	const uint32_t EventType::audiodeviceremoved = SDL_AUDIODEVICEREMOVED;
	const uint32_t EventType::render_targets_reset = SDL_RENDER_TARGETS_RESET;
	const uint32_t EventType::render_device_reset = SDL_RENDER_DEVICE_RESET;
	const uint32_t EventType::userevent = SDL_USEREVENT;
	const uint32_t EventType::lastevent = SDL_LASTEVENT;

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

	bool Event::wait(EventType::type type)
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