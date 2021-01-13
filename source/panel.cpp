#include "../include/panel.hpp"
#include <iostream>

void tbo::panel::draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, style.color.r, style.color.g, style.color.b, style.color.a);

	int x = (style.position.x & tbo::style::PERCENT) == static_cast<int>(tbo::style::PERCENT) ? (static_cast<double>(style.position.x & static_cast<int>(tbo::style::PERCENT - 1)) / 100) * window.width : style.position.x;
	int y = (style.position.y & tbo::style::PERCENT) == static_cast<int>(tbo::style::PERCENT) ? (static_cast<double>(style.position.y & static_cast<int>(tbo::style::PERCENT - 1)) / 100) * window.height : style.position.y;

	int w = (style.size.width & tbo::style::PERCENT) == static_cast<int>(tbo::style::PERCENT) ? (static_cast<double>(style.size.width & static_cast<int>(tbo::style::PERCENT - 1)) / 100) * window.width : style.size.width;
	int h = (style.size.height & tbo::style::PERCENT) == static_cast<int>(tbo::style::PERCENT) ? (static_cast<double>(style.size.height & static_cast<int>(tbo::style::PERCENT - 1)) / 100) * window.height : style.size.height;

	for (int ypos = y; ypos < y + h ; ypos++)
	{
		for (int xpos = x; xpos < x + w ; xpos++)
		{
			SDL_RenderDrawPoint(renderer, xpos, ypos);
		}
	}
}

