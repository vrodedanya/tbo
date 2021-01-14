#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include <string>

namespace tbo
{
	class parser
	{
	public:
		parser() = delete;
		static std::vector<std::string> split(const std::string& str, char separator);
		static std::string remove_extra(const std::string& string, char sym);
	};
}

#endif
