#include "EventHandler.hpp"

namespace vas
{
	EventHandler & EventHandler::getInstance()
	{
		static EventHandler instance;
		return instance;
	}

	EventPulseSignal & EventHandler::getSignal(EventPulseSignalType type)
	{
		return this->eventLoop[type];
	}

	void EventHandler::emitSignal(EventPulseSignalType type, SDL_Event & eventBus)
	{
		this->eventLoop[type](eventBus);
	}

	EventHandler::EventHandler()
	{
	}


	EventHandler::~EventHandler()
	{
	}
}