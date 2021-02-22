#ifndef DRAWING_HPP
#define DRAWING_HPP

#include "SDL.h"
#include "types.hpp"

namespace tbo
{
	using renderer = SDL_Renderer;
	class drawing
	{
	public:
		static void line(tbo::renderer* renderer, int x1, int y1, int x2, int y2, int thickness);

		static void point(tbo::renderer* renderer, int x, int y);

		static void circle(tbo::renderer* renderer, int x, int y, int radius);

		static void rect(tbo::renderer* renderer, int x, int y, int width, int height);

		static void fillScreen(tbo::renderer* renderer);

		static void changeColor(tbo::renderer* renderer, tbo::byte r, tbo::byte g, tbo::byte b, tbo::byte a);

		static void updateRenderer(tbo::renderer* renderer);
	};
}

#endif
