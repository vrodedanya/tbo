#include "../include/event_manager.hpp"

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
						SDL_Window* wind = SDL_GetWindowFromID(event.window.windowID);
						SDL_DestroyWindow(wind);
						break;
				}
				break;
		}
	}
}
