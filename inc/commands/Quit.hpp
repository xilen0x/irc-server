#ifndef QUIT_HPP
# define QUIT_HPP

# include <iostream>
# include "ICommand.hpp"

class Quit : public ICommand
{
	private:
		void _selectMemberAsOperator( Server* server, Channel* actualChannel);

	public:
		~Quit( void );

		void execute( Server*, std::string &, int );
};

#endif

