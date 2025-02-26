
# include "Channel.hpp"


// Private For debugging
void	Channel::_printVectorStrings(std::vector<std::string> stringVector)
{
	std::vector<std::string>::iterator it;

	for (it=stringVector.begin();it != stringVector.end(); it++)
	{
		std::cout << "\t- " << *it << std::endl;
	}
}

void	Channel::_printMapKeys(std::map<std::string, Client *> mapVar)
{
	std::map<std::string, Client *>::iterator it;

	for (it=mapVar.begin();it != mapVar.end(); it++)
	{
		std::cout << "\t- " << it->first << std::endl;
	}
}

/* ------------------- PUBLIC Constructor/ Destructor FUNCTIONS ------------------*/
Channel::Channel( void )
{
	this->_channelName = "";
	this->_inviteChannel = false;
	this->_topic = "";
	this->_topicRestricted = false;
	this->_hasChannelKey = false;
	this->_channelKey = "";
	this->_hasUserLimit = false;
	this->_userLimitNumber = MAX_USER_LIMIT_NUMBER;
	char cha[5] = {'i', 't', 'k', 'o', 'l'};
	for (int i = 0; i < 5; i++)
		this->_modeOptions.push_back(std::make_pair(cha[i], false));
}

Channel::Channel( std::string channelName, std::string operatorNick, Client *operatorClient) :_channelName( channelName )
{
	std::cout << "Channel => Object Map created" << std::endl;

	this->_inviteChannel = false;
	this->_topic = "";
	this->_topicRestricted = false;
	this->_hasChannelKey = false;
	this->_channelKey = "";
	this->_hasUserLimit = false;
	this->_userLimitNumber = MAX_USER_LIMIT_NUMBER;
	this->_operator[operatorNick] = operatorClient;
	char cha[5] = {'i', 't', 'k', 'o', 'l'};
	for (int i = 0; i < 5; i++)
		this->_modeOptions.push_back(std::make_pair(cha[i], false));
}

Channel::Channel( Channel const &src){ *this = src; }

Channel &Channel::operator=( Channel const &src)
{
	if (this != &src)
	{
		this->_channelName = src._channelName;
		this->_inviteChannel = src._inviteChannel;
		this->_topic = src._topic;
		this->_topicRestricted = src._topicRestricted;
		this->_channelKey = src._channelKey;
		this->_hasChannelKey = src._hasChannelKey;
		this->_hasUserLimit = src._hasUserLimit;
		this->_userLimitNumber = src._userLimitNumber;
		this->_modeOptions = src._modeOptions;
		this->_operator = src._operator;
		this->_memClients = src._memClients;
		this->_invClients = src._invClients;
	}
	return (*this);

}

Channel::~Channel( void )
{
	this->_memClients.clear();
	this->_invClients.clear();
	this->_operator.clear();
}

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

std::string	Channel::getChannelName( void ) const { return ( this->_channelName); }

void Channel::setChannelName(std::string channelName) { this->_channelName = channelName; }

Client*	Channel::getCliInChannel(std::string &nick)
{
	std::string nickCopy = nick;
	nickCopy = uppercase(nickCopy);
	std::map<std::string, Client *>::iterator it = _memClients.find(nickCopy);	
	if (it != _memClients.end())
		return (it->second);
	it = _invClients.find(nickCopy);
	if (it != _invClients.end())
		return (it->second);
	it = _operator.find(nickCopy);
	if (it != _operator.end())
		return (it->second);
	return (NULL);
}

Client*	Channel::getCliExceptInv(std::string &nick)
{
	std::string nickCopy = nick;
	nickCopy = uppercase(nickCopy);
	std::map<std::string, Client *>::iterator it = _memClients.find(nickCopy);
	if (it != _memClients.end())
		return (it->second);
	it = _operator.find(nickCopy);
	if (it != _operator.end())
		return (it->second);
	return (NULL);
}

