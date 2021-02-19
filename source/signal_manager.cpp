#include "signal_manager.hpp"
#include <algorithm>

std::mutex tbo::signal_manager::locker;
std::vector<tbo::signal> tbo::signal_manager::signals;
std::map<std::string, std::vector<tbo::subscriber*>> tbo::signal_manager::subscriptions;

void tbo::signal_manager::subscribe(std::string subscription, tbo::subscriber* subscriber)
{
	subscriptions[subscription].emplace_back(subscriber);
}
void tbo::signal_manager::add_signal(const tbo::signal& sig)
{
	auto it = subscriptions.find(sig.recipient);
	if (it == subscriptions.end())
	{
		throw std::runtime_error(sig.recipient + " doesn't exist");
	}
	for (auto& subscriber : it->second)
	{
		subscriber->signal_handler(sig.command);
	}
}


