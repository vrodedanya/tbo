#include "../include/event_manager.hpp"
#include "../include/signal_manager.hpp"

void SDL2S::event_manager::update()
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_WINDOWEVENT:
				switch(event.window.event)
				{
					case SDL_WINDOWEVENT_CLOSE:
						SDL2S::signal_manager::add_signal(SDL2S::signal("program", std::to_string(event.window.windowID), "destroy window"));
						break;
				}
				break;
		}
	}
}
