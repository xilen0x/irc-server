
#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <algorithm> 
# include <iostream>
# include <vector>

// includes by Linnnnnnnnnnnnnnnn
# include <map>
# include "Server.hpp"
# include "Client.hpp"

class Client;

class Channel
{
	private:
		std::string		_channelName;

		bool 			_inviteChannel;

		std::string		_topic; 			// For Channel
		bool			_topicRestricted;	// If True only operatos can change _topic

		std::string		_channelKey;//password channel

		bool			_hasUserLimit;
		int				_userLimitNumber;
//		unsigned long	_userLimitNumber;

/*
// 250212 - Delete this part?????
		std::vector<std::string>	_operators;
		std::vector<std::string>	_memberClients;
		std::vector<std::string>	_invitedClients;
*/

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

		// End Added Linnnnnnnnnnnnnnnnn

/*
// 250212 - Delete this part?????
		template <typename T>
		bool	_isInVector(T &t, std::string nickClient );

		template <typename T>
		bool	_addInVector(T &t, std::string nickClient );

		template <typename T>
		bool	_deleteInVector(T &t, std::string nickClient );
*/
/*		
		template <typename T>
		int		_getFdInMapSctringClient(size_t pos, T &t);
*/
		// For debugging
		void	_printVectorStrings(std::vector<std::string> stringVector);

		void	_printMapKeys(std::map<std::string, Client *> mapVar);

	public:
		Channel( void );
		Channel( std::string channelName, std::string operatorNick );
		Channel( std::string channelName, std::string operatorNick, Client *operatorClient);    // By Linnnnnnn
		Channel( Channel const &src);
		Channel &operator=( Channel const &src);
		~Channel( void );

		//_channelName
		std::string		getChannelName( void ) const;
		void			setChannelName(std::string channelName);

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
//		unsigned long	getUserLimitNumber( void ) const;
		int				getUserLimitNumber( void ) const;
		void			setUserLimitNumber( unsigned long limit);

		int				getClientSum();

/*
// 250212 - Delete this part?????
		// _operators
		bool 			isOperator( std::string nickClient );
		void 			addOperator( std::string nickClient );
		void 			deleteOperator( std::string nickClient );
		size_t			sizeOperators( void );

		// _memberClients
		bool			isMember( std::string nickClient );
		void			addMember( std::string nickClient );
		void			deleteMember( std::string nickClient );
		size_t			sizeMemberClients( void );

		// _invitedClients
		bool			isInvited( std::string nickClient );
		void			addInvited( std::string nickClient );
		void			deleteInvited( std::string nickClient );
*/
		// _operator _memClients _invClients  Added by Linnnnnnnnnnnnnnnnnnnn
		void 			addOpe(Client *client);
		void 			deleteOpe(std::string &nick);
		void			addMem(Client *client);
		void			deleteMem(std::string &nick);
		void			addInv(Client *client);
		void			deleteInv(std::string &nick);

		// 250207 by apardo-m
		bool			isOpe(std::string nick);
		bool			isMem(std::string nick);
		Client 			*getFirstMem( void );  // Delete???
		std::string		getFirstMemNick( void );
		size_t			sizeOpe( void );
		size_t			sizeMem( void );
		// 250212 by apardo-m
		bool			isInv(std::string nick);
		Client			*getFirstOpe( void );  // For test 250213 . Delte???
		std::string		getFirstOpeNick( void );
		// 250215 by apardo-m
		std::vector<std::string>	getNicksInChannel( void );
		int				getFdOperatorByPosInOperators(size_t pos);
		int				getFdMemberByPosInMemClients(size_t pos);


// For debugging
		void		printChannelVars( void ); 
};

# include "Channel.tpp"
# include "Channel1.tpp"

#endif
