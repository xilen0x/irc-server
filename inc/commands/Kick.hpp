#ifndef KICK_HPP
# define KICK_HPP

# include <iostream>
# include "ICommand.hpp"

class Kick : public ICommand
{
	public:
		~Kick( void );

		void execute( std::string );
};

#endif

