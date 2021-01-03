#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include <vector>
#include "../include/renderable.hpp"
#ifdef DEBUG
	#include <iostream>
#endif

namespace tbo
{
	class window
	{
	private:
		SDL_Window* wind;
		SDL_Renderer* renderer;
		std::vector<tbo::renderable*> objects;
	public:
		explicit window(const char* title, int width = 100, int height = 100, int xpos = SDL_WINDOWPOS_CENTERED, int ypos = SDL_WINDOWPOS_CENTERED, Uint32 window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, Uint32 renderer_flags = SDL_RENDERER_ACCELERATED)
		{
			if (SDL_WasInit(SDL_INIT_VIDEO) == 0) 
			{
				if (SDL_Init(SDL_INIT_VIDEO) != 0) throw std::runtime_error("Video initializing error");
			}
			if ((wind = SDL_CreateWindow(title, xpos, ypos, width, height, window_flags)) == NULL)
			{
				throw std::runtime_error("Creating window error");
			}
			if ((renderer = SDL_CreateRenderer(wind, -1, renderer_flags)) == NULL)
			{
				throw std::runtime_error("Creating renderer error");
			}
		}	
		window(const window& wind) = delete;
		window(window&& w)
		{
			this->wind = w.wind;
			this->renderer = w.renderer;
			w.wind = nullptr;
			w.renderer = nullptr;
#ifdef DEBUG
			std::cerr << "Called window move constructor" << std::endl;
#endif
		}
		~window()
		{
			if (renderer != nullptr) SDL_DestroyRenderer(renderer);
			if (wind != nullptr) SDL_DestroyWindow(wind);
			if (wind == NULL) std::cerr << "It's okey..." << std::endl;
#ifdef DEBUG
			std::cerr << "Called window destructor" << std::endl;
#endif
		}
		SDL_Window* get_window(){return wind;}
		SDL_Renderer* get_renderer(){return renderer;}

		void update();

		std::vector<tbo::renderable*>& get_objects(){return objects;}

		void add_object(tbo::renderable* obj);

		void remove_object(tbo::renderable * obj);
	};
}

#endif
