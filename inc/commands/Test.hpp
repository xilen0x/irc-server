#pragma once

# include <iostream>
# include "ICommand.hpp"

class Test : public ICommand
{
	public:
		~Test( void );

		void execute( std::string& , int );
};