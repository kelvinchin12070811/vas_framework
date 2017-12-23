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
		switch (type)
		{
		case EventPulseSignalType::PreEventLoop:
			return this->preEventLoop;
			break;
		case EventPulseSignalType::PostEventLoop:
			return this->postEvnetLoop;
			break;
		default:
			return this->preEventLoop;
		}
	}

	void EventHandler::emitSignal(EventPulseSignalType type, SDL_Event & eventBus)
	{
		switch (type)
		{
		case EventPulseSignalType::PreEventLoop:
			this->preEventLoop(eventBus);
			break;
		case EventPulseSignalType::PostEventLoop:
			this->postEvnetLoop(eventBus);
			break;
		}
	}

	EventHandler::EventHandler()
	{
	}


	EventHandler::~EventHandler()
	{
	}
}