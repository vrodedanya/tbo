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
		tbo::panel* parent = nullptr;
	public:
		explicit panel(tbo::style _style) : style(_style)
		{
			this->type = tbo::renderable::PANEL;
		}
		~panel()
		{
		}
		void draw(SDL_Renderer* renderer);

		tbo::style& get_style(){return style;}
		void set_parent(tbo::panel* parent){this->parent = parent;}
		tbo::panel* get_parent(){return parent;}
	};
}

#endif
