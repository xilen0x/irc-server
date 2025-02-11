
#include <sstream>
#include <string>
#include <vector>
#include "Server.hpp"

std::vector<std::string> split_msgAPM(std::string &msg)
{
	std::vector<std::string> res;
	std::istringstream stream(msg);
	std::string s;

	while (stream >> s)
	{
		res.push_back(s);
		s.clear();
	}
	return (res);
}
