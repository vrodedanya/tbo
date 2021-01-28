#include "../include/event_manager.hpp"
#include "../include/signal_manager.hpp"
#include "../include/logger.hpp"
#include <string>

void tbo::event_manager::update()
{
	std::string receiver;
	while (SDL_PollEvent(&event))
	{
		receiver = "window " + std::to_string(event.window.windowID);
		switch (event.type)
		{
			case SDL_WINDOWEVENT:
				switch(event.window.event)
				{
					case SDL_WINDOWEVENT_CLOSE:
						tbo::logger::log("event manager", tbo::logger::LOW_PRIORITY, "caught close window event");
						tbo::signal_manager::add_signal(tbo::signal("program", "destroy " + std::to_string(event.window.windowID)));
						break;
					case SDL_WINDOWEVENT_HIDDEN:
						break;
						tbo::logger::log("event manager", tbo::logger::LOW_PRIORITY, "caught hidden window event from", event.window.windowID);
						tbo::signal_manager::add_signal(tbo::signal(receiver, "hide"));
					case SDL_WINDOWEVENT_SHOWN:
						tbo::logger::log("event manager", tbo::logger::LOW_PRIORITY, "caught shown window event from", event.window.windowID);
						tbo::signal_manager::add_signal(tbo::signal(receiver, "show"));
						break;
					case SDL_WINDOWEVENT_EXPOSED:
						tbo::logger::log("event manager", tbo::logger::LOW_PRIORITY, "caught exposed window event from", event.window.windowID);
						break;
					case SDL_WINDOWEVENT_MOVED:
						tbo::logger::log("event manager", tbo::logger::LOW_PRIORITY, "caught move window event from", event.window.windowID, "new coords are", event.window.data1, event.window.data2);
						tbo::signal_manager::add_signal(tbo::signal(receiver, "move " + std::to_string(event.window.data1) + " " + std::to_string(event.window.data2)));
						break;
					case SDL_WINDOWEVENT_RESIZED:
					case SDL_WINDOWEVENT_SIZE_CHANGED:
						tbo::logger::log("event manager", tbo::logger::LOW_PRIORITY, "caught resize window event from", event.window.windowID, "new size are", event.window.data1, event.window.data2);
						tbo::signal_manager::add_signal(tbo::signal(receiver, "resize " + std::to_string(event.window.data1) + " " + std::to_string(event.window.data2)));
						break;
					case SDL_WINDOWEVENT_ENTER:
						tbo::logger::log("event manager", tbo::logger::LOW_PRIORITY, "caught enter window event from", event.window.windowID);
						tbo::signal_manager::add_signal(tbo::signal(receiver, "enter"));
						break;
					case SDL_WINDOWEVENT_LEAVE:
						tbo::logger::log("event manager", tbo::logger::LOW_PRIORITY, "caught leave window event from", event.window.windowID);
						tbo::signal_manager::add_signal(tbo::signal(receiver, "leave"));
						break;
					case SDL_WINDOWEVENT_TAKE_FOCUS:
						tbo::logger::log("event manager", tbo::logger::LOW_PRIORITY, "caught take focus window event from", event.window.windowID);
						break;
					case SDL_WINDOWEVENT_MAXIMIZED:
						tbo::logger::log("event manager", tbo::logger::LOW_PRIORITY, "caught maximized window event from", event.window.windowID);
						break;
					case SDL_WINDOWEVENT_MINIMIZED:
						tbo::logger::log("event manager", tbo::logger::LOW_PRIORITY, "caught minimized window event from", event.window.windowID);
						break;
					case SDL_WINDOWEVENT_HIT_TEST:
						tbo::logger::log("event manager", tbo::logger::LOW_PRIORITY, "caught hit test window event from", event.window.windowID);
						break;
					case SDL_WINDOWEVENT_RESTORED:
						tbo::logger::log("event manager", tbo::logger::LOW_PRIORITY, "caught restored window event from", event.window.windowID);
						break;
					case SDL_WINDOWEVENT_FOCUS_GAINED:
						tbo::logger::log("event manager", tbo::logger::LOW_PRIORITY, "caught focus gained window event from", event.window.windowID);
						break;
					case SDL_WINDOWEVENT_FOCUS_LOST:
						tbo::logger::log("event manager", tbo::logger::LOW_PRIORITY, "caught focus lost window event from", event.window.windowID);
						break;
					default:
						tbo::logger::log("event manager", tbo::logger::MEDIUM_PRIORITY, "caught unexpected window event");
				}
				break;
			case SDL_MOUSEMOTION:
				tbo::logger::log("event manager", tbo::logger::LOW_PRIORITY, "caught mouse motion event");
				tbo::signal_manager::add_signal(tbo::signal(receiver, "mouse " + std::to_string(event.motion.x) + " " + std::to_string(event.motion.y)));
				break;
		}

	}
}
