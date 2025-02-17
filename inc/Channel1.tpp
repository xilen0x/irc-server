#ifndef CHANNEL1_TPP
# define CHANNEL1_TPP

# include "Channel.hpp"


template <typename T>
bool	Channel::_addInMap(std::map<std::string, T*> &targetMap, std::string &nick, T *t)
{
	if (!t)
		return (false);
	if (targetMap.find(nick) != targetMap.end())
		return (false);
	targetMap[nick] = t;
	return (true);
}

template <typename T>
bool	Channel::_deleteInMap(std::map<std::string, T*> &targetMap, std::string &nick)
{
	std::cout << "nick: " << nick << std::endl;
	if (targetMap.find(nick) != targetMap.end())
	{
	//	delete targetMap[nick];  // 250210 Delete is not necessary
		targetMap.erase(nick);
		return (true);
	}
	return (false);
}


#endif
