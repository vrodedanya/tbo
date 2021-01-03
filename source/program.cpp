#include "../include/program.hpp"
#include <algorithm>
#include <stdexcept>
#include "../include/signal_manager.hpp"

void tbo::program::signal_handler()
{
	tbo::signal sig;
	while((sig = tbo::signal_manager::get_signal("program")) != tbo::signal("","",""))
	{
#ifdef DEBUG
		std::cerr << "Program receiving signal..." << std::endl;
		std::cerr << sig << std::endl; 
#endif
		if (sig.command == "destroy window")
		{
			Uint32 id = std::stoi(sig.id);
			auto it = std::find_if (windows.begin(), windows.end(), [id](tbo::window* w){return SDL_GetWindowID(w->get_window()) == id;});

			if (it != windows.end())
			{
				delete *it;
				windows.erase(it);
#ifdef DEBUG
				std::cerr << "Window with id " << id << " was destroyed" << std::endl;
#endif
			}
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
}

tbo::window* tbo::program::get_window(const char* window_name)
{
	if (windows_map.find(window_name) == windows_map.end())
	{
		throw std::runtime_error("This window doesn't exist!");
	}
	return windows_map[window_name];
}
