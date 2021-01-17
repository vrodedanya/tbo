#include "../include/style.hpp"

int tbo::operator&(int num, const style::Measure& mes)
{
	int n = mes;
	return n & num;
}

int tbo::operator|(int num, const style::Measure& mes)
{
	int n = mes;
	return n | num;
}

bool tbo::style::isPercent(int value)
{
	if ((value & tbo::style::PERCENT) == static_cast<int>(tbo::style::PERCENT)) return true;
	else return false;
}
double tbo::style::get_fraction(int percent)
{
	return (static_cast<double>(percent & (tbo::style::PERCENT - 1)) / 100);
}
