#include "../include/program.hpp"
#include "../include/panel.hpp"
#include "../include/style.hpp"

int main()
{
	tbo::program prog;
	tbo::logger::set_priority(tbo::logger::MEDIUM_PRIORITY);

	tbo::style style1;
	style1.size.width = 30 | tbo::style::PERCENT;
	style1.size.height = 20 | tbo::style::PERCENT;
	style1.color = tbo::style::rgba(255, 255, 255, 0);

	tbo::panel panel1(tbo::renderable::PANEL, style1);
	panel1.get_style().position.x = 5 | tbo::style::PERCENT;
	panel1.get_style().position.y = 5 | tbo::style::PERCENT;
	tbo::panel panel2(tbo::renderable::PANEL, style1);
	panel2.get_style().position.x = 5 | tbo::style::PERCENT;
	panel2.get_style().position.y = 30 | tbo::style::PERCENT;


	prog.add_window("main", "title", 500, 500);

	prog.get_window("main")->add_object(&panel1);
	prog.get_window("main")->add_object(&panel2);

	int code = prog.loop();

	return code;
}
