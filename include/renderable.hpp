#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include "drawing.hpp"

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
		virtual void draw(tbo::renderer* renderer) = 0;
	};
}
#endif
