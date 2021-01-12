#include "../include/panel.hpp"
#include <iostream>

void tbo::panel::draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

	int x = (style.position.x & tbo::style::PERCENT) == tbo::style::PERCENT ? (static_cast<double>(style.position.x & 255) / 100) * window.width : style.position.x;
	int y = (style.position.y & tbo::style::PERCENT) == tbo::style::PERCENT ? (static_cast<double>(style.position.y & 255) / 100) * window.height : style.position.y;

	int w = (style.size.width & tbo::style::PERCENT) == tbo::style::PERCENT ? (static_cast<double>(style.size.width & 255) / 100) * window.width : style.size.width;
	int h = (style.size.height & tbo::style::PERCENT) == tbo::style::PERCENT ? (static_cast<double>(style.size.height & 255) / 100) * window.height : style.size.height;

	for (int ypos = y; ypos < y + h ; ypos++)
	{
		for (int xpos = x; xpos < x + w ; xpos++)
		{
			SDL_RenderDrawPoint(renderer, xpos, ypos);
		}
	}
}

