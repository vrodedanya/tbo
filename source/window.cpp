#include "../include/window.hpp"
#include <algorithm>
#include <stdexcept>
#include "../include/signal_manager.hpp"
#include "../include/logger.hpp"

void tbo::window::update()
{
	if (isShown)
	{
		SDL_SetRenderDrawColor(renderer, body->get_style().color.r, body->get_style().color.g, body->get_style().color.b, body->get_style().color.a);
		SDL_RenderClear(renderer);

		for (auto& obj : objects)
		{
			obj->draw(renderer);
		}

		SDL_RenderPresent(renderer);
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

void tbo::window::remove_object(tbo::renderable * obj)
{
	auto it = std::find(objects.begin(), objects.end(), obj);
	if (it == objects.end()) throw std::runtime_error("Object doesn't exist");
	objects.erase(it);
	tbo::logger::log("window", tbo::logger::MEDIUM_PRIORITY, "object was removed from render");
}
