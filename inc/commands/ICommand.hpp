#ifndef ICOMMAND_HPP
# define ICOMMAND_HPP

# include "replies.hpp"
# include "Server.hpp"

class ICommand
{
	public:
		virtual	~ICommand( void ) {};

		virtual void execute( Server*, std::string &, int ) = 0;
};

#endif
