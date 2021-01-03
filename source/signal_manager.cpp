#include "../include/signal_manager.hpp"
#include <algorithm>

std::vector<tbo::signal> tbo::signal_manager::signals;

tbo::signal tbo::signal_manager::get_signal(const std::string& recipient)
{
	auto it = std::find_if(signals.begin(), signals.end(), [recipient](const tbo::signal& sig){return recipient == sig.recipient;});
	if (it != signals.end())
	{
		tbo::signal buf{*it};
		signals.erase(it);
		return buf;
	}
	return tbo::signal("","","");
}

void tbo::signal_manager::add_signal(const tbo::signal& sig)
{
	signals.push_back(sig);
}

bool tbo::operator == (const tbo::signal& sig1, const tbo::signal& sig2)
{
	if (sig1.command == sig2.command && sig1.id == sig2.id && sig1.recipient == sig2.recipient) return true;
	else return false;
}

bool tbo::operator != (const tbo::signal& sig1, const tbo::signal& sig2)
{
	if (!(sig1 == sig2)) return true;
	else return false;
}

std::ostream& tbo::operator << (std::ostream& os, const tbo::signal& sig)
{
	os << "Recipient: " << sig.recipient << " | " << "ID: " << sig.id <<  " | " << "Command: " << sig.command;
	return os;
}
