#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include <SDL2/SDL.h>

namespace SDL2S
{
	class renderable
	{
	private:
	public:
		virtual void draw(SDL_Renderer* renderer) = 0;
	};
}
#endif
