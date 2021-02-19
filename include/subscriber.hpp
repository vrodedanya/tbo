#ifndef SUBSCRIBET_HPP
#define SUBSCRIBET_HPP

#include "signal.hpp"

namespace tbo
{
	class subscriber
	{
	private:

	public:
		virtual ~subscriber(){}
		virtual void signal_handler(tbo::signal){}
	};
}

#endif
