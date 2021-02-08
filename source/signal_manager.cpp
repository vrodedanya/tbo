#include "signal_manager.hpp"
#include <algorithm>
#include <mutex>
#include <ostream>

std::mutex tbo::signal_manager::locker;
std::vector<tbo::signal> tbo::signal_manager::signals;

tbo::signal tbo::signal_manager::get_signal(const std::string& recipient)
{
	std::lock_guard<std::mutex> lock(locker);
	auto it = std::find_if(signals.begin(), signals.end(), [recipient](const tbo::signal& sig){return recipient == sig.recipient;});
	if (it != signals.end())
	{
		tbo::signal buf{*it};
		signals.erase(it);
		return buf;
	}
	return tbo::signal("","");
}

void tbo::signal_manager::add_signal(const tbo::signal& sig)
{
	std::lock_guard<std::mutex> lock(locker);
	signals.push_back(sig);
}

bool tbo::operator == (const tbo::signal& sig1, const tbo::signal& sig2)
{
	if (sig1.command == sig2.command && sig1.recipient == sig2.recipient) return true;
	else return false;
}

bool tbo::operator != (const tbo::signal& sig1, const tbo::signal& sig2)
{
	if (!(sig1 == sig2)) return true;
	else return false;
}

std::ostream& tbo::operator << (std::ostream& os, const tbo::signal& sig)
{
	os << "Recipient: " << sig.recipient << " | " << "Command: " << sig.command;
	return os;
}
