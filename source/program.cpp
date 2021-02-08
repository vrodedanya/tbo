#include "program.hpp"
#include <algorithm>
#include <stdexcept>
#include "signal_manager.hpp"
#include "logger.hpp"
#include "parser.hpp"
#include "time.hpp"
#include <thread>

tbo::program::~program()
{
	delete emanager;
	for (auto& window : windows)
	{
		delete window;
	}
	tbo::logger::log("program", tbo::logger::MEDIUM_PRIORITY, "was called destructor");
}

int tbo::program::loop()
{
	std::thread eventmanager(&tbo::event_manager::update, emanager);
	while (!windows.empty())
	{
		tbo::time::timerange::begin();
		try
		{
			signal_handler();
			update();
			for (auto& window : windows)
			{
				window->update();
			}
		}
		catch (const std::exception& except)
		{
			tbo::logger::log("program", tbo::logger::HIGH_PRIORITY, except.what());
			return EXIT_FAILURE;
		}
		tbo::time::timerange::end();
		tbo::logger::log("program", tbo::logger::LOW_PRIORITY, "loop ended with", 1 / tbo::time::timerange::get_delta(), "fps");
	}
	tbo::signal_manager::add_signal(tbo::signal("eventmanager", "shutdown"));
	eventmanager.join();
	return EXIT_SUCCESS;
}

void tbo::program::add_window(const std::string& name, const char* title, int width, int height, int xpos, int ypos, Uint32 window_flags, Uint32 renderer_flags)
{
	tbo::window* win = new tbo::window(title, width, height, xpos, ypos, window_flags, renderer_flags);
	windows_map[name] = win;
	windows.emplace_back(win);
	tbo::logger::log("program", tbo::logger::MEDIUM_PRIORITY, "added new window with name", name);
}

tbo::window* tbo::program::get_window(const char* window_name)
{
	if (windows_map.find(window_name) == windows_map.end())
	{
		throw std::runtime_error("This window doesn't exist!");
	}
	return windows_map[window_name];
}

void tbo::program::signal_handler()
{
	tbo::signal sig;
	while((sig = tbo::signal_manager::get_signal("program")) != tbo::signal("",""))
	{
		tbo::logger::log("program", tbo::logger::LOW_PRIORITY, "receiving signal (", sig, ")");		
		std::vector<std::string> command = tbo::parser::split(sig.command, ' ');
		
		if (command[0] == "destroy")
		{
			Uint32 id = std::stoi(command[1]);
			auto it = std::find_if (windows.begin(), windows.end(), [id](tbo::window* w){return SDL_GetWindowID(w->get_window()) == id;});
			if (it != windows.end())
			{
				delete *it;
				windows.erase(it);
				for (auto map_it = windows_map.begin() ; map_it != windows_map.end() ; map_it++)
				{
					if (map_it->second == *it) 
					{
						windows_map.erase(map_it);
						break;
					}
				}
				tbo::logger::log("program", tbo::logger::MEDIUM_PRIORITY, "window with id", id, "was destroyed");
			}
		}

	}
}
