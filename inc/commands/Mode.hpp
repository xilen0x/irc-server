#ifndef MODE_HPP
# define MODE_HPP

# include <iostream>
# include "ICommand.hpp"

class Mode : public ICommand
{
	public:
		~Mode( void );
		// void execute( std::string & , int );
		void execute( Server*, std::string &, int );
};

#endif

