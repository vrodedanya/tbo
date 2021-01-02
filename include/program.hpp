#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "window.hpp"
#include <string>
#include <map>
#include <vector>
#include "event_manager.hpp"

namespace SDL2S
{
	class program
	{
	private:
		std::map<std::string, window*> windows_map;
		std::vector<window*> windows;
		SDL2S::event_manager* emanager;
	public:
		explicit program() : emanager(new SDL2S::event_manager()){}
		program(const program& prog) = delete;
		~program()
		{
			delete emanager;
			for (auto& window : windows)
			{
				delete window;
			}
		}
		void add_window(const std::string& name, const char* title, int width = 100, int height = 100, int xpos = SDL_WINDOWPOS_CENTERED, int ypos = SDL_WINDOWPOS_CENTERED, Uint32 window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, Uint32 renderer_flags = SDL_RENDERER_ACCELERATED);

		SDL2S::window* get_window(const char* window_name);

		SDL2S::event_manager* get_eventManager(){return emanager;}

		void loop();

	};
}

#endif
