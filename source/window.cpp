#include "../include/window.hpp"
#include <algorithm>
#include <stdexcept>
#include "../include/signal_manager.hpp"
#include "../include/logger.hpp"
#include "../include/drawing.hpp"

void tbo::window::update()
{
	tbo::drawing::changeColor(renderer, body->get_style().background.color.r, body->get_style().background.color.g, body->get_style().background.color.b, body->get_style().background.color.a);
	tbo::drawing::fillScreen(renderer);
	if (isShown)
	{
		for (auto& obj : objects)
		{
			obj->draw(renderer);
		}

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
