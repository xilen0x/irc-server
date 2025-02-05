#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include "ICommand.hpp"

class User : public ICommand
{
	private:
		bool welcomeMsg;
		
	public:
		User( void );
		~User( void );

		void execute( Server*, std::string &, int );
};

#endif

