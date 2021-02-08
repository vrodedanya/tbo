#ifndef SIGNAL_MANAGER
#define SIGNAL_MANAGER

#include <vector>
#include <string>
#include <mutex>

namespace tbo
{
	class signal
	{
	private:
	public:
		signal()
		{
		}
		signal(const std::string& _recipient, const std::string& _command) : recipient(_recipient), command(_command)
		{
		}
		std::string recipient;
		std::string command;

		friend bool operator !=(const tbo::signal&, const tbo::signal&);
		friend bool operator ==(const tbo::signal&, const tbo::signal&);
		friend std::ostream& operator <<(std::ostream& os, const tbo::signal& sig);
	};
	bool operator ==(const tbo::signal& sig1, const tbo::signal& sig2);
	bool operator !=(const tbo::signal& sig1, const tbo::signal& sig2);
	std::ostream& operator <<(std::ostream& os, const tbo::signal& sig);
		
	class signal_manager
	{
	private:
		static std::vector<tbo::signal> signals;
		static std::mutex locker;
	public:
		signal_manager() = delete;
		signal_manager(const signal_manager&) = delete;
		signal_manager(signal_manager&&) = delete;

		static tbo::signal get_signal(const std::string& recipient);
		static void add_signal(const tbo::signal& sig);
	};
}

#endif