//_inviteChannel
void	Channel::setModeOption(size_t index, bool option){this->_modeOptions[index].second = option;}
bool	Channel::getModeOption(size_t index){return this->_modeOptions[index].second;}
bool	Channel::isInviteChannel( void ) const { return (this->_inviteChannel); }

void	Channel::setInviteChannel ( void ) { this->_inviteChannel = true; }

void	Channel::unsetInviteChannel ( void ){ this->_inviteChannel = false; }

// _topic
std::string	Channel::getTopic( void ) const { return ( this->_topic); } 

void	Channel::setTopic( std::string topic ) { this->_topic = topic; }

// _topicRestricted
bool	Channel::isTopicRestricted( void ) const { return ( this->_topicRestricted); }

void	Channel::setTopicRestricted( void ) { this->_topicRestricted = true; }

void	Channel::unsetTopicRestricted( void ) { this->_topicRestricted = false; }

// _channelKey
bool	Channel::getHasChannelKey( void ) const { return ( this->_hasChannelKey); }
void	Channel::setHasChannelKey( bool flag ) { this->_hasChannelKey = flag; }

std::string	Channel::getChannelKey( void ) const { return( this->_channelKey); }

void	Channel::setChannelKey( std::string key ) { this->_channelKey = key;}

// _userLimit
bool	Channel::isUserLimitActived( void ) const { return ( this->_hasUserLimit ); }

void	Channel::setUserLimitActived( void ) { this->_hasUserLimit = true; }

void	Channel::unsetUserLimitActived( void ) { this->_hasUserLimit = false; }

// _userLimitNumber
int		Channel::getUserLimitNumber( void ) const { return (this->_userLimitNumber); }
void	Channel::setUserLimitNumber( int limit) { this->_userLimitNumber = limit; }

int		Channel::getClientSum() { return (this->_operator.size() + this->_memClients.size() + this->_invClients.size()); }
int		Channel::getOperAndMemSum( void ) { return (this->_operator.size() + this->_memClients.size()); }

std::string 	Channel::getClientsList()
{
	std::string list;
	for (std::map<std::string, Client *>::iterator it = _operator.begin(); it != _operator.end(); ++it)
	{
		list += "@" + it->first;
		std::map<std::string, Client *>::iterator next_it = it;
		++next_it;
		if (next_it != _operator.end())
			list += " ";
	}
	if (!_operator.empty() && !_memClients.empty())
		list += " ";
	for (std::map<std::string, Client *>::iterator it = _memClients.begin(); it != _memClients.end(); ++it)
	{
		list += it->first;
		std::map<std::string, Client *>::iterator next_it = it;
		++next_it;
		if (next_it != _memClients.end())
			list += " ";
	}
	return list;
}

void 	Channel::addOpe(Client *client)
{
	if (!client->getNick().empty())
	{
		std::string nick = client->getNick();
		if (!this->_addInMap(this->_operator, nick, client))
			std::cout << nick << " is already in _operator map. CAN'T ADD!!!" << std::endl;//debug
	}
}

void 	Channel::deleteOpe(std::string &nick)
{
	if (!this->_deleteInMap(this->_operator, nick))
		std::cout << nick << " is NOT in _operator map. CAN'T DELETE IT!!!" << std::endl;//debug
}

void	Channel::addMem(Client *client)
{
	if (!client->getNick().empty())
	{
		std::string nick = client->getNick();
		if (!this->_addInMap(this->_memClients, nick, client))
			std::cout << nick << " is already in _memClients map. CAN'T ADD!!!" << std::endl;//debug
		else
			std::cout << nick << " has been added in _memClients map! " << std::endl;//debug
	}
}

void	Channel::deleteMem(std::string &nick)//uppercase
{
	if (!this->_deleteInMap(this->_memClients, nick))
		std::cout << nick << " is NOT in _memClients map. CAN'T DELETE IT!!!" << std::endl;//debug
}

std::string	Channel::getFirstMemNick( void ) { return (this->_memClients.begin()->first); }
std::string Channel::getFirstOpeNick( void ) { return (this->_operator.begin()->first); }

Client*	Channel::getFirstMem( void ) { return (this->_memClients.begin()->second); }

