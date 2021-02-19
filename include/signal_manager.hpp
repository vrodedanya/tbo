#ifndef SIGNAL_MANAGER
#define SIGNAL_MANAGER

#include <vector>
#include <map>
#include <mutex>
#include "signal.hpp"
#include "subscriber.hpp"

namespace tbo
{
	class signal_manager
	{
	private:
		static std::map<std::string, std::vector<tbo::subscriber*>> subscriptions; // Storage subscription and subscribers
		static std::vector<tbo::signal> signals;
		static std::mutex locker;
	public:
		signal_manager() = delete;
		signal_manager(const signal_manager&) = delete;
		signal_manager(signal_manager&&) = delete;

		static void subscribe(std::string subscription, tbo::subscriber*);
		static void add_signal(const tbo::signal& sig); // calls subscribers signal handler functions
	};
}

#endif
