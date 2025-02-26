
#ifndef MESSAGEPROCESSING_HPP
# define MESSAGEPROCESSING_HPP

# include <algorithm>
# include <cctype>
# include <iostream>
# include <map>
# include <vector>
# include <sstream>
# include "ICommand.hpp"
# include "Cap.hpp"
# include "Invite.hpp"
# include "Join.hpp"
# include "Kick.hpp"
# include "Mode.hpp"
# include "Nick.hpp"
# include "Pass.hpp"
# include "Ping.hpp"
# include "Privmsg.hpp"
# include "Quit.hpp"
# include "Topic.hpp"
# include "User.hpp"

class Messageprocessing
{
	private:
		std::map<std::string, ICommand *>	_commands;

	public:
		Messageprocessing( void );
		~Messageprocessing( void );

		void processMessage(Server* server, std::string message, int fd);
};

#endif
