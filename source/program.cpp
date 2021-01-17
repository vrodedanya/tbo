#include "../include/program.hpp"
#include <algorithm>
#include <stdexcept>
#include "../include/signal_manager.hpp"
#include "../include/logger.hpp"
#include "../include/parser.hpp"

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
		else if (command[0] == "show")
		{
			Uint32 id = std::stoi(command[1]);
			auto it = std::find_if (windows.begin(), windows.end(), [id](tbo::window* w){return SDL_GetWindowID(w->get_window()) == id;});
			(*it)->set_isShown(true);
		}
		else if (command[0] == "hide")
		{
			Uint32 id = std::stoi(command[1]);
			auto it = std::find_if (windows.begin(), windows.end(), [id](tbo::window* w){return SDL_GetWindowID(w->get_window()) == id;});
			(*it)->set_isShown(false);
		}
		else if (command[0] == "enter")
		{
			Uint32 id = std::stoi(command[1]);
			auto it = std::find_if (windows.begin(), windows.end(), [id](tbo::window* w){return SDL_GetWindowID(w->get_window()) == id;});
			(*it)->set_isMouseIn(true);
		}
		else if (command[0] == "leave")
		{
			Uint32 id = std::stoi(command[1]);
			auto it = std::find_if (windows.begin(), windows.end(), [id](tbo::window* w){return SDL_GetWindowID(w->get_window()) == id;});
			(*it)->set_isMouseIn(false);
		}
		else if (command[0] == "move")
		{
			Uint32 id = std::stoi(command[1]);
			auto it = std::find_if (windows.begin(), windows.end(), [id](tbo::window* w){return SDL_GetWindowID(w->get_window()) == id;});
		}
		else if (command[0] == "resize")
		{
			Uint32 id = std::stoi(command[1]);
			auto it = std::find_if (windows.begin(), windows.end(), [id](tbo::window* w){return SDL_GetWindowID(w->get_window()) == id;});
			(*it)->get_style().size.width  = std::stoi(command[2]);
			(*it)->get_style().size.height = std::stoi(command[3]);
		}
		else
		{
			throw std::runtime_error("Unexpected command: " + command[0]);
		}
	}
}

int tbo::program::loop()
{
	while (!windows.empty())
	{
		try
		{
			emanager->update();
			signal_handler();
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
	}
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
