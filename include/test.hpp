#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include "logger.hpp"

namespace tbo
{
	class test
	{
	private:
		static inline unsigned tests_count = 0;
	public:
		template<typename RETURN_TYPE, typename... FUNC_ARGS_B, typename... FUNC_ARGS>
		static void assert(RETURN_TYPE expectation, RETURN_TYPE(*func)(FUNC_ARGS_B...), FUNC_ARGS... args)
		{
			RETURN_TYPE buffer = func(args...);
			if (buffer != expectation)
			{
				tbo::logger::log("test", tbo::logger::HIGH_PRIORITY, "test", tests_count, "is failed!", "Got", buffer, "instead", expectation);
				std::terminate();
			}
			else
			{
				tbo::logger::log("test", tbo::logger::HIGH_PRIORITY, "test", tests_count++, "is passed!");
			}
		}
	};
}

#endif
