#include "../include/program.hpp"
#include "../include/panel.hpp"
#include "../include/style.hpp"
#include "../include/test.hpp"
#include <functional>

void test()
{
	tbo::logger::log("test", tbo::logger::HIGH_PRIORITY, "start testing style function isPercent");
	tbo::test::assert(true, tbo::style::isPercent, 5 | tbo::style::PERCENT);
	tbo::test::assert(true, tbo::style::isPercent, 50 | tbo::style::PERCENT);
	tbo::test::assert(true, tbo::style::isPercent, 332 | tbo::style::PERCENT);
	tbo::test::assert(true, tbo::style::isPercent, 5020 | tbo::style::PERCENT);
	tbo::test::assert(true, tbo::style::isPercent, 50323 | tbo::style::PERCENT);
	tbo::test::assert(true, tbo::style::isPercent, 153030 | tbo::style::PERCENT);
	tbo::test::assert(false, tbo::style::isPercent, 5);
	tbo::test::assert(false, tbo::style::isPercent, 50);
	tbo::test::assert(false, tbo::style::isPercent, 332);
	tbo::test::assert(false, tbo::style::isPercent, 5020);
	tbo::test::assert(false, tbo::style::isPercent, 50323);
	tbo::test::assert(false, tbo::style::isPercent, 153030);
	tbo::logger::log("test", tbo::logger::HIGH_PRIORITY, "start testing style function get_fraction");
	tbo::test::assert(0.1, tbo::style::get_fraction, 10 | tbo::style::PERCENT);
	tbo::test::assert(0.2, tbo::style::get_fraction, 20 | tbo::style::PERCENT);
	tbo::test::assert(0.9, tbo::style::get_fraction, 90 | tbo::style::PERCENT);
	tbo::test::assert(0.01, tbo::style::get_fraction, 1 | tbo::style::PERCENT);
	tbo::test::assert(0.04, tbo::style::get_fraction, 4 | tbo::style::PERCENT);
	tbo::test::assert(0.09, tbo::style::get_fraction, 9 | tbo::style::PERCENT);
	tbo::test::assert(0.03, tbo::style::get_fraction, 3 | tbo::style::PERCENT);

	tbo::style back;
	back.position.x = 0 | tbo::style::PIXELS;
	back.position.y = 0 | tbo::style::PIXELS;
	back.size.width = 200 | tbo::style::PIXELS;
	back.size.height = 200 | tbo::style::PIXELS;
	tbo::style style;
	style.size.width  = 50 | tbo::style::PERCENT;
	style.size.height = 60 | tbo::style::PERCENT;
	style.position.x = 50 | tbo::style::PERCENT;
	style.position.y = 60 | tbo::style::PERCENT;
	tbo::style sub;
	sub.size.width = 50  | tbo::style::PERCENT;
	sub.size.width = 70  | tbo::style::PERCENT;
	sub.position.x = 20 | tbo::style::PIXELS;
	sub.position.y = 40;

	tbo::panel body(back);
	tbo::panel panel(style);
	tbo::panel s(sub);
	panel.set_parent(&body);
	s.set_parent(&panel);

	tbo::logger::log("test", tbo::logger::HIGH_PRIORITY, "start testing panel function get_pixel...");
	tbo::test::assert(100, &tbo::panel::get_pixel_width, &panel);
	tbo::test::assert(120, &tbo::panel::get_pixel_height, &panel);
	panel.get_style().size.width = 100 | tbo::style::PIXELS;
	tbo::test::assert(100, &tbo::panel::get_pixel_width, &panel);
	tbo::test::assert(100, &tbo::panel::get_pixel_xpos, &panel);
	panel.get_style().position.x = 150 | tbo::style::PIXELS;
	tbo::test::assert(150, &tbo::panel::get_pixel_xpos, &panel);
	tbo::test::assert(120, &tbo::panel::get_pixel_ypos, &panel);
	tbo::test::assert(170, &tbo::panel::get_pixel_xpos, &s);
}

int main()
{
	test();

	tbo::program prog;
	tbo::logger::set_priority(tbo::logger::MEDIUM_PRIORITY);

	tbo::style main;
	main.size.width = 90 | tbo::style::PERCENT;
	main.size.height = 90 | tbo::style::PERCENT;
	main.position.x = 5 | tbo::style::PERCENT;
	main.position.y = 5 | tbo::style::PERCENT;
	main.margin.left = 5 | tbo::style::PERCENT;
	main.margin.top = 20 | tbo::style::PERCENT;
	main.color.r = 255;
	main.color.g = 255;
	main.color.b = 255;

	tbo::style common;
	common.size.width = 90 | tbo::style::PERCENT;
	common.size.height = 10 | tbo::style::PERCENT;
	common.position.x = 5 | tbo::style::PERCENT;
	common.position.y = 5 | tbo::style::PERCENT;
	common.color.r = 210;
	common.color.g = 210;
	common.color.b = 210;

	prog.add_window("main", "title", 500, 500);

	prog.get_window("main")->get_style().color.r = 255;
	prog.get_window("main")->get_style().color.g = 0;
	prog.get_window("main")->get_style().color.b = 255;
	prog.get_window("main")->get_style().color.a = 255;

	tbo::panel& panel1 = prog.get_window("main")->add_panel(main);
	tbo::panel& panel2 = prog.get_window("main")->add_panel(common, &panel1);
	tbo::panel& panel3 = prog.get_window("main")->add_panel(common, &panel1);
	tbo::panel& panel4 = prog.get_window("main")->add_panel(common, &panel1);
	tbo::panel& panel5 = prog.get_window("main")->add_panel(common, &panel1);

	panel3.get_style().position.y = 20 | tbo::style::PERCENT;
	panel4.get_style().position.y = 35 | tbo::style::PERCENT;
	panel5.get_style().position.y = 50 | tbo::style::PERCENT;
	
	int code = prog.loop();

	return code;
}
