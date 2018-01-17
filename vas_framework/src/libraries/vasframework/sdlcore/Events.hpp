#pragma once
#include <SDL.h>

namespace sdl
{
	struct EventType
	{
		using type = uint32_t;
		static const uint32_t firstevent;     /**< Unused (do not remove) */
		/* Application events */
		static const uint32_t quit; /**< User-requested quit */

		/* These application events have special meaning on iOS, see README-ios.md for details */
		static const uint32_t app_terminating;        /**< The application is being terminated by the OS
								Called on iOS in applicationWillTerminate()
								Called on Android in onDestroy()
								*/
		static const uint32_t app_lowmemory;         /**< The application is low on memory, free memory if possible.
								Called on iOS in applicationDidReceiveMemoryWarning()
								Called on Android in onLowMemory()
								*/
		static const uint32_t app_willenterbackground; /**< The application is about to enter the background
								 Called on iOS in applicationWillResignActive()
								 Called on Android in onPause()
								 */
		static const uint32_t app_didenterbackground; /**< The application did enter the background and may not get CPU for some time
								Called on iOS in applicationDidEnterBackground()
								Called on Android in onPause()
								*/
		static const uint32_t app_willenterforeground; /**< The application is about to enter the foreground
								 Called on iOS in applicationWillEnterForeground()
								 Called on Android in onResume()
								 */
		static const uint32_t app_didenterforeground; /**< The application is now interactive
								Called on iOS in applicationDidBecomeActive()
								Called on Android in onResume()
								*/

		/* Window events */
		static const uint32_t windowevent; /**< Window state change */
		static const uint32_t syswmevent;             /**< System specific event */

		/* Keyboard events */
		static const uint32_t keydown; /**< Key pressed */
		static const uint32_t keyup;                  /**< Key released */
		static const uint32_t textediting;            /**< Keyboard text editing (composition) */
		static const uint32_t textinput;              /**< Keyboard text input */
		static const uint32_t keymapchanged;          /**< Keymap changed due to a system event such as an
								input language or keyboard layout change.
								*/

		/* Mouse events */
		static const uint32_t mousemotion; /**< Mouse moved */
		static const uint32_t mousebuttondown;        /**< Mouse button pressed */
		static const uint32_t mousebuttonup;          /**< Mouse button released */
		static const uint32_t mousewheel;             /**< Mouse wheel motion */

		/* Joystick events */
		static const uint32_t joyaxismotion; /**< Joystick axis motion */
		static const uint32_t joyballmotion;          /**< Joystick trackball motion */
		static const uint32_t joyhatmotion;           /**< Joystick hat position change */
		static const uint32_t joybuttondown;          /**< Joystick button pressed */
		static const uint32_t joybuttonup;            /**< Joystick button released */
		static const uint32_t joydeviceadded;         /**< A new joystick has been inserted into the system */
		static const uint32_t joydeviceremoved;       /**< An opened joystick has been removed */

		/* Game controller events */
		static const uint32_t controlleraxismotion; /**< Game controller axis motion */
		static const uint32_t controllerbuttondown;          /**< Game controller button pressed */
		static const uint32_t controllerbuttonup;            /**< Game controller button released */
		static const uint32_t controllerdeviceadded;         /**< A new Game controller has been inserted into the system */
		static const uint32_t controllerdeviceremoved;       /**< An opened Game controller has been removed */
		static const uint32_t controllerdeviceremapped;      /**< The controller mapping was updated */

		/* Touch events */
		static const uint32_t fingerdown;
		static const uint32_t fingerup;
		static const uint32_t fingermotion;

		/* Gesture events */
		static const uint32_t dollargesture;
		static const uint32_t dollarrecord;
		static const uint32_t multigesture;

		/* Clipboard events */
		static const uint32_t clipboardupdate; /**< The clipboard changed */

		/* Drag and drop events */
		static const uint32_t dropfile; /**< The system requests a file open */
		static const uint32_t droptext;                 /**< text/plain drag-and-drop event */
		static const uint32_t dropbegin;                /**< A new set of drops is beginning (NULL filename) */
		static const uint32_t dropcomplete;             /**< Current set of drops is now complete (NULL filename) */

		/* Audio hotplug events */
		static const uint32_t audiodeviceadded; /**< A new audio device is available */
		static const uint32_t audiodeviceremoved;        /**< An audio device has been removed. */

