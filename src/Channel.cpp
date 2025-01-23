/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apardo-m <apardo-m@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 08:59:00 by apardo-m          #+#    #+#             */
/*   Updated: 2025/01/23 13:47:46 by apardo-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	this->_printVectorStrings(this->_operators);
	std::cout << "- CHANNEL _memberClients:" << std::endl;
	this->_printVectorStrings(this->_memberClients);
	std::cout << "- CHANNEL _invitedClients:" << std::endl;
	this->_printVectorStrings(this->_invitedClients);
	std::cout << "----- CHANNEL DATA  (end)-----" << std::endl;
}
