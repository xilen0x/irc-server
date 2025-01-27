#ifndef NICK_HPP
# define NICK_HPP

# include <iostream>
# include "ICommand.hpp"

class Nick : public ICommand
{
	public:
		~Nick( void );

		void execute( std::string );
};

#endif

