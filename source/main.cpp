#include "../include/program.hpp"
#include "../include/panel.hpp"
#include "../include/style.hpp"

int main()
{
	tbo::program prog;
	tbo::logger::set_priority(tbo::logger::MEDIUM_PRIORITY);

	tbo::style style1;
	style1.position.x = 5 | tbo::style::PERCENT;
	style1.position.y = 10 | tbo::style::PIXELS;
	style1.size.width = 30 | tbo::style::PERCENT;
	style1.size.height = 20 | tbo::style::PERCENT;
	style1.color = tbo::style::rgba(255, 255, 255, 0);

	tbo::panel panel(tbo::renderable::PANEL, style1, 500, 500);

	prog.add_window("main", "title", 500, 500);

	prog.get_window("main")->add_object(&panel);

	int code = prog.loop();

	return code;
}
