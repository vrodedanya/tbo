#include "../include/event_manager.hpp"
#include "../include/signal_manager.hpp"
#include "../include/logger.hpp"

void tbo::event_manager::update()
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_WINDOWEVENT:
				switch(event.window.event)
				{
					case SDL_WINDOWEVENT_CLOSE:
						tbo::logger::log("event manager", "caught close window event");
						tbo::signal_manager::add_signal(tbo::signal("program", std::to_string(event.window.windowID), "destroy window"));
						break;
					case SDL_WINDOWEVENT_HIDDEN:
						break;
						tbo::logger::log("event manager", "caught hidden window event from", event.window.windowID);
						tbo::signal_manager::add_signal(tbo::signal("program", std::to_string(event.window.windowID), "window hidded"));
					case SDL_WINDOWEVENT_SHOWN:
						tbo::logger::log("event manager", "caught shown window event from", event.window.windowID);
						//tbo::signal_manager::add_signal(tbo::signal("program", std::to_string(event.window.windowID), "window shown"));
						break;
					case SDL_WINDOWEVENT_EXPOSED:
						tbo::logger::log("event manager", "caught exposed window event from", event.window.windowID, "- This event doesn't hadling now");
						break;
					case SDL_WINDOWEVENT_MOVED:
						tbo::logger::log("event manager", "caught move window event from", event.window.windowID, "new coords are", event.window.data1, event.window.data2);
						break;
					case SDL_WINDOWEVENT_RESIZED:
					case SDL_WINDOWEVENT_SIZE_CHANGED:
						tbo::logger::log("event manager", "caught resize window event from", event.window.windowID);
						break;
					case SDL_WINDOWEVENT_ENTER:
						tbo::logger::log("event manager", "caught enter window event from", event.window.windowID);
						break;
					case SDL_WINDOWEVENT_LEAVE:
						tbo::logger::log("event manager", "caught leave window event from", event.window.windowID);
						break;
					case SDL_WINDOWEVENT_TAKE_FOCUS:
						tbo::logger::log("event manager", "caught take focus window event from", event.window.windowID);
						break;
					case SDL_WINDOWEVENT_MAXIMIZED:
						tbo::logger::log("event manager", "caught maximized window event from", event.window.windowID);
						break;
					case SDL_WINDOWEVENT_MINIMIZED:
						tbo::logger::log("event manager", "caught minimized window event from", event.window.windowID);
						break;
					case SDL_WINDOWEVENT_HIT_TEST:
						tbo::logger::log("event manager", "caught hit test window event from", event.window.windowID);
						break;
					case SDL_WINDOWEVENT_RESTORED:
						tbo::logger::log("event manager", "caught restored window event from", event.window.windowID);
						break;
					case SDL_WINDOWEVENT_FOCUS_GAINED:
						tbo::logger::log("event manager", "caught focus gained window event from", event.window.windowID);
						break;
					case SDL_WINDOWEVENT_FOCUS_LOST:
						tbo::logger::log("event manager", "caught focus lost window event from", event.window.windowID);
						break;
					default:
						tbo::logger::log("event manager", "caught unexpected window event");
				}
				break;
		}
	}
}