Client*	Channel::getFirstOpe( void ) { return (this->_operator.begin()->second); }//debug

std::vector<std::string>	Channel::getNicksInChannel( void )
{
	std::vector<std::string>	allNicks;

	for (std::map<std::string, Client *>::iterator it = _operator.begin(); it != _operator.end(); it++)
		allNicks.push_back(it->first);
	for (std::map<std::string, Client *>::iterator it = _memClients.begin(); it != _memClients.end(); it++)
		allNicks.push_back(it->first);
	return (allNicks);
}

// Returns:
// fd from client in position _operator[position]
// -1 if position is not in Range of _operator.size()
int	Channel::getFdOperatorByPosInOperators(size_t pos)
{

	std::map<std::string, Client *>::iterator it;

	it = _operator.begin();

	if (pos <= _operator.size())
	{	
		for (size_t i = 1; i <= pos; i++)
			it++;
		return ( it->second->getFdClient() );
	}
	std::cout << "!!!!!!NOT IN limits : Pos = " << pos << " , _operator.size()=" << _operator.size() << std::endl;//debug
	return (-1);
}

int	Channel::getFdMemberByPosInMemClients(size_t pos)
{
	std::map<std::string, Client *>::iterator it;

	it = _memClients.begin();

	if (pos <= _memClients.size())
	{
		for (size_t i = 1; i <= pos; i++)
			it++;
		return ( it->second->getFdClient());
	}
	std::cout << "!!!!!!NOT IN limits : Pos = " << pos << " , _memClients.size()=" << _memClients.size() << std::endl;//debug
	return (-1);
}

void	Channel::addInv(Client *client)
{
	if (!client->getNick().empty())
	{
		std::string nick = client->getNick();
		if (!this->_addInMap(this->_invClients, nick, client))
			std::cout << nick << " is in already _invClients map. CAN'T ADD!!!" << std::endl;//debug
		else
			std::cout << nick << " has been added in _invClients map! " << std::endl;//debug
	}
}
		
void	Channel::deleteInv(std::string &nick)
{
	if (!this->_deleteInMap(this->_invClients, nick))
		std::cout << nick << " is NOT in _invClients map. CAN'T DELETE IT!!!" << std::endl;//debug
}

bool	Channel::isOpe(std::string nick)
{
	if( this->_operator.find(nick) != this->_operator.end() )
		return ( true );
	return ( false );
}

bool	Channel::isMem(std::string nick)
{
	if( this->_memClients.find(nick) != this->_memClients.end() )
		return ( true );
	return ( false );
}

size_t	Channel::sizeOpe( void ) { return (this->_operator.size()); }

size_t	Channel::sizeMem( void ) { return (this->_memClients.size()); }

bool	Channel::isInv(std::string nick)
{
	if( this->_invClients.find(nick) != this->_invClients.end() )
		return ( true );
	return ( false );
}

//debug
void	Channel::printChannelVars( void )
{
	std::cout << "----- CHANNEL DATA  (start)-----" << std::endl;
	std::cout << "_channelName = " << this->_channelName << std::endl;
	std::cout << "_inviteChannel = " << this->_inviteChannel << std::endl;
	std::cout << "_topic = " << this->_topic << std::endl;
	std::cout << "_topicRestricted = " << this->_topicRestricted << std::endl;
	std::cout << "_channelKey = " << this->_channelKey << std::endl;
	std::cout << "_hasUserLimit = " << this->_hasUserLimit << std::endl;
	std::cout << "_userLimitNumber = " << this->_userLimitNumber << std::endl;
	std::cout << "- CHANNEL _operators:" << std::endl;
	this->_printMapKeys(this->_operator);
	std::cout << "- CHANNEL _memClients:" << std::endl;
	this->_printMapKeys(this->_memClients);
	std::cout << "- CHANNEL _invitedClients:" << std::endl;
	this->_printMapKeys(this->_invClients);
	std::cout << "----- CHANNEL DATA  (end)-----\n" << std::endl;
}
