#ifndef CHANNEL_TPP
# define CHANNEL_TPP

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
	if (targetMap.find(nick) != targetMap.end())
	{
		targetMap.erase(nick);
		return (true);
	}
	return (false);
}


#endif
