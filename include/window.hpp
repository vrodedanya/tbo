#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include <vector>
#include "../include/renderable.hpp"
#include "../include/panel.hpp"
#include "logger.hpp"

namespace tbo
{
	class window
	{
	private:
		SDL_Window* wind;
		SDL_Renderer* renderer;
		std::vector<tbo::renderable*> objects;
		bool isShown = true;
		bool isMouseIn = false;

		tbo::panel* body = nullptr;
	public:
		explicit window(const char* title, int width = 100, int height = 100, int xpos = SDL_WINDOWPOS_CENTERED, int ypos = SDL_WINDOWPOS_CENTERED, Uint32 window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, Uint32 renderer_flags = SDL_RENDERER_ACCELERATED)
		{
			if (SDL_WasInit(SDL_INIT_VIDEO) == 0) 
			{
				if (SDL_Init(SDL_INIT_VIDEO) != 0) throw std::runtime_error("Video initializing error");
				tbo::logger::log("window", tbo::logger::MEDIUM_PRIORITY, "SDL2 was initialized");
			}
			if ((wind = SDL_CreateWindow(title, xpos, ypos, width, height, window_flags)) == NULL)
			{
				throw std::runtime_error("Creating window error");
			}
			tbo::logger::log("window", tbo::logger::MEDIUM_PRIORITY, "new window was created with id", SDL_GetWindowID(wind));
 
			if ((renderer = SDL_CreateRenderer(wind, -1, renderer_flags)) == NULL)
			{
				throw std::runtime_error("Creating renderer error");
			}
			tbo::logger::log("window", tbo::logger::MEDIUM_PRIORITY, "window's renderer was created");

			tbo::style style;
			style.size.width = width | tbo::style::PIXELS;
			style.size.height = height | tbo::style::PIXELS;
			body = new tbo::panel(style);
		}	
		window(const window& wind) = delete;
		window(window&& w)
		{
			this->body = w.body;
			this->wind = w.wind;
			this->renderer = w.renderer;
			w.body = nullptr;
			w.wind = nullptr;
			w.renderer = nullptr;
			tbo::logger::log("window", tbo::logger::MEDIUM_PRIORITY, "called move constructor");
		}
		~window()
		{
			delete body;
			if (renderer != nullptr) SDL_DestroyRenderer(renderer);
			if (wind != nullptr) SDL_DestroyWindow(wind);
			tbo::logger::log("window", tbo::logger::MEDIUM_PRIORITY, "called destructor");
		}
		SDL_Window* get_window(){return wind;}
		SDL_Renderer* get_renderer(){return renderer;}

		void update(); // render all objects

		std::vector<tbo::renderable*>& get_objects(){return objects;}

		void add_object(tbo::renderable* obj);

		tbo::panel& add_panel(tbo::style style);
		tbo::panel& add_panel(tbo::style style, tbo::panel* parent);

		void remove_object(tbo::renderable* obj);

		void set_isShown(bool _isShown){isShown = _isShown;}
		bool get_isShown(){return isShown;}

		void set_isMouseIn(bool _isMouseIn){isMouseIn = _isMouseIn;}
		bool get_isMouseIn(){return isMouseIn;}

		tbo::style& get_style(){return body->get_style();}

	};
}

#endif
