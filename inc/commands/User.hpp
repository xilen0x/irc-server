#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include "ICommand.hpp"

class User : public ICommand
{
	public:
		bool welcomeMsgUser;
		User( void );
		~User( void );

		void execute( Server*, std::string &, int );
};

#endif

