
#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <algorithm> 
# include <iostream>
# include <vector>
# include <map>
# include "Server.hpp"
# include "Client.hpp"

class Channel
{
	private:
		std::string		_channelName;

		bool 			_inviteChannel;

		std::string		_topic; 			// For Channel
		bool			_topicRestricted;	// If True only operatos can change _topic

		std::string		_channelKey;//password channel

		bool			_hasUserLimit;
		unsigned long	_userLimitNumber;

		// DOUBT: 250119 - only store nicks o store Objects?
		std::vector<std::string>	_operators;
		std::vector<std::string>	_memberClients;
		std::vector<std::string>	_invitedClients;

		// Added by Linnnnnnnnnnnnnnnnnn
//		std::vector<Client> 		_clients; // including _memberClients and _invitedClients
//		std::vector<Client> 		_operators;
		std::map<std::string, Client *>	_memClients;
		std::map<std::string, Client *>	_invClients;
		std::map<std::string, Client *>	_operator;

		template <typename T>
		bool	_addInMap(std::map<std::string, T*> &targetMap, std::string &nick, T *t);
		template <typename T>
		bool	_deleteInMap(std::map<std::string, T*> &targetMap, std::string &nick);


		template <typename T>
		bool	_isInVector(T &t, std::string nickClient );

		template <typename T>
		bool	_addInVector(T &t, std::string nickClient );

		template <typename T>
		bool	_deleteInVector(T &t, std::string nickClient );

		// For debugging
		void	_printVectorStrings(std::vector<std::string> stringVector);

	public:
		Channel( std::string channelName, std::string operatorNick );
		Channel( std::string channelName, std::string operatorNick, Client *operatorClient);
		Channel( Channel const &src);
		Channel &operator=( Channel const &src);
		~Channel( void );

		//_channelName
		std::string		getChannelName( void ) const;

		// to get Client with nickname in a specific channel //Added by Lin
		Client			*getCliInChannel(std::string &nick);

		std::string 	getClientsList();

		//_inviteChannel
		bool			isInviteChannel( void ) const;
		void			setInviteChannel ( void );
		void			unsetInviteChannel ( void );

		// _topic
		std::string		getTopic( void ) const;
		void			setTopic( std::string topic );

		//_topicRestricted
		bool			isTopicRestricted( void ) const;
		void			setTopicRestricted( void );
		void			unsetTopicRestricted( void );

		// _channelKey
		std::string		getChannelKey( void ) const;
		void			setChannelKey( std::string key );

		// _userLimit
		bool			isUserLimitActived( void ) const;
		void			setUserLimitActived( void );
		void			unsetUserLimitActived( void );

		// _userLimitNumber
		unsigned long	getUserLimitNumber( void ) const;
		void			setUserLimitNumber( unsigned long limit);

		// _operators
		bool 			isOperator( std::string nickClient );
		void 			addOperator( std::string nickClient );
		void 			deleteOperator( std::string nickClient );

		// _memberClients
		bool			isMember( std::string nickClient );
		void			addMember( std::string nickClient );
		void			deleteMember( std::string nickClient );

		// _invitedClients
		bool			isInvited( std::string nickClient );
		void			addInvited( std::string nickClient );
		void			deleteInvited( std::string nickClient );

		// _operator _memClients _invClients  Added by Linnnnnnnnnnnnnnnnnnnn
		void 			addOpe(Client *client);
		void 			deleteOpe(std::string &nick);
		void			addMem(Client *client);
		void			deleteMem(std::string &nick);
		void			addInv(Client *client);
		void			deleteInv(std::string &nick);

// For debugging
		void		printChannelVars( void ); 
};

# include "Channel.tpp"
# include "Channel1.tpp"

#endif
