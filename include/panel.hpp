#ifndef PANEL_HPP
#define PANEL_HPP

#include "renderable.hpp"
#include "style.hpp"

namespace tbo
{
	class panel : public tbo::renderable
	{
	private:
		tbo::style style;
		tbo::style hover;
		tbo::panel* parent = nullptr;
		bool isHover = false;
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
		void set_parent(tbo::panel* _parent){this->parent = _parent;}
		tbo::panel* get_parent(){return parent;}

		void check_isHover(int xpos, int ypos);

		void set_hover_style(tbo::style hover)
		{
			this->hover = hover;
		}

		int get_pixel_xpos();
		int get_pixel_ypos();
		int get_pixel_width();
		int get_pixel_height();
	};
}

#endif
