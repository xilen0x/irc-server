#ifndef INVITE_HPP
# define INVITE_HPP

# include <iostream>
# include "ICommand.hpp"

class Invite : public ICommand
{
	public:
		~Invite( void );

		void execute( Server*, std::string &, int );
};

#endif

