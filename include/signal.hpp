#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <string>
#include <iostream>

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
}

#endif
