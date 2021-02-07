#include "../include/time.hpp"

void tbo::time::timerange::begin()
{
	beg = std::chrono::system_clock::now();
}

void tbo::time::timerange::end()
{
	delta = static_cast<std::chrono::duration<double>>(std::chrono::system_clock::now() - beg).count();
}

double tbo::time::timerange::delta = 0;
std::chrono::system_clock::time_point tbo::time::timerange::beg = std::chrono::system_clock::now();
