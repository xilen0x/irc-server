#ifndef PING_HPP
# define PING_HPP

# include <iostream>
# include "ICommand.hpp"

class Ping : public ICommand
{
	private:
		bool _extractParams(Server* server, std::string command, std::string &msg, int fd);

	public:
		~Ping( void );

		void execute( Server*, std::string &, int );
};

#endif
