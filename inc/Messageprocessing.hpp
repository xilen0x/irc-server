
#ifndef MESSAGEPROCESSING_HPP
# define MESSAGEPROCESSING_HPP

# include <iostream>
# include <map>
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
# include "Test.hpp"
# include <vector>

class Messageprocessing
{
	private:
		std::map<std::string, ICommand *>	_commands;

	public:
		Messageprocessing( void );
		~Messageprocessing( void );

		void	processMessage(std::string message, int fd);
		std::vector<std::string> split_msg(std::string &msg);
};

#endif
