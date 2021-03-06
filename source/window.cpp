#include "window.hpp"
#include <algorithm>
#include <stdexcept>
#include "signal_manager.hpp"
#include "logger.hpp"
#include "drawing.hpp"
#include "parser.hpp"

tbo::window::window(const char* title, int width, int height, int xpos, int ypos, Uint32 window_flags, Uint32 renderer_flags)
{
	if (SDL_WasInit(SDL_INIT_VIDEO) == 0) 
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0) throw std::runtime_error("Video initializing error");
		tbo::logger::log("window", tbo::logger::MEDIUM_PRIORITY, "SDL2 was initialized");
	}
	if ((wind = SDL_CreateWindow(title, xpos, ypos, width, height, window_flags)) == NULL)
	{
		throw std::runtime_error("Creating window error");
	}
	tbo::logger::log("window", tbo::logger::MEDIUM_PRIORITY, "new window was created with id", SDL_GetWindowID(wind));

	if ((renderer = SDL_CreateRenderer(wind, -1, renderer_flags)) == NULL)
	{
		throw std::runtime_error("Creating renderer error");
	}
	tbo::logger::log("window", tbo::logger::MEDIUM_PRIORITY, "window's renderer was created");

	tbo::style style;
	style.size.width = width | tbo::style::PIXELS;
	style.size.height = height | tbo::style::PIXELS;
	body = new tbo::panel(style);
	tbo::signal_manager::subscribe("window " + std::to_string(SDL_GetWindowID(wind)), this);
}	
tbo::window::window(window&& w)
{
	this->body = w.body;
	this->wind = w.wind;
	this->renderer = w.renderer;
	w.body = nullptr;
	w.wind = nullptr;
	w.renderer = nullptr;
	tbo::logger::log("window", tbo::logger::MEDIUM_PRIORITY, "called move constructor");
}
tbo::window::~window()
{
	delete body;
	if (renderer != nullptr) SDL_DestroyRenderer(renderer);
	if (wind != nullptr) SDL_DestroyWindow(wind);
	tbo::logger::log("window", tbo::logger::MEDIUM_PRIORITY, "called destructor");
}


void tbo::window::update()
{
	const tbo::style& back = body->get_style();
	tbo::drawing::changeColor(renderer, back.background.color.r, back.background.color.g, back.background.color.b, back.background.color.a);
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

void tbo::window::signal_handler(std::string command)
{
		std::vector<std::string> arguments = tbo::parser::split(command, ' ');

		if (arguments[0] == "show")
		{
			isShown = true;
		}
		else if (arguments[0] == "hide")
		{
			isShown = false;
		}
		else if (arguments[0] == "enter")
		{
			isMouseIn = true;
		}
		else if (arguments[0] == "leave")
		{
			isMouseIn = false;
		}
		else if (arguments[0] == "move")
		{
		}
		else if (arguments[0] == "resize")
		{
			body->get_style().size.width = std::stoi(arguments[1]);
			body->get_style().size.height = std::stoi(arguments[2]);
		}
		else
		{
			throw std::runtime_error("Unexpected arguments: " + arguments[0]);
		}
}

