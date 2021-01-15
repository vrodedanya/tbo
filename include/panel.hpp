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
		explicit panel(tbo::renderable::Type type, tbo::style _style) : style(_style)
		{
			this->type = type;
		}
		void draw(SDL_Renderer* renderer);

		tbo::style& get_style(){return style;}
	};
}

#endif
