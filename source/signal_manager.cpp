#include "../include/signal_manager.hpp"
#include <algorithm>

std::vector<SDL2S::signal> SDL2S::signal_manager::signals;

SDL2S::signal SDL2S::signal_manager::get_signal(const std::string& recipient)
{
	auto it = std::find_if(signals.begin(), signals.end(), [recipient](const SDL2S::signal& sig){return recipient == sig.recipient;});
	if (it != signals.end())
	{
		SDL2S::signal buf{*it};
		signals.erase(it);
		return buf;
	}
	return SDL2S::signal("","","");
}

void SDL2S::signal_manager::add_signal(const SDL2S::signal& sig)
{
	signals.push_back(sig);
}

bool SDL2S::operator !=(const SDL2S::signal& sig1, const SDL2S::signal& sig2)
{
	if (sig1.command != sig2.command || sig1.id != sig2.id || sig1.recipient != sig2.recipient) return true;
	else return false;
}
