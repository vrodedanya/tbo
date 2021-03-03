#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>
#include <stack>

namespace tbo
{
	class time
	{
	private:
		
	public:
		class range
		{
		private:
			static double delta;
			static std::stack<std::chrono::system_clock::time_point> sessions;
		public:
			static void begin();
			static double end();
			static void deltaEnd();
			static double get_delta(){return delta;}
		};
	};
}


#endif // TIME_HPP
