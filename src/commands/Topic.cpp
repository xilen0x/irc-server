
#include "Topic.hpp"
#include "replies.hpp"

Topic::~Topic( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Topic::execute( Server* server, std::string &msg , int fd)
{
	std::vector<std::string>	str;
	std::vector<std::string>	splitedStrVect;
	std::string					chName;
	std::string					topic = "";
	Client						*cl;


	cl = server->getClient(fd);

//	if (isAuthenticated(server->getClient(fd), server, fd))
//	{
		std::cout << "    ----" << std::endl;
		std::cout << "TOPIC  => TODO : several cases " << msg << std::endl;
		std::cout << "TOPIC  => TODO : Check if client is auth to continue " << msg << std::endl;
		deleteRN(msg);
		splitedStrVect = splitByDoublePoint(msg);
		str = split_msgAPM(splitedStrVect[0]);
		if (str.size() == 1)
		{
			server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "TOPIC"), fd);  // 461  //Perhaps "*" must be changed
			return;
		}
		else if (str.size() > 2)
		{
			std::cout << "TODO : a lot of params =" << splitedStrVect[0] << std::endl;
			return;
		}
		std::cout << "TODO : str[1]=" << str[1] << std::endl;
		/*
		 * si  No empieza con # o & error -> ERR_NOSUCHCHANNEL(nickname, channelname) //403
		 *
		 * Mirar el nombre a partir del segundo char (evitar el primer # ó &)
		 * Si canal no esta en la lista de canales -> ERR_NOSUCHCHANNEL nickname, channelname) //403
		 * Si el cliente no está en este canal -> ERR_NOTONCHANNEL(nickname, channelname) //442
		 * Si el topic is protected -> ERR_CHANOPRIVSNEEDED(nickname, channelname) //482
		 *
		 */
		if (splitedStrVect.size() == 2)
		{
			topic = splitedStrVect[1];
			std::cout << "TODO : topic=" << topic << std::endl;
		}
		chName = str[1];
		for (size_t i=0; i < str.size(); ++i)
			std::cout << "- str[" << i << "]=" << str[i] << std::endl;
		if (chName[0] != '#' || chName[0] != '&')
		{
			server->sendResp(ERR_NOSUCHCHANNEL(cl->getNick(), chName), fd);
			return;
		}
		std::cout << "    ----" << std::endl;
//	}
}
