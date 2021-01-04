#include "../include/program.hpp"
#include <algorithm>
#include <stdexcept>
#include "../include/signal_manager.hpp"
#include "../include/logger.hpp"

void tbo::program::signal_handler()
{
	tbo::signal sig;
	while((sig = tbo::signal_manager::get_signal("program")) != tbo::signal("","",""))
	{
		tbo::logger::log("program", "receiving signal (", sig, ")");		
		if (sig.command == "destroy window")
		{
			Uint32 id = std::stoi(sig.id);
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
				tbo::logger::log("program", "window with id", id, "was destroyed");
			}
		}
		else if (sig.command == "window shown")
		{
			Uint32 id = std::stoi(sig.id);
			auto it = std::find_if (windows.begin(), windows.end(), [id](tbo::window* w){return SDL_GetWindowID(w->get_window()) == id;});
			(*it)->set_isShown(true);
		}
		else if (sig.command == "window hidden")
		{
			Uint32 id = std::stoi(sig.id);
			auto it = std::find_if (windows.begin(), windows.end(), [id](tbo::window* w){return SDL_GetWindowID(w->get_window()) == id;});
			(*it)->set_isShown(false);
		}
		else if (sig.command == "window enter")
		{
			Uint32 id = std::stoi(sig.id);
			auto it = std::find_if (windows.begin(), windows.end(), [id](tbo::window* w){return SDL_GetWindowID(w->get_window()) == id;});
			(*it)->set_isMouseIn(true);
		}
		else if (sig.command == "window leave")
		{
			Uint32 id = std::stoi(sig.id);
			auto it = std::find_if (windows.begin(), windows.end(), [id](tbo::window* w){return SDL_GetWindowID(w->get_window()) == id;});
			(*it)->set_isMouseIn(false);
		}
		else if (sig.command == "move window")
		{
			//TODO Fix signal structure
		}
		else if (sig.command == "resize window")
		{
			//TODO Fix signal structure
		}
		else
		{
			throw std::runtime_error("Unexpected command: " + sig.command);
		}
	}
}

void tbo::program::loop()
{
	while (!windows.empty())
	{
		emanager->update();
		signal_handler();
		for (auto& window : windows)
		{
			window->update();
		}
	}
}

void tbo::program::add_window(const std::string& name, const char* title, int width, int height, int xpos, int ypos, Uint32 window_flags, Uint32 renderer_flags)
{
	tbo::window* win = new tbo::window(title, width, height, xpos, ypos, window_flags, renderer_flags);
	windows_map[name] = win;
	windows.emplace_back(win);
	tbo::logger::log("program", "added new window with name", name);
}

tbo::window* tbo::program::get_window(const char* window_name)
{
	if (windows_map.find(window_name) == windows_map.end())
	{
		throw std::runtime_error("This window doesn't exist!");
	}
	return windows_map[window_name];
}
