#ifndef ICOMMAND_HPP
# define ICOMMAND_HPP

# include "replies.hpp"

class ICommand
{
	public:
		virtual	~ICommand( void ) {};

		virtual void execute( void ) = 0;
		virtual void execute( std::string ) = 0;
};

#endif