		/* Render events */
		static const uint32_t render_targets_reset; /**< The render targets have been reset and their contents need to be updated */
		static const uint32_t render_device_reset; /**< The device has been reset and all textures need to be recreated */

		/** Events ::SDL_USEREVENT through ::SDL_LASTEVENT are for your use,
		*  and should be allocated with SDL_RegisterEvents()
		*/
		static const uint32_t userevent;

		/**
		*  This last event is only for bounding internal arrays
		*/
		static const uint32_t lastevent;
	};

	using CommonEvent = SDL_CommonEvent;
	using WindowEvent = SDL_WindowEvent;
	using KeyboardEvent = SDL_KeyboardEvent;
	using TextEditingEvent = SDL_TextEditingEvent;
	using TextInputEvent = SDL_TextInputEvent;
	using MouseMotionEvent = SDL_MouseMotionEvent;
	using MouseButtonEvent = SDL_MouseButtonEvent;
	using MouseWheelEvent = SDL_MouseWheelEvent;
	using JoyAxisEvent = SDL_JoyAxisEvent;
	using JoyBallEvent = SDL_JoyBallEvent;
	using JoyHatEvent = SDL_JoyHatEvent;
	using JoyButtonEvent = SDL_JoyButtonEvent;
	using JoyDeviceEvent = SDL_JoyDeviceEvent;
	using ControllerAxisEvent = SDL_ControllerAxisEvent;
	using ControllerButtonEvent = SDL_ControllerButtonEvent;
	using ControllerDeviceEvent = SDL_ControllerDeviceEvent;
	using AudioDeviceEvent = SDL_AudioDeviceEvent;
	using TouchFingerEvent = SDL_TouchFingerEvent;
	using MultiGestureEvent = SDL_MultiGestureEvent;
	using DollarGestureEvent = SDL_DollarGestureEvent;
	using DropEvent = SDL_DropEvent;
	using QuitEvent = SDL_QuitEvent;
	using QuitEvent = SDL_QuitEvent;
	using UserEvent = SDL_UserEvent;
	using SysWMmsg = SDL_SysWMmsg;
	using SysWMEvent = SDL_SysWMEvent;
	//using Event = SDL_Event; // ready for class

	using EventAction = SDL_eventaction;

	class Event
	{
	public:
		const SDL_Event& getInstance() const;
		SDL_Event& getInstance();

		sdl::EventType::type type();
		sdl::CommonEvent common();
		sdl::WindowEvent window();
		sdl::KeyboardEvent key();
		sdl::TextEditingEvent edit();
		sdl::TextInputEvent text();
		sdl::MouseMotionEvent motion();
		sdl::MouseButtonEvent button();
		sdl::MouseWheelEvent wheel();
		sdl::JoyAxisEvent jaxis();
		sdl::JoyBallEvent jball();
		sdl::JoyHatEvent jhat();
		sdl::JoyButtonEvent jbutton();
		sdl::JoyDeviceEvent jdevice();
		sdl::ControllerAxisEvent caxis();
		sdl::ControllerButtonEvent cbutton();
		sdl::ControllerDeviceEvent cdevice();
		sdl::AudioDeviceEvent adevice();
		sdl::QuitEvent quit();
		sdl::UserEvent user();
		sdl::SysWMEvent syswm();
		sdl::TouchFingerEvent tfinger();
		sdl::MultiGestureEvent mgesture();
		sdl::DollarGestureEvent dgesture();
		sdl::DropEvent drop();

		bool pollEvent();

		bool is(EventType::type evType);
		bool hasEvent(EventType::type type);
		bool hasEvents(EventType::type minType, EventType::type maxType);
		bool wait(EventType::type type);
		bool waitTimeout(int timeout);

		static void flushEvent(EventType::type type);
		static void flushEvents(EventType::type minType, EventType::type maxType);
		/**
		*  \brief Add an event to the event queue.
		*
		*  \return 1 on success, 0 if the event was filtered, or -1 if the event queue
		*          was full or there was some other error.
		*/
		static int pushEvent(EventType::type type);

		explicit operator SDL_Event&();
		explicit operator const SDL_Event&() const;
	private:
		SDL_Event instance;
	};
}