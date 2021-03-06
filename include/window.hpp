#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <vector>
#include "renderable.hpp"
#include "panel.hpp"
#include "logger.hpp"
#include "subscriber.hpp"

namespace tbo
{
	class window : public subscriber
	{
	private:
		SDL_Window* wind;
		tbo::renderer* renderer;
		std::vector<tbo::renderable*> objects;
		bool isShown = true;
		bool isMouseIn = false;

		tbo::panel* body = nullptr;
		void signal_handler(std::string command);
	public:
		explicit window(const char* title, int width = 100, int height = 100, int xpos = SDL_WINDOWPOS_CENTERED, int ypos = SDL_WINDOWPOS_CENTERED, Uint32 window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, Uint32 renderer_flags = SDL_RENDERER_ACCELERATED);

		window(const window& wind) = delete;

		window(window&& w);

		~window();

		void update(); // render all objects

		void add_object(tbo::renderable* obj);
		tbo::panel& add_panel(tbo::style style);
		tbo::panel& add_panel(tbo::style style, tbo::panel* parent);
		void remove_object(tbo::renderable* obj);

		SDL_Window* get_window(){return wind;}
		tbo::renderer* get_renderer(){return renderer;}

		std::vector<tbo::renderable*>& get_objects(){return objects;}

		void set_isShown(bool _isShown){isShown = _isShown;}
		bool get_isShown(){return isShown;}

		void set_isMouseIn(bool _isMouseIn){isMouseIn = _isMouseIn;}
		bool get_isMouseIn(){return isMouseIn;}

		tbo::style& get_style(){return body->get_style();}
	};
}

#endif
