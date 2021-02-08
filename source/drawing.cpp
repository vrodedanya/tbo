#include "drawing.hpp"
#include <cmath>
#include <iostream>

void tbo::drawing::line(tbo::renderer* renderer, int x1, int y1, int x2, int y2, int thickness)
{
	SDL_Rect brash = {0, 0, thickness, thickness};	
	double xpos = x1, ypos = y1;

	while (std::abs(xpos - x2) >= 1 || std::abs(ypos - y2) >= 1)
	{
		brash.x = xpos - brash.w / 2;
		brash.y = ypos - brash.h / 2;

		SDL_RenderFillRect(renderer, &brash);

		xpos += (x2 - x1) / std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
		ypos += (y2 - y1) / std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
	}
}

void tbo::drawing::point(tbo::renderer* renderer, int x, int y)
{
	SDL_RenderDrawPoint(renderer, x, y);
}

void tbo::drawing::circle(tbo::renderer* renderer, int x0, int y0, int radius)
{
	int power_radius = std::pow(radius, 2);
	for (int x = x0 - radius ; x < x0 + radius ; x++)
	{
		for (int y = y0 - radius ; y < y0 + radius ; y++)
		{
			if (std::pow(x - x0, 2) + std::pow(y - y0, 2) <= power_radius)
			{
				tbo::drawing::point(renderer, x, y);
			}
		}
	}
}

void tbo::drawing::rect(tbo::renderer* renderer, int x0, int y0, int width, int height)
{
	for (int x = x0 ; x < x0 + width ; x++)
	{
		for (int y = y0 ; y < y0 + height ; y++)
		{
			tbo::drawing::point(renderer, x, y);
		}
	}
}
		
void tbo::drawing::fillScreen(tbo::renderer* renderer)
{
	SDL_RenderClear(renderer);
}

void tbo::drawing::changeColor(tbo::renderer* renderer, tbo::byte r, tbo::byte g, tbo::byte b, tbo::byte a)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void tbo::drawing::updateRenderer(tbo::renderer* renderer)
{
	SDL_RenderPresent(renderer);
}
