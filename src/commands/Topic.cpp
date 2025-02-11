
#include "Topic.hpp"
#include "replies.hpp"

Topic::~Topic( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Topic::execute( Server* server, std::string &msg , int fd)
{
	std::vector<std::string>	str;
	std::vector<std::string>	splitedStrVect;

//	if (isAuthenticated(server->getClient(fd), server, fd))
//	{
		std::cout << "    ----" << std::endl;
		std::cout << "TOPIC  => TODO : several cases " << msg << std::endl;
		std::cout << "TOPIC  => TODO : Check if client is auth to continue " << msg << std::endl;
		deleteRN(msg);
		splitedStrVect = splitByDoublePoint(msg);
		str = split_msgAPM(splitedStrVect[0]);
		if (str.size() != 2)
		{
   	     server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "TOPIC"), fd);  // 461  //Perhaps "*" must be changed
   	     return;
		}
		std::cout << "TODO : str[1]=" << str[1] << std::endl;
		if (splitedStrVect.size() == 2)
			std::cout << "TODO : topic=" << splitedStrVect[1] << std::endl;
		std::cout << "    ----" << std::endl;
//	}
}
