#ifndef SIGNAL_MANAGER
#define SIGNAL_MANAGER

#include <vector>
#include <string>

#ifdef DEBUG
	#include <iostream>
#endif

namespace tbo
{
	class signal
	{
	private:
	public:
		signal()
		{
		}
		signal(const std::string& _recipient, const std::string& _id, const std::string& _command) : recipient(_recipient), id(_id), command(_command)
		{
		}
		std::string recipient;
		std::string id;
		std::string command;


		friend bool operator !=(const tbo::signal&, const tbo::signal&);
	};
	bool operator !=(const tbo::signal& sig1, const tbo::signal& sig2);
		

	class signal_manager
	{
	private:
		static std::vector<tbo::signal> signals;
	public:
		static tbo::signal get_signal(const std::string& recipient);
		static void add_signal(const tbo::signal& sig);
	};
}

#endif
