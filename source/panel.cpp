#include "../include/panel.hpp"
#include <iostream>
#include "../include/drawing.hpp"

void tbo::panel::draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, style.background.color.r, style.background.color.g, style.background.color.b, style.background.color.a);

	int x = get_pixel_xpos(); // left xpos of panel
	int y = get_pixel_ypos(); // top ypos of panel
	int w =	get_pixel_width(); // panel's width
	int h = get_pixel_height(); // panel's height
	
	int parent_end_x = parent->get_pixel_xpos() + parent->get_pixel_width(); // right xpos of panel
	int parent_end_y = parent->get_pixel_ypos() + parent->get_pixel_height(); // bot ypos of panel;
	int x2 = (x + w) > parent_end_x ? parent_end_x : (x + w);
	int y2 = (y + h) > parent_end_y ? parent_end_y : (y + h);

	for (int ypos = y ; ypos < y2 ; ypos++)
	{
		for (int xpos = x ; xpos < x2 ; xpos++)
		{
			SDL_RenderDrawPoint(renderer, xpos, ypos);
		}
	}

	if (style.border.style != tbo::style::HIDDEN)
	{
		SDL_SetRenderDrawColor(renderer, style.border.color.r, style.border.color.g, style.border.color.b, style.border.color.a);
		int width = tbo::style::isPercent(style.border.width) ? tbo::style::get_fraction(style.border.width) * get_pixel_height() : style.border.width;
		tbo::drawing::line(renderer, x,  y,  x2, y,  width); // top
		tbo::drawing::line(renderer, x2, y,  x2, y2, width); // right
		tbo::drawing::line(renderer, x2, y2, x,  y2, width); // bot
		tbo::drawing::line(renderer, x,  y,  x,  y2, width); // left
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
