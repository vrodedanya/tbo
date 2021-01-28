#ifndef STYLE_HPP
#define STYLE_HPP

#include <string>
#include "types.hpp"

namespace tbo
{
	struct style
	{
		enum Measure
		{
			PIXELS = 0,
			PERCENT = 2147483648 
		};
		enum BorderStyle
		{
			HIDDEN = 0,
			SOLID = 1
		};

		struct Position
		{
			int x = 0;
			int y = 0;
		} position;
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
		};

		struct Size
		{
			int width  = 0;
			int height = 0;
		} size;
		struct Margin
		{
			int absolute = 0;
			int top      = 0;
			int bot      = 0;
			int right    = 0;
			int left     = 0;
		} margin;
		
		struct Background
		{
			rgba color;
		} background;
		
		struct Border
		{
			BorderStyle style = tbo::style::HIDDEN;
			rgba color;
			unsigned width = 1;
		} border;
		

		static bool isPercent(int value);
		static double get_fraction(int percent);
	};
	int operator&(int num, const style::Measure& mes);
	int operator|(int num, const style::Measure& mes);
}

#endif
