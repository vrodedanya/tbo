#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>

namespace tbo
{
	class time
	{
	private:
		
	public:
		class timerange
		{
		private:
			static double delta;
			static std::chrono::system_clock::time_point beg;
		public:
			static void begin();
			static void end();
			static double get_delta(){return delta;}
		};
	};
}


#endif // TIME_HPP
