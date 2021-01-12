#include "../include/program.hpp"
#include "../include/panel.hpp"
#include "../include/style.hpp"

int main()
{
	tbo::program prog;
	tbo::logger::set_priority(tbo::logger::MEDIUM_PRIORITY);

	tbo::style style1;
	style1.position.measure = tbo::style::PERCENT;
	style1.position.x = 50;
	style1.position.y = 50;
	style1.size.measure = tbo::style::PIXELS;
	style1.size.width = 40;
	style1.size.height = 40;

	tbo::panel panel(100,500, 0, 0);
	tbo::panel panel2(100, 500, 0, 150);

	prog.add_window("main", "title", 500, 500);
	prog.add_window("sub_window", "question", 200, 50, 0, 0, SDL_WINDOW_SHOWN);

	prog.get_window("main")->add_object(&panel);
	prog.get_window("main")->add_object(&panel2);

	int code = prog.loop();

	return code;
}
