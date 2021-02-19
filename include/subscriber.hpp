#ifndef SUBSCRIBET_HPP
#define SUBSCRIBET_HPP

#include <string>
#include "signal.hpp"

namespace tbo
{
	class subscriber
	{
	private:

	public:
		virtual ~subscriber(){}
		virtual void signal_handler(std::string){}
	};
}

#endif
