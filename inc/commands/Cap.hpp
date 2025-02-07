#ifndef CAP_HPP
# define CAP_HPP

# include <iostream>
# include "ICommand.hpp"

class Cap : public ICommand
{
	public:
		~Cap( void );

		void execute( Server*, std::string &, int );
};

#endif

