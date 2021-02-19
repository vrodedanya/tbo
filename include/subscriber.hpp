#ifndef SUBSCRIBET_HPP
#define SUBSCRIBET_HPP

#include "signal.hpp"

namespace tbo
{
	class subscriber
	{
	private:

	public:
		virtual void signal_handler(tbo::signal){}
	};
}

#endif
