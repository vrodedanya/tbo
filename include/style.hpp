#ifndef STYLE_HPP
#define STYLE_HPP

#include <string>

namespace tbo
{
	class style
	{
	public:
		enum Measure
		{
			PIXELS = 0,
			PERCENT = 256
		};
	private:
	public:
		struct Position
		{
			double x;
			double y;
		} position;
		struct Size
		{
			double width;
			double height;

		} size;

	};
}

#endif
