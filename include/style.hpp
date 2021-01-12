#ifndef STYLE_HPP
#define STYLE_HPP

#include <string>

namespace tbo
{
	class style
	{
	public:
		enum measure
		{
			PERCENT = 1,
			PIXELS = 2
		};
	private:
	public:
		struct position
		{
			measure measure;
			double x;
			double y;
		} position;
		struct size
		{
			measure measure;
			double width;
			double height;

		} size;

	};
}

#endif
