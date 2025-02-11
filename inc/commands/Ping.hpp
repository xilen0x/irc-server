#ifndef PING_HPP
# define PING_HPP

# include <iostream>
# include "ICommand.hpp"

class Ping : public ICommand
{
	public:
		~Ping( void );

		void execute( Server*, std::string &, int );
};

#endif
