#ifndef DRAWING_HPP
#define DRAWING_HPP

#include <SDL2/SDL.h>

namespace tbo
{
	class drawing
	{
	public:
		static void line(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int thickness);
	};
}

#endif
