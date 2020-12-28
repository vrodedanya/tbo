#include "../include/window.hpp"
#include <utility>

int main()
{
	SDL2S::window wind("title", 400, 400);

	SDL2S::window test{std::move(wind)};

	SDL_Event event;
	bool isWork = true;
	while (isWork) 
	{
		wind.update();
		//test.update();
		while (SDL_PollEvent(&event))
			if (event.type == SDL_KEYDOWN) isWork = false;
	}
	return 0;
}
