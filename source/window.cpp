#include "../include/window.hpp"
#include <algorithm>
#include <stdexcept>

void SDL2S::window::update()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	for (auto& obj : objects)
	{
		obj->draw(renderer);
	}

	SDL_RenderPresent(renderer);
}

void SDL2S::window::add_object(SDL2S::renderable* obj)
{
	if (std::find(objects.begin(), objects.end(), obj) != objects.end())
	{
		throw std::runtime_error("Object is already exist");
	}
	objects.emplace_back(obj);
}
