#ifndef SIGNAL_MANAGER
#define SIGNAL_MANAGER

#include <vector>
#include <string>

#ifdef DEBUG
	#include <iostream>
#endif

namespace SDL2S
{
	class signal
	{
	private:
	public:
		signal(const std::string& _recipient, const std::string& _id, const std::string& _command) : recipient(_recipient), id(_id), command(_command)
		{
		}
		std::string recipient;
		std::string id;
		std::string command;
	};

	class signal_manager
	{
	private:
		static std::vector<SDL2S::signal> signals;
	public:
		static SDL2S::signal get_signal(const std::string& recipient);
		static void add_signal(const SDL2S::signal& sig);
	};
}

#endif
