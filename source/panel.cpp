#include "../include/panel.hpp"
#include <iostream>

void tbo::panel::draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, style.color.r, style.color.g, style.color.b, style.color.a);

	int x = get_pixel_xpos();
	int y = get_pixel_ypos();
	int w =	get_pixel_width();
	int h = get_pixel_height();

	for (int ypos = y; ypos < y + h ; ypos++)
	{
		for (int xpos = x; xpos < x + w ; xpos++)
		{
			SDL_RenderDrawPoint(renderer, xpos, ypos);
		}
	}
}

int tbo::panel::get_pixel_xpos()
{
	if (parent == nullptr)
	{
		return 0;
	}
	else
	{
		int margin = tbo::style::isPercent(parent->get_style().margin.absolute) ? tbo::style::get_fraction(parent->get_style().margin.absolute) * parent->get_pixel_width() : parent->get_style().margin.absolute;
		margin += tbo::style::isPercent(parent->get_style().margin.left) ? tbo::style::get_fraction(parent->get_style().margin.left) * parent->get_pixel_width() : parent->get_style().margin.left;
		int current = (tbo::style::isPercent(style.position.x) ? (margin + tbo::style::get_fraction(style.position.x) * parent->get_pixel_width()) : (margin + style.position.x));
		return current + parent->get_pixel_xpos(); 
	}
}

int tbo::panel::get_pixel_ypos()
{
	if (parent == nullptr)
	{
		return 0;
	}
	else
	{
		int margin = tbo::style::isPercent(parent->get_style().margin.absolute) ? tbo::style::get_fraction(parent->get_style().margin.absolute) * parent->get_pixel_width() : parent->get_style().margin.absolute;
		margin += tbo::style::isPercent(parent->get_style().margin.top) ? tbo::style::get_fraction(parent->get_style().margin.top) * parent->get_pixel_height() : parent->get_style().margin.top;
		int current = (tbo::style::isPercent(style.position.y) ? (margin + tbo::style::get_fraction(style.position.y) * parent->get_pixel_height()) : (margin + style.position.y));
		return current + parent->get_pixel_ypos(); 
	}
}

int tbo::panel::get_pixel_width()
{
	if (parent == nullptr || !tbo::style::isPercent(style.size.width))
	{
		return style.size.width;
	}
	else
	{
		int value = tbo::style::get_fraction(style.size.width) * parent->get_pixel_width();
		return value;
	}
}

int tbo::panel::get_pixel_height()
{
	if (parent == nullptr || !tbo::style::isPercent(style.size.height))
	{
		return style.size.height;
	}
	else
	{
		return tbo::style::get_fraction(style.size.height) * parent->get_pixel_height();
	}
}
