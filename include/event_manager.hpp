#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <SDL2/SDL_events.h>

namespace SDL2S
{
	class event_manager
	{
	private:
		SDL_Event event;
	public:
		void update();
	};
}

#endif
