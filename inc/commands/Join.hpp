#ifndef JOIN_HPP
# define JOIN_HPP

# include <iostream>
# include "ICommand.hpp"

class Server;

class Join : public ICommand
{
	public:
		~Join( void );

		void execute(Server* server, std::string &msg , int fd);
		bool parseJoin(Server* server, std::vector<std::pair<std::string, std::string> >& parVec, std::string &msg, int fd);
};

#endif
