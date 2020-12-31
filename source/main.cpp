#include "../include/program.hpp"
#include "../include/panel.hpp"

int main()
{
	SDL2S::program prog;

	SDL2S::panel panel(100,500, 0, 0);

	prog.add_window("main", "title", 500, 500);
	prog.get_window("main")->add_object(&panel);

	prog.loop();

	return 0;
}
