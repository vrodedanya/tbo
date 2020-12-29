#include "../include/program.hpp"

int main()
{
	SDL2S::program prog;

	prog.add_window("main", "title", 500, 500);

	prog.get_window("sub")->update();

	prog.loop();

	return 0;
}
