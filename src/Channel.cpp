
# include "Channel.hpp"

# define DEFAULT_LIMIT 100

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
Channel::Channel( void ) : _channelName(""), _inviteChannel(false), _channelKey("")
{}


/*
// 250212 - Delete this part?????
Channel::Channel( std::string channelName, std::string operatorNick ) :_channelName( channelName )
{
	std::cout << "Channel => Object created" << std::endl;

	this->_inviteChannel = false;
	this->_topic = "";
	this->_topicRestricted = false;
	this->_channelKey = "";
	this->_hasUserLimit = false;
	this->_userLimitNumber = DEFAULT_LIMIT;
	this->_operators.push_back(operatorNick);
}
*/

// Reloaded by Linnnnnnnnnnnnnnnnnnnnnn
Channel::Channel( std::string channelName, std::string operatorNick, Client *operatorClient) :_channelName( channelName )
{
	std::cout << "Channel => Object Map created" << std::endl;

	this->_inviteChannel = false;
	this->_topic = "";
	this->_topicRestricted = false;
	this->_channelKey = "";
	this->_hasUserLimit = false;
	this->_userLimitNumber = DEFAULT_LIMIT;
//	this->_operators.push_back(operatorNick);  // 250212 - Delete ????? 
	this->_operator[operatorNick] = operatorClient;
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
		this->_hasUserLimit = src._hasUserLimit;
		this->_userLimitNumber = src._userLimitNumber;

/*
// 250212 - Delete this part?????
		this->_operators = src._operators;
		this->_memberClients = src._memberClients;
		this->_invitedClients = src._invitedClients;
*/

		this->_operator = src._operator;
		this->_memClients = src._memClients;
		this->_invClients = src._invClients;
	}
	return (*this);

}

Channel::~Channel( void )
{
	//std::cout << "~Channel => Clear vectors (_channelName=\"" << this->_channelName << "\")" << std::endl;
/*
// 250212 - Delete this part?????
	this->_operators.clear();
	this->_memberClients.clear();
	this->_invitedClients.clear();
*/
	this->_memClients.clear();
	this->_invClients.clear();
	this->_operator.clear();
}

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/
//_channelName
std::string	Channel::getChannelName( void ) const { return ( this->_channelName); }

void Channel::setChannelName(std::string channelName) { this->_channelName = channelName; }

/*
// it will be modified in near future: clients should be those in this instance of channel instead of those in server
Client	*Channel::getCliInChannel(std::string &nick)
{
	for (std::vector<Client>::iterator it = _clients.begin(); it !=_clients.end(); it++)
	{
		std::string tmpCli = it->getNick();
		if (uppercase(tmpCli) == uppercase(nick))
			return (&(*it));
	}
	for (std::vector<Client>::iterator it = _operators.begin(); it != _operators.end(); it++)
	{
		std::string tmpOpe = it->getNick();
		if (uppercase(tmpOpe) == uppercase(nick))
			return (&(*it));
	}
	return (NULL);
}
*/

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

//_inviteChannel
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
std::string	Channel::getChannelKey( void ) const { return( this->_channelKey); }

void	Channel::setChannelKey( std::string key ) { this->_channelKey = key; }

// _userLimit
bool	Channel::isUserLimitActived( void ) const { return ( this->_hasUserLimit ); }

void	Channel::setUserLimitActived( void ) { this->_hasUserLimit = true; }

void	Channel::unsetUserLimitActived( void ) { this->_hasUserLimit = false; }

// _userLimitNumber
int		Channel::getUserLimitNumber( void ) const { return (this->_userLimitNumber); }
//unsigned long	Channel::getUserLimitNumber( void ) const { return (this->_userLimitNumber); }

void	Channel::setUserLimitNumber( unsigned long limit) { this->_userLimitNumber = limit; }

int		Channel::getClientSum() { return (this->_operator.size() + this->_memClients.size() + this->_invClients.size()); }

/*
std::string 	Channel::getClientsList()
{
	std::string list;
	for (std::map<std::string, Client *>::iterator it = _operator.begin(); it != _operator.end(); ++it)
	{
		list += "@" + it->second->getNick();
		std::map<std::string, Client *>::iterator next_it = it;
		++next_it;
		if (next_it != _operator.end())
			list += " ";
	}
	if (!_operator.empty() && !_memClients.empty())
		list += " ";
	for (std::map<std::string, Client *>::iterator it = _memClients.begin(); it != _memClients.end(); ++it)
	{
		list += it->second->getNick();
		std::map<std::string, Client *>::iterator next_it = it;
		++next_it;
		if (next_it != _memClients.end())
			list += " ";
	}
	return list;
}
*/

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


