/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apardo-m <apardo-m@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 07:11:15 by apardo-m          #+#    #+#             */
/*   Updated: 2025/01/19 11:00:24 by apardo-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <vector>

class Channel
{
	private:
		std::string		_channelName;

		bool 			_inviteChannel;

		std::string		_topic; 			// For Channel
		bool			_topicRestricted;	// If True only operatos can change _topic

		std::string		_channelKey;

		bool			_hasUserLimit;
		unsigned long	_userLimitNumber;

		// DOUBT: 250119 - only store nicks?
		std::vector<std::string>	_operators;
		std::vector<std::string>	_memberClients;
		std::vector<std::string>	_invitedClients;

		std::vector<std::string>::iterator	_findStringInVector( std::string  findString);
		
	public:
		// Channel( std::string channelName, std::string operatorNick );
		// ~Channel( void );

		// //_channelName
		// std::string		getChannelName( void ) const;

		// //_inviteChannel
		// bool			isInviteChannel( void ) const;
		// void			setInviteChannel ( void );
		// void			unsetInviteChannel ( void );

		// // _topic
		// std::string		getTopic( void ) const;
		// void			setTopic( std::string topic );

		// //_topicRestricted
		// bool			isTopicRestricted( void ) const;
		// void			setTopicRestricted( void );
		// void			unsetTopicRestricted( void );

		// // _channelKey
		// std::string		getChannelKey( void ) const;
		// void			setChannelKey( std::string key );

		// // _userLimit
		// bool			isUserLimitActived( void ) const;
		// void			setUserLimitActived( void );
		// void			unsetUserLimitActived( void );

		// // _userLimitNumber
		// unsigned long	getUserLimitNumber( void ) const;
		// void			setUserLimitNumber( unsigned long limit);

		// // _operators
		// bool 			isOperator( std::string nickClient );
		// void 			addOperator( std::string nickClient );
		// void 			deleteOperator( std::string nickClient );

		// // _memberClients
		// bool			isMember( std::string nickClient );
		// void			addMember( std::string nickClient );
		// void			deleteMember( std::string nickClient );

		// // _invitedClients
		// bool			isInvited( std::string nickClient );
		// void			addInvited( std::string nickClient );
		// void			deleteInvited( std::string nickClient );
}

#endif