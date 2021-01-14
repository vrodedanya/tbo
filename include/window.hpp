#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include <vector>
#include "../include/renderable.hpp"
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

		int width;
		int height;
		int xpos;
		int ypos;
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

			SDL_GetWindowPosition(wind, &xpos, &ypos);
			SDL_GetWindowSize(wind, &width, &height);

			if ((renderer = SDL_CreateRenderer(wind, -1, renderer_flags)) == NULL)
			{
				throw std::runtime_error("Creating renderer error");
			}
			tbo::logger::log("window", tbo::logger::MEDIUM_PRIORITY, "window's renderer was created");
		}	
		window(const window& wind) = delete;
		window(window&& w)
		{
			this->wind = w.wind;
			this->renderer = w.renderer;
			w.wind = nullptr;
			w.renderer = nullptr;
			tbo::logger::log("window", tbo::logger::MEDIUM_PRIORITY, "called move constructor");
		}
		~window()
		{
			if (renderer != nullptr) SDL_DestroyRenderer(renderer);
			if (wind != nullptr) SDL_DestroyWindow(wind);
			tbo::logger::log("window", tbo::logger::MEDIUM_PRIORITY, "called destructor");
		}
		SDL_Window* get_window(){return wind;}
		SDL_Renderer* get_renderer(){return renderer;}

		void update();

		std::vector<tbo::renderable*>& get_objects(){return objects;}

		void add_object(tbo::renderable* obj);

		void remove_object(tbo::renderable * obj);

		void set_isShown(bool _isShown){isShown = _isShown;}
		bool get_isShown(){return isShown;}

		void set_isMouseIn(bool _isMouseIn){isMouseIn = _isMouseIn;}
		bool get_isMouseIn(){return isMouseIn;}

		void set_width(int width){this->width = width;}
		int get_width(){return width;}
		void set_height(int height){this->height = height;}
		int get_height(){return height;}

		void set_xpos(int xpos){this->xpos = xpos;}
		int get_xpos(){return xpos;}
		void set_ypos(int ypos){this->ypos = ypos;}
		int get_ypos(){return ypos;}
	};
}

#endif
