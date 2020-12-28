#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>

class Window
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
public:
	explicit Window(const char* title, int width = 100, int height = 100, int xpos = SDL_WINDOWPOS_CENTERED, int ypos = SDL_WINDOWPOS_CENTERED, Uint32 window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, Uint32 renderer_flags = SDL_RENDERER_ACCELERATED)
	{
		if (SDL_WasInit(SDL_INIT_VIDEO) == 0) SDL_Init(SDL_INIT_VIDEO);
		window = SDL_CreateWindow(title, xpos, ypos, width, height, window_flags);
		renderer = SDL_CreateRenderer(window, -1, renderer_flags);
	}	
	~Window()
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}
	SDL_Window* get_window(){return window;}
	SDL_Renderer* get_renderer(){return renderer;}

	void update();
};

#endif
