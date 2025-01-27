#ifndef CHANNEL_TPP
# define CHANNEL_TPP

# include "Channel.hpp"

template <typename T>
bool	Channel::_isInVector(T &t, std::string nickClient )
{
	std::vector<std::string>::iterator it;
	
	if (t.size() != 0)
	{	
		it = std::find(t.begin(), t.end(), nickClient);
		if (it != t.end())
			return (true);
	}
	return (false);
}

template <typename T>
bool	Channel::_addInVector(T &t, std::string nickClient )
{
	if (this->_isInVector(t, nickClient))
		return (false);
	t.push_back(nickClient);
	return (true);
}

template <typename T>
bool	Channel::_deleteInVector(T &t, std::string nickClient )
{
	std::vector<std::string>::iterator	it;
	
	it = std::find(t.begin(), t.end(), nickClient);
	if (it == t.end())
		return (false);
	t.erase(it);
	return (true);
}	

#endif
