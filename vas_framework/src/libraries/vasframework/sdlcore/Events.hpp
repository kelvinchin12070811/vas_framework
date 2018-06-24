#pragma once
#include <SDL.h>
#include "../VASConfig.hpp"

namespace vas::sdl
{
	struct EventType
	{
		using type = uint32_t;
		static const uint32_t firstevent = SDL_FIRSTEVENT;     /**< Unused (do not remove) */
		/* Application events */
		static const uint32_t quit = SDL_QUIT; /**< User-requested quit */

		/* These application events have special meaning on iOS, see README-ios.md for details */
		static const uint32_t app_terminating = SDL_APP_TERMINATING;        /**< The application is being terminated by the OS
								Called on iOS in applicationWillTerminate()
								Called on Android in onDestroy()
								*/
		static const uint32_t app_lowmemory = SDL_APP_LOWMEMORY;         /**< The application is low on memory, free memory if possible.
								Called on iOS in applicationDidReceiveMemoryWarning()
								Called on Android in onLowMemory()
								*/
		static const uint32_t app_willenterbackground = SDL_APP_WILLENTERBACKGROUND; /**< The application is about to enter the background
								 Called on iOS in applicationWillResignActive()
								 Called on Android in onPause()
								 */
		static const uint32_t app_didenterbackground = SDL_APP_DIDENTERBACKGROUND; /**< The application did enter the background and may not get CPU for some time
								Called on iOS in applicationDidEnterBackground()
								Called on Android in onPause()
								*/
		static const uint32_t app_willenterforeground = SDL_APP_WILLENTERFOREGROUND; /**< The application is about to enter the foreground
								 Called on iOS in applicationWillEnterForeground()
								 Called on Android in onResume()
								 */
		static const uint32_t app_didenterforeground = SDL_APP_DIDENTERFOREGROUND; /**< The application is now interactive
								Called on iOS in applicationDidBecomeActive()
								Called on Android in onResume()
								*/

		/* Window events */
		static const uint32_t windowevent = SDL_WINDOWEVENT; /**< Window state change */
		static const uint32_t syswmevent = SDL_SYSWMEVENT;             /**< System specific event */

		/* Keyboard events */
		static const uint32_t keydown = SDL_KEYDOWN; /**< Key pressed */
		static const uint32_t keyup = SDL_KEYUP;                  /**< Key released */
		static const uint32_t textediting = SDL_TEXTEDITING;            /**< Keyboard text editing (composition) */
		static const uint32_t textinput = SDL_TEXTINPUT;              /**< Keyboard text input */
		static const uint32_t keymapchanged = SDL_KEYMAPCHANGED;          /**< Keymap changed due to a system event such as an
								input language or keyboard layout change.
								*/

		/* Mouse events */
		static const uint32_t mousemotion = SDL_MOUSEMOTION; /**< Mouse moved */
		static const uint32_t mousebuttondown = SDL_MOUSEBUTTONDOWN;        /**< Mouse button pressed */
		static const uint32_t mousebuttonup = SDL_MOUSEBUTTONUP;          /**< Mouse button released */
		static const uint32_t mousewheel = SDL_MOUSEWHEEL;             /**< Mouse wheel motion */

		/* Joystick events */
		static const uint32_t joyaxismotion = SDL_JOYAXISMOTION; /**< Joystick axis motion */
		static const uint32_t joyballmotion = SDL_JOYBALLMOTION;          /**< Joystick trackball motion */
		static const uint32_t joyhatmotion = SDL_JOYHATMOTION;           /**< Joystick hat position change */
		static const uint32_t joybuttondown = SDL_JOYBUTTONDOWN;          /**< Joystick button pressed */
		static const uint32_t joybuttonup = SDL_JOYBUTTONUP;            /**< Joystick button released */
		static const uint32_t joydeviceadded = SDL_JOYDEVICEADDED;         /**< A new joystick has been inserted into the system */
		static const uint32_t joydeviceremoved = SDL_JOYDEVICEREMOVED;       /**< An opened joystick has been removed */

		/* Game controller events */
		static const uint32_t controlleraxismotion = SDL_CONTROLLERAXISMOTION; /**< Game controller axis motion */
		static const uint32_t controllerbuttondown = SDL_CONTROLLERBUTTONDOWN;          /**< Game controller button pressed */
		static const uint32_t controllerbuttonup = SDL_CONTROLLERBUTTONUP;            /**< Game controller button released */
		static const uint32_t controllerdeviceadded = SDL_CONTROLLERDEVICEADDED;         /**< A new Game controller has been inserted into the system */
		static const uint32_t controllerdeviceremoved = SDL_CONTROLLERDEVICEREMOVED;       /**< An opened Game controller has been removed */
		static const uint32_t controllerdeviceremapped = SDL_CONTROLLERDEVICEREMAPPED;      /**< The controller mapping was updated */

		/* Touch events */
		static const uint32_t fingerdown = SDL_FINGERUP;
		static const uint32_t fingerup = SDL_FINGERDOWN;
		static const uint32_t fingermotion = SDL_FINGERMOTION;

		/* Gesture events */
		static const uint32_t dollargesture = SDL_DOLLARGESTURE;
		static const uint32_t dollarrecord = SDL_DOLLARRECORD;
		static const uint32_t multigesture = SDL_MULTIGESTURE;

		/* Clipboard events */
		static const uint32_t clipboardupdate = SDL_CLIPBOARDUPDATE; /**< The clipboard changed */

		/* Drag and drop events */
		static const uint32_t dropfile = SDL_DROPFILE; /**< The system requests a file open */
		static const uint32_t droptext = SDL_DROPTEXT;                 /**< text/plain drag-and-drop event */
		static const uint32_t dropbegin = SDL_DROPBEGIN;                /**< A new set of drops is beginning (NULL filename) */
		static const uint32_t dropcomplete = SDL_DROPCOMPLETE;             /**< Current set of drops is now complete (NULL filename) */

		/* Audio hotplug events */
		static const uint32_t audiodeviceadded = SDL_AUDIODEVICEADDED; /**< A new audio device is available */
		static const uint32_t audiodeviceremoved = SDL_AUDIODEVICEREMOVED;        /**< An audio device has been removed. */

		/* Render events */
		static const uint32_t render_targets_reset = SDL_RENDER_TARGETS_RESET; /**< The render targets have been reset and their contents need to be updated */
		static const uint32_t render_device_reset = SDL_RENDER_DEVICE_RESET; /**< The device has been reset and all textures need to be recreated */

		/** Events ::SDL_USEREVENT through ::SDL_LASTEVENT are for your use,
		*  and should be allocated with SDL_RegisterEvents()
		*/
		static const uint32_t userevent = SDL_USEREVENT;

		/**
		*  This last event is only for bounding internal arrays
		*/
		static const uint32_t lastevent = SDL_LASTEVENT;
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

	class VAS_DECLSPEC Event
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

		bool operator==(const EventType::type& type) const;
		bool operator!=(const EventType::type& type) const;

		operator const EventType::type();

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