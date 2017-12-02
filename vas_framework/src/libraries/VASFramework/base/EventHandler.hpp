#pragma once
#include <SDL.h>

namespace vas
{
	/*
	This class give the ability for drived class to handle event
	To implement this ability, override virtual void eventSlot(SDL_Event&)
	*/
	class EventHandler
	{
	public:
		EventHandler();
		virtual ~EventHandler();

		/*virtual void eventHandler(SDL_Event& eventBus);
		Give drived class have the ability to handle event*/
		virtual void eventSlot(SDL_Event& eventBus) = 0;
	};
}