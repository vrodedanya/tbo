#include "../include/program.hpp"
#include "../include/panel.hpp"

int main()
{
	SDL2S::program prog;

	SDL2S::panel panel(100,500, 0, 0);
	SDL2S::panel panel2(100, 500, 0, 150);

	prog.add_window("main", "title", 500, 500);
	prog.add_window("sub_window", "question", 200, 50, 0, 0, SDL_WINDOW_SHOWN);

	prog.get_window("main")->add_object(&panel);
	prog.get_window("main")->add_object(&panel2);

	prog.loop();

	return 0;
}
