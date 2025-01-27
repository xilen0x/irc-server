#ifndef TOPIC_HPP
# define TOPIC_HPP

# include <iostream>
# include "ICommand.hpp"

class Topic : public ICommand
{
	public:
		~Topic( void );

		void execute( std::string & , int );
};

#endif