/*
// 250212 - Delete this part?????
// _operators
bool 	Channel::isOperator( std::string nickClient )
{
	return ( this->_isInVector(this->_operators, nickClient));
}

void 	Channel::addOperator( std::string nickClient )
{
	if (!this->_addInVector(this->_operators,nickClient))
		std::cout << nickClient << " is in _operators vector. CAN´T ADD!!!" << std::endl;
}

void 	Channel::deleteOperator( std::string nickClient )
{
	if(!this->_deleteInVector(this->_operators, nickClient))
		std::cout << nickClient << " is NOT in _operators. CAN´T DELETE IT!!!" << std::endl;

}

size_t	Channel::sizeOperators( void ) { return (this->_operators.size()); }

// _memberClients
bool	Channel::isMember( std::string nickClient )
{
	return ( this->_isInVector(this->_memberClients, nickClient));
}

void	Channel::addMember( std::string nickClient )
{
	if (!this->_addInVector(this->_memberClients, nickClient))
		std::cout << nickClient << " is in _memberClients. CAN´T ADD!!!" << std::endl;
}

void	Channel::deleteMember( std::string nickClient )
{
	if( !this->_deleteInVector(this->_memberClients, nickClient))
		std::cout << nickClient << " is NOT  in _memberClients. CAN´T DELETE IT!!!" << std::endl;
}

size_t	Channel::sizeMemberClients( void ) { return (this->_memClients.size()); }

// _invitedClients
bool	Channel::isInvited( std::string nickClient )
{
	return ( this->_isInVector(this->_invitedClients, nickClient));
}

void	Channel::addInvited( std::string nickClient )
{
	if (!this->_addInVector(this->_invitedClients, nickClient))
		std::cout << nickClient << " is in invitedClients. CAN´T ADD!!!" << std::endl;
}

void	Channel::deleteInvited( std::string nickClient )
{
	if(!this->_deleteInVector(this->_invitedClients, nickClient))
		std::cout << nickClient << " is NOT in _invitedClients. CAN´T DELETE IT!!!" << std::endl;
}
*/

// Added by Linnnnnnnnnnnnnnnnnnnnnnnnnn
//void 	Channel::addOpe(std::string &nick, Client *client)
void 	Channel::addOpe(Client *client)
{
	if (!client->getNick().empty())
	{
		std::string nick = client->getNick();
//		if (!this->_addInMap(this->_operator, nick, client))
		if (!this->_addInMap(this->_operator, nick, client))
			std::cout << nick << " is already in _operator map. CAN'T ADD!!!" << std::endl;
	}
}

void 	Channel::deleteOpe(std::string &nick)
{
	if (!this->_deleteInMap(this->_operator, nick))
		std::cout << nick << " is NOT in _operator map. CAN'T DELETE IT!!!" << std::endl;
}

void	Channel::addMem(Client *client)
{
	if (!client->getNick().empty())
	{
		std::string nick = client->getNick();
		if (!this->_addInMap(this->_memClients, nick, client))
			std::cout << nick << " is already in _memClients map. CAN'T ADD!!!" << std::endl;
		else
			std::cout << nick << " has been added in _memClients map! " << std::endl;
	}
}

void	Channel::deleteMem(std::string &nick)//uppercase
{
	if (!this->_deleteInMap(this->_memClients, nick))
		std::cout << nick << " is NOT in _memClients map. CAN'T DELETE IT!!!" << std::endl;
}

std::string	Channel::getFirstMemNick( void ) { return (this->_memClients.begin()->first); }
std::string Channel::getFirstOpeNick( void ) { return (this->_operator.begin()->first); }

Client*	Channel::getFirstMem( void ) { return (this->_memClients.begin()->second); } //Delete ???

Client*	Channel::getFirstOpe( void ) { return (this->_operator.begin()->second); }  // For test 251213  Delete ??

// Start  250215 by apardo-m

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
	std::cout << "!!!!!!NOT IN limits : Pos = " << pos << " , _operator.size()=" << _operator.size() << std::endl;
	return (-1);

//	return (this->_getFdInMapSctringClient(pos, this->_operator));
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
	std::cout << "!!!!!!NOT IN limits : Pos = " << pos << " , _memClients.size()=" << _memClients.size() << std::endl;
	return (-1);
}
// End  250215 by apardo-m

void	Channel::addInv(Client *client)
{
	if (!client->getNick().empty())
	{
		std::string nick = client->getNick();
		if (!this->_addInMap(this->_invClients, nick, client))
			std::cout << nick << " is in already _invClients map. CAN'T ADD!!!" << std::endl;
		else
			std::cout << nick << " has been added in _invClients map! " << std::endl;
	}
}
		
void	Channel::deleteInv(std::string &nick)
{
	if (!this->_deleteInMap(this->_invClients, nick))
		std::cout << nick << " is NOT in _invClients map. CAN'T DELETE IT!!!" << std::endl;
}
// End Added by Linnnnnnnnnnnnnnnnnnnnnnnnnn

// 250207 by apardo-m
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

// End 250207 by apardo-m

// 250212 by apardo-m
bool	Channel::isInv(std::string nick)
{
	if( this->_invClients.find(nick) != this->_invClients.end() )
		return ( true );
	return ( false );
}
// End 250212 by apardo-m

// For debugging
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
	//this->_printVectorStrings(this->_operators);
	this->_printMapKeys(this->_operator);
	std::cout << "- CHANNEL _memClients:" << std::endl;
//	this->_printVectorStrings(this->_memberClients);
	this->_printMapKeys(this->_memClients);
	std::cout << "- CHANNEL _invitedClients:" << std::endl;
//	this->_printVectorStrings(this->_invitedClients);
	this->_printMapKeys(this->_invClients);
	std::cout << "----- CHANNEL DATA  (end)-----\n" << std::endl;
}
