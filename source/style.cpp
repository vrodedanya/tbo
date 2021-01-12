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
