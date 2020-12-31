#ifndef PANEL_HPP
#define PANEL_HPP

#include "renderable.hpp"
#include <SDL2/SDL.h>

namespace SDL2S
{
	class panel : public SDL2S::renderable
	{
	private:
		SDL_Rect body;
	public:
		explicit panel(int width, int height, int xpos, int ypos) : body({xpos, ypos, height, width})
		{
		}
		void draw(SDL_Renderer* renderer);
	};
}

#endif
