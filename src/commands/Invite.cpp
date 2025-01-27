
#include "Invite.hpp"

Invite::~Invite( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Invite::execute( std::string &msg, int fd )
{
	std::cout << "    ----" << std::endl;
	std::cout << "INVITE  => TODO with fd=" << fd << " and message " << msg << std::endl;
	std::cout << "    ----" << std::endl;
}
