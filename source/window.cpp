#include "../include/window.hpp"
#include <algorithm>
#include <stdexcept>
#include "../include/signal_manager.hpp"
#include "../include/logger.hpp"
#include "../include/drawing.hpp"
#include "../include/parser.hpp"

void tbo::window::update()
{
	signal_handler();
	tbo::drawing::changeColor(renderer, body->get_style().background.color.r, body->get_style().background.color.g, body->get_style().background.color.b, body->get_style().background.color.a);
	tbo::drawing::fillScreen(renderer);
	if (isShown)
	{
		for (auto& obj : objects)
		{
			obj->draw(renderer);
		}

		tbo::drawing::changeColor(renderer, 255, 0, 0, 0);
		tbo::drawing::circle(renderer, cursor.x, cursor.y, 25);

		tbo::drawing::updateRenderer(renderer);
	}
}

void tbo::window::add_object(tbo::renderable* obj)
{
	if (std::find(objects.begin(), objects.end(), obj) != objects.end())
	{
		throw std::runtime_error("Object is already exist");
	}
	if (obj->type == tbo::renderable::PANEL)
	{
		if(static_cast<tbo::panel*>(obj)->get_parent() == nullptr)
		{	
			static_cast<tbo::panel*>(obj)->set_parent(body);
		}
	}
	objects.emplace_back(obj);
	tbo::logger::log("window", tbo::logger::MEDIUM_PRIORITY, "new object was added to render");
}

tbo::panel& tbo::window::add_panel(tbo::style style)
{
	tbo::panel* buf = new tbo::panel(style);
	buf->set_parent(body);
	objects.emplace_back(buf);
	tbo::logger::log("window", tbo::logger::MEDIUM_PRIORITY, "new panel was added to render");
	return *buf;
}

tbo::panel& tbo::window::add_panel(tbo::style style, tbo::panel* parent)
{
	tbo::panel* buf = new tbo::panel(style);
	buf->set_parent(parent);
	objects.emplace_back(buf);
	tbo::logger::log("window", tbo::logger::MEDIUM_PRIORITY, "new panel was added to render");
	return *buf;
}

void tbo::window::remove_object(tbo::renderable * obj)
{
	auto it = std::find(objects.begin(), objects.end(), obj);
	if (it == objects.end()) throw std::runtime_error("Object doesn't exist");
	objects.erase(it);
	tbo::logger::log("window", tbo::logger::MEDIUM_PRIORITY, "object was removed from render");
}

void tbo::window::signal_handler()
{
	tbo::signal sig;
	std::string receiver = "window " + std::to_string(SDL_GetWindowID(wind));
	while((sig = tbo::signal_manager::get_signal(receiver)) != tbo::signal("",""))
	{
		tbo::logger::log("window", tbo::logger::LOW_PRIORITY, "receiving signal (", sig, ")");		

		std::vector<std::string> command = tbo::parser::split(sig.command, ' ');

		if (command[0] == "show")
		{
			isShown = true;
		}
		else if (command[0] == "hide")
		{
			isShown = false;
		}
		else if (command[0] == "enter")
		{
			isMouseIn = true;
		}
		else if (command[0] == "leave")
		{
			isMouseIn = false;
		}
		else if (command[0] == "move")
		{
		}
		else if (command[0] == "resize")
		{
			body->get_style().size.width = std::stoi(command[1]);
			body->get_style().size.height = std::stoi(command[2]);
		}
		else if (command[0] == "mouse")
		{
			cursor.x = std::stoi(command[1]);
			cursor.y = std::stoi(command[2]);
		}
		else
		{
			throw std::runtime_error("Unexpected command: " + command[0]);
		}
	}
}

