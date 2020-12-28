#include "../include/window.hpp"

int main()
{
	Window window("title", 400, 400);


	SDL_Event event;
	bool isWork = true;
	while (isWork) 
	{
		window.update();
		while (SDL_PollEvent(&event))
			if (event.type == SDL_KEYDOWN) isWork = false;
	}
	return 0;
}
