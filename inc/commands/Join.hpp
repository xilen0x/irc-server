#ifndef JOIN_HPP
# define JOIN_HPP

# include <iostream>
# include "ICommand.hpp"

class Join : public ICommand
{
	public:
		~Join( void );

		void execute( std::string & , int );
};

#endif

