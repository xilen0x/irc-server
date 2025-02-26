#ifndef PRIVMSG_HPP
# define PRIVMSG_HPP

# include <iostream>
# include "ICommand.hpp"

class Privmsg : public ICommand
{
	public:
		~Privmsg( void );
		void execute( Server*, std::string &, int );
};

#endif

