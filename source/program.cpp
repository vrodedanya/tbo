#include "../include/program.hpp"


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
