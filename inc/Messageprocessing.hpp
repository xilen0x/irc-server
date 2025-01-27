
#ifndef MESSAGEPROCESSING_HPP
# define MESSAGEPROCESSING_HPP

# include <iostream>
# include <map>
# include "ICommand.hpp"
# include "Ping.hpp"

class Messageprocessing
{
	private:
		std::map<std::string, ICommand *>	_commands;

	public:
		Messageprocessing( void );
		~Messageprocessing( void );

		void	processMessage(std::string message); 
};

#endif
