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
	while (!windows.empty())
	{
		tbo::time::range::begin();
		try
		{
			emanager->update();
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
		tbo::time::range::deltaEnd();
		tbo::logger::log("program", tbo::logger::LOW_PRIORITY, "loop ended with", 1 / tbo::time::range::get_delta(), "fps");
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
		return nullptr;
	}
	return windows_map[window_name];
}

void tbo::program::signal_handler(std::string command)
{
	std::vector<std::string> arguments = tbo::parser::split(command, ' ');
	
	if (arguments[0] == "destroy")
	{
		Uint32 id = std::stoi(arguments[1]);
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
