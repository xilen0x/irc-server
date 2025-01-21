/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apardo-m <apardo-m@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 08:59:00 by apardo-m          #+#    #+#             */
/*   Updated: 2025/01/21 18:06:28 by apardo-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Channel.hpp"

# define DEFAULT_LIMIT 100


/* ------------------- PUBLIC Constructor/ Destructor FUNCTIONS ------------------*/
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

Channel::~Channel( void )
{
	std::cout << "~Channel => Clear vectors" << std::endl;
	this->_operators.clear();
	this->_memberClients.clear();
	this->_invitedClients.clear();
}

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/
//_channelName
std::string	Channel::getChannelName( void ) const { return ( this->_channelName); }

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
unsigned long	Channel::getUserLimitNumber( void ) const { return (this->_userLimitNumber); }

void	Channel::setUserLimitNumber( unsigned long limit) { this->_userLimitNumber = limit; }

// _operators
//bool 	Channel::isOperator( std::string nickClient )
//{
//	for ( std::vector<std::string>::iterator it = this->_operators.begin(); it != this->_operators.end(); ++it)
//	{
//		if (*it == nickClient)
//			return (true);
//	}
//	return (false);
//}
bool 	Channel::isOperator( std::string nickClient )
{
	return ( this->_isInVector(this->_operators, nickClient));
}

void 	Channel::addOperator( std::string nickClient )
{
	if (!this->_addInVector(this->_operators,nickClient))
		std::cout << nickClient << "is in _operators vector. CAN´T ADD!!!" << std::endl;
}

void 	Channel::deleteOperator( std::string nickClient )
{
	this->_deleteInVector(this->_operators, nickClient);
}

// _memberClients
bool	Channel::isMember( std::string nickClient )
{
	return ( this->_isInVector(this->_memberClients, nickClient));
}

void	Channel::addMember( std::string nickClient )
{
	if (!this->_addInVector(this->_memberClients, nickClient))
		std::cout << nickClient << "is in _memberClients. CAN´T ADD!!!" << std::endl;
}

void	Channel::deleteMember( std::string nickClient )
{
	this->_deleteInVector(this->_memberClients, nickClient);
}

// _invitedClients
bool	Channel::isInvited( std::string nickClient )
{
	return ( this->_isInVector(this->_invitedClients, nickClient));
}

void	Channel::addInvited( std::string nickClient )
{
	if (!this->_addInVector(this->_memberClients, nickClient))
		std::cout << nickClient << "is in  invitedClients. CAN´T ADD!!!" << std::endl;
}

void	Channel::deleteInvited( std::string nickClient )
{
	this->_deleteInVector(this->_invitedClients, nickClient);
}
