#include "../include/drawing.hpp"
#include <cmath>
#include <iostream>

void tbo::drawing::line(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int thickness)
{
	SDL_Rect brash = {0, 0, thickness, thickness};	
	double xpos = x1, ypos = y1;

	while (std::abs(xpos - x2) >= 1 || std::abs(ypos - y2) >= 1)
	{
		brash.x = xpos - brash.w / 2;
		brash.y = ypos - brash.h / 2;
		std::cout << brash.w << " " << brash.h << " " << brash.x << " " << brash.y << std::endl;

		SDL_RenderFillRect(renderer, &brash);

		xpos += (x2 - x1) / std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
		ypos += (y2 - y1) / std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
	}
}
