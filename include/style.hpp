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
			PERCENT = 2147483648 
		};
	private:
	public:
		struct Position
		{
			int x;
			int y;
		} position;
		struct Size
		{
			int width;
			int height;

		} size;

	};
	int operator&(int num, const style::Measure& mes);
	int operator|(int num, const style::Measure& mes);
}

#endif
