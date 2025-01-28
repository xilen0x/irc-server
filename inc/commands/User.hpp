#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include "ICommand.hpp"

class User : public ICommand
{
	public:
		~User( void );

		// void execute( std::string & , int );
		void execute( Server*, std::string &, int );
};

#endif

