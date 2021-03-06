#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "window.hpp"
#include <string>
#include <map>
#include <vector>
#include "event_manager.hpp"
#include "logger.hpp"
#include "subscriber.hpp"
#include "signal_manager.hpp"

namespace tbo
{
	class program : public subscriber
	{
	private:
		std::map<std::string, tbo::window*> windows_map; // contains pair 'name' and window. Required to work with a window by name
		std::vector<tbo::window*> windows; // contains all windows. Used for update objects
		tbo::event_manager* emanager; // handle program events
		void signal_handler(std::string command);
	public:
		explicit program() : emanager(new tbo::event_manager())
		{
			tbo::signal_manager::subscribe("program", this);
		}
		~program();

// Deleted methods
		program(const program&) = delete;

		program(program&&) = delete;

// Settings methods
		void add_window(const std::string& name, const char* title, int width = 100, int height = 100, int xpos = SDL_WINDOWPOS_CENTERED, int ypos = SDL_WINDOWPOS_CENTERED, Uint32 window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, Uint32 renderer_flags = SDL_RENDERER_ACCELERATED);

		tbo::window* get_window(const char* window_name);

		tbo::event_manager* get_eventManager(){return emanager;}

// Methods that are called in the loop
		int loop();

		virtual void update(){}; // this method called in loop function and created for implement user requests

	};
}

#endif
