#ifndef STYLE_HPP
#define STYLE_HPP

#include <string>

namespace tbo
{
	using byte = unsigned char;
	struct style
	{
		enum Measure
		{
			PIXELS = 0,
			PERCENT = 2147483648 
		};

		struct Position
		{
			int x = 0;
			int y = 0;
		} position;
		struct Size
		{
			int width  = 0;
			int height = 0;
		} size;
		struct rgba
		{
		public:
			explicit rgba(tbo::byte r, tbo::byte g, tbo::byte b, tbo::byte a)
			{
				this->r = r;
				this->g = g;
				this->b = b;
				this->a = a;
			}
			rgba() : r(0), g(0), b(0), a(0)
			{
			}
			rgba& operator = (const rgba& color) = default;
			tbo::byte r;
			tbo::byte g;
			tbo::byte b;
			tbo::byte a;
		} color;
		static bool isPercent(int value);
		static double get_fraction(int percent);
		struct Margin
		{
			int absolute = 0;
			int top      = 0;
			int bot      = 0;
			int right    = 0;
			int left     = 0;
		} margin;
	};
	int operator&(int num, const style::Measure& mes);
	int operator|(int num, const style::Measure& mes);
}

#endif
