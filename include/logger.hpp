#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>

namespace tbo
{
	class logger
	{
	private:
		template<typename T>
		static void rec_log(T value)
		{
			std::cerr << value;
		}
		template<typename T, typename... AArgs>
		static void rec_log(T first, AArgs... MArgs)
		{
			std::cerr << first << " ";
			rec_log(MArgs...);
		}
	public:
		logger() = delete;

		static bool TurnedOn;

		template<typename... AArgs>
		static void log(const std::string& sender, AArgs... MArgs)
		{
			if (TurnedOn)
			{
				std::cerr << "[Logger]: from " << sender << ": ";
				rec_log(MArgs...);
				std::cerr << std::endl;
			}
		}
	};
}

#endif
