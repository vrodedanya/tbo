#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include "SDL_events.h"
#include "subscriber.hpp"

namespace tbo
{
	class event_manager : public subscriber
	{
	private:
		SDL_Event event;
		void signal_handler(std::string command);
		bool isWorking();
	public:
		event_manager();
		void update();
	};
}

#endif
