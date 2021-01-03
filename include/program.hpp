#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "window.hpp"
#include <string>
#include <map>
#include <vector>
#include "event_manager.hpp"

namespace tbo
{
	class program
	{
	private:
		std::map<std::string, tbo::window*> windows_map;
		std::vector<tbo::window*> windows;
		tbo::event_manager* emanager;
	public:
		explicit program() : emanager(new tbo::event_manager()){}
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

		tbo::window* get_window(const char* window_name);

		tbo::event_manager* get_eventManager(){return emanager;}

		void loop();

		void signal_handler();

	};
}

#endif
