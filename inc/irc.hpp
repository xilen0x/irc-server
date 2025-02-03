#ifndef IRC_HPP
# define IRC_HPP

# include <cstring>
# include <unistd.h>
# include <cstdlib>
# include <iostream>
# include <string>

/*-----------COLORS------------*/
#define GRE "\e[1;32m"
#define RED "\e[1;31m"
#define YEL "\e[1;33m"
#define RES "\033[0m"
#define WHI "\e[1;37m"


int	 parseInput(std::string password, int port);
std::string getCurrentTime();
std::string formatIRCMessage(const std::string& message);

#endif