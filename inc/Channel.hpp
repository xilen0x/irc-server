
#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <algorithm> 
# include <iostream>
# include <vector>

# include <map>
# include "Server.hpp"
# include "Client.hpp"

# define MAX_USER_LIMIT_NUMBER 100

class Client;

class Channel
{
	private:
		std::string		_channelName;

		bool 			_inviteChannel;

		std::string		_topic; 			// For Channel
		bool			_topicRestricted;	// If True only operatos can change _topic

		bool			_hasChannelKey;
		std::string		_channelKey;//password channel

		bool			_hasUserLimit;
		int				_userLimitNumber;
		std::vector<std::pair<char, bool> > _modeOptions;


		std::map<std::string, Client *>	_memClients;
		std::map<std::string, Client *>	_invClients;
		std::map<std::string, Client *>	_operator;

		template <typename T>
		bool	_addInMap(std::map<std::string, T*> &targetMap, std::string &nick, T *t);

		template <typename T>
		bool	_deleteInMap(std::map<std::string, T*> &targetMap, std::string &nick);


		void	_printVectorStrings(std::vector<std::string> stringVector);

		void	_printMapKeys(std::map<std::string, Client *> mapVar);

	public:
		Channel( void );
		// Channel( std::string channelName, std::string operatorNick );
		Channel( std::string channelName, std::string operatorNick, Client *operatorClient);
		Channel( Channel const &src);
		Channel &operator=( Channel const &src);
		~Channel( void );

		std::string		getChannelName( void ) const;
		void			setChannelName(std::string channelName);

		// to get Client with nickname in a specific channel
		Client			*getCliInChannel(std::string &nick);
		Client			*getCliExceptInv(std::string &nick);

		std::string 	getClientsList();

		//_inviteChannel
		void			setModeOption(size_t index, bool option);
		bool			getModeOption(size_t index);
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
		bool			getHasChannelKey( void ) const;
		void			setHasChannelKey( bool flag );
		std::string		getChannelKey( void ) const;
		void			setChannelKey( std::string key );

		// _userLimit
		bool			isUserLimitActived( void ) const;
		void			setUserLimitActived( void );
		void			unsetUserLimitActived( void );

		// _userLimitNumber
		int				getUserLimitNumber( void ) const;
		void			setUserLimitNumber( int limit);

		int				getClientSum();
		int				getOperAndMemSum( void );


		// _operator _memClients _invClients
		void 			addOpe(Client *client);
		void 			deleteOpe(std::string &nick);
		void			addMem(Client *client);
		void			deleteMem(std::string &nick);
		void			addInv(Client *client);
		void			deleteInv(std::string &nick);

		bool			isOpe(std::string nick);
		bool			isMem(std::string nick);
		Client 			*getFirstMem( void );
		std::string		getFirstMemNick( void );
		size_t			sizeOpe( void );
		size_t			sizeMem( void );
		bool			isInv(std::string nick);
		Client			*getFirstOpe( void );
		std::string		getFirstOpeNick( void );
		std::vector<std::string>	getNicksInChannel( void );
		int				getFdOperatorByPosInOperators(size_t pos);
		int				getFdMemberByPosInMemClients(size_t pos);


// For debugging
		void		printChannelVars( void ); 
};

# include "Channel.tpp"

#endif
