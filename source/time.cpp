#include "time.hpp"
#include <stdexcept>

std::stack<std::chrono::system_clock::time_point> tbo::time::range::sessions;

void tbo::time::range::begin()
{
	sessions.push(std::chrono::system_clock::now());
	
}

void tbo::time::range::deltaEnd()
{
	if (sessions.empty()) throw std::runtime_error("Time: stack is empty. You need call begin() first");
	delta = static_cast<std::chrono::duration<double>>(std::chrono::system_clock::now() - sessions.top()).count();
	sessions.pop();
}

double tbo::time::range::end()
{
	if (sessions.empty()) throw std::runtime_error("Time: stack is empty. You need call begin() first");
	double buf = static_cast<std::chrono::duration<double>>(std::chrono::system_clock::now() - sessions.top()).count();
	sessions.pop();
	return buf;
}

double tbo::time::range::delta = 0;
