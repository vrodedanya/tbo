#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "window.hpp"
#include <string>
#include <map>
#include <vector>

namespace SDL2S
{
	class program
	{
	private:
		std::map<std::string, window*> windows_map;
		std::vector<window*> windows;
	public:
		explicit program(){}
		program(const program& prog) = delete;
		~program()
		{
			for (auto& window : windows)
			{
				delete window;
			}
		}
		void add_window(const std::string& name, const char* title, int width = 100, int height = 100, int xpos = SDL_WINDOWPOS_CENTERED, int ypos = SDL_WINDOWPOS_CENTERED, Uint32 window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, Uint32 renderer_flags = SDL_RENDERER_ACCELERATED);
		
		void loop();

	};
}

#endif
