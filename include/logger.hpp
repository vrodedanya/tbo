#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>

namespace tbo
{
	
	class logger
	{
	public:
		enum Priority
		{
			LOW_PRIORITY = 0,
			MEDIUM_PRIORITY = 1,
			HIGH_PRIORITY = 2
		};

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
		static tbo::logger::Priority current_priority;
	public:
		
		logger() = delete;

		static bool TurnedOn;

		static void set_priority(Priority prior){current_priority = prior;}

		static tbo::logger::Priority get_priority(){return current_priority;}

		template<typename... AArgs>
		static void log(const std::string& sender, Priority prior, AArgs... MArgs)
		{
			if (TurnedOn && prior >= current_priority)
			{
				std::cerr << "[Logger]: from " << sender << ": ";
				rec_log(MArgs...);
				std::cerr << std::endl;
			}
		}
	};
}

#endif
