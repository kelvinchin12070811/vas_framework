#pragma once
#include <SDL.h>
#include <array>
#include <boost/signals2.hpp>

#define VAS_CONNECT_PRE_EVENT(slot) vas::EventHandlerAPI().getSignal(vas::EventPulseSignalType::PreEventLoop).connect(boost::bind(slot, this, boost::placeholders::_1))
#define VAS_DISCONNECT_PRE_EVENT(slot) vas::EventHandlerAPI().getSignal(vas::EventPulseSignalType::PreEventLoop).disconnect(boost::bind(slot, this, boost::placeholders::_1))

#define VAS_CONNECT_POST_EVENT(slot) vas::EventHandlerAPI().getSignal(vas::EventPulseSignalType::PostEventLoop).connect(boost::bind(slot, this, boost::placeholders::_1))
#define VAS_DISCONNECT_POST_EVENT(slot) vas::EventHandlerAPI().getSignal(vas::EventPulseSignalType::PostEventLoop).disconnect(boost::bind(slot, this, boost::placeholders::_1))

namespace vas
{
	using EventPulseSignal = boost::signals2::signal<void(SDL_Event&)>;
	enum EventPulseSignalType : uint8_t { PreEventLoop, PostEventLoop };

	/*
	Give ability for object to recive event
	Connect object's function to recieve event
	*/
	class EventHandler
	{
	public:
		static EventHandler& getInstance();
		
		EventPulseSignal& getSignal(EventPulseSignalType type);
		void emitSignal(EventPulseSignalType type, SDL_Event& eventBus);
	private:
		EventHandler();
		~EventHandler();
		std::array<EventPulseSignal, 2> eventLoop;
	};
	inline vas::EventHandler& EventHandlerAPI() { return vas::EventHandler::getInstance(); };
}