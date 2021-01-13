#ifndef STYLE_HPP
#define STYLE_HPP

#include <string>

namespace tbo
{
	using byte = unsigned char;
	class style
	{
	public:
		enum Measure
		{
			PIXELS = 0,
			PERCENT = 2147483648 
		};
		class color
		{
		public:
			explicit color(tbo::byte r, tbo::byte g, tbo::byte b, tbo::byte a)
			{
				this->r = r;
				this->g = g;
				this->b = b;
				this->a = a;
			}
			color() : r(0), g(0), b(0), a(0)
			{
			}
			color& operator = (const color& color) = default;
			tbo::byte r;
			tbo::byte g;
			tbo::byte b;
			tbo::byte a;
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
		tbo::style::color color;
	};
	int operator&(int num, const style::Measure& mes);
	int operator|(int num, const style::Measure& mes);
}

#endif
