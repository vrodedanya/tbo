#ifndef PANEL_HPP
#define PANEL_HPP

#include "renderable.hpp"
#include <SDL2/SDL.h>
#include "style.hpp"

namespace tbo
{
	class panel : public tbo::renderable
	{
	private:
		tbo::style style;
	public:
		explicit panel(tbo::renderable::Type type, tbo::style _style, int window_width, int window_height) : style(_style)
		{
			this->type = type;
			window.width = window_width;
			window.height = window_height;
		}
		void draw(SDL_Renderer* renderer);
	};
}

#endif
