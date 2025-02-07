#ifndef NICK_HPP
# define NICK_HPP

# include <iostream>
# include "ICommand.hpp"

class Nick : public ICommand
{
	public:
		bool welcomeMsgNick;
		Nick( void );
		~Nick( void );

		void execute( Server*, std::string &, int );
};

#endif
