#include "../include/program.hpp"
#include <algorithm>
#include <stdexcept>
#include "../include/signal_manager.hpp"

void SDL2S::program::add_window(const std::string& name, const char* title, int width, int height, int xpos, int ypos, Uint32 window_flags, Uint32 renderer_flags)
{
	SDL2S::window* win = new SDL2S::window(title, width, height, xpos, ypos, window_flags, renderer_flags);
	windows_map[name] = win;
	windows.emplace_back(win);
}

void SDL2S::program::loop()
{
	SDL_Event event;
	while (1)
	{
		SDL2S::signal sig = SDL2S::signal_manager::get_signal("program");
		if (sig.recipient != "")
		{
			std::cerr << "Recipient: " << sig.recipient << std::endl;
			std::cerr << "ID       : " << sig.id << std::endl;
			std::cerr << "Command  : " << sig.command << std::endl;
		}
		for (auto& window : windows)
		{
			window->update();
		}
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) std::abort();
		}
	}
}

SDL2S::window* SDL2S::program::get_window(const char* window_name)
{
	if (windows_map.find(window_name) == windows_map.end())
	{
		throw std::runtime_error("This window doesn't exist!");
	}
	return windows_map[window_name];
}
