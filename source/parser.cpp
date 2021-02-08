#include "parser.hpp"

std::vector<std::string> tbo::parser::split(const std::string& str, char separator)
{
	std::string string = remove_extra(str, separator);
	std::vector<std::string> buffer_vector;
	std::string buffer_string = "";
	for (auto& ch : string)
	{
		if (ch != separator)
		{
			buffer_string += ch;
		}
		else
		{
			buffer_vector.push_back(buffer_string);
			buffer_string = "";
		}
	}
	if (!buffer_string.empty())
	{
		buffer_vector.push_back(buffer_string);
	}

	return buffer_vector;
}

std::string tbo::parser::remove_extra(const std::string& string, char sym)
{
	std::string buffer;
	bool isPrev = false;
	for (auto& ch : string)
	{
		if (ch == sym)
		{
			if (!isPrev)
			{
				buffer += ch;
				isPrev = true;
			}
		}
		else
		{
			isPrev = false;
			buffer += ch;
		}
	}
	return buffer;
}
