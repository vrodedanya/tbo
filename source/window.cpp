#include "../include/window.hpp"

void SDL2S::window::update()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}
