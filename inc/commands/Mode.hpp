#ifndef MODE_HPP
# define MODE_HPP

# include <iostream>
# include <sstream>
# include <vector>
# include "ICommand.hpp"

class Mode : public ICommand
{
	private:
		std::string	_intToString( int num );
		bool		_isInt( const std::string &str );
		std::string	limit_mode(Channel *ch, char sign, std::string param, int maxLimitUser);

	public:
		~Mode( void );
		void execute( Server*, std::string &, int );
		bool getModeArgs(std::string msg, std::string &channelName, std::string &option, std::string &param);
		std::string inviteOnly_mode(Channel *ch, char sign, std::string optionChain);
		std::string modeOption_push(std::string optionChain, char sign, char option);
		std::string topic_mode(Channel *ch, char sign, std::string optionChain);
		std::string changeOperatorPrivilege(Server *server, Channel *ch, char sign, std::string nick, std::string optionChain, int &status);
		std::string key_mode(Channel *ch, char sign, std::string key, std::string optionChain);
};

#endif

