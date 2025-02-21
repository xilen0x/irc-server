#ifndef MODE_HPP
# define MODE_HPP

# include <iostream>
# include <sstream>
# include "ICommand.hpp"

class Mode : public ICommand
{
	private:
		std::string limit_mode(Channel *ch, char sign, std::string optionChain);
				

	public:
		~Mode( void );
		// void execute( std::string & , int );
		void execute( Server*, std::string &, int );
		void getModeArgs(std::string msg, std::string &channelName, std::string &option, std::string &param);
		std::string inviteOnly_mode(Channel *ch, char sign, std::string optionChain);
		std::string modeOption_push(std::string optionChain, char sign, char option);
		std::string topic_mode(Channel *ch, char sign, std::string optionChain);
		// std::string changeOperatorPrivilege(Server *server, Channel *ch, char sign, std::string nick, std::string optionChain);
		std::string changeOperatorPrivilege(Server *server, Channel *ch, char sign, std::string nick, std::string optionChain, int &status);
		std::string key_mode(Channel *ch, char sign, std::string key, std::string optionChain);
};

#endif

