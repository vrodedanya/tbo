#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include <SDL2/SDL.h>

namespace tbo
{
	class renderable
	{
	public:
		enum Type
		{
			PANEL = 1,
			OTHER = 2
		};

		Type type;
		virtual ~renderable(){}
		virtual void draw(SDL_Renderer* renderer) = 0;
	};
}
#endif
