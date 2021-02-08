#include "time.hpp"
#include <stdexcept>

std::stack<std::chrono::system_clock::time_point> tbo::time::timerange::sessions;

void tbo::time::timerange::begin()
{
	sessions.push(std::chrono::system_clock::now());
	
}

void tbo::time::timerange::end()
{
	if (sessions.empty()) throw std::runtime_error("Time: stack is empty. You need call begin() first");
	delta = static_cast<std::chrono::duration<double>>(std::chrono::system_clock::now() - sessions.top()).count();
	sessions.pop();
}

double tbo::time::timerange::delta = 0;
