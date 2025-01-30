
#include "Cap.hpp"
// #include "Messageprocessing.hpp"

void Cap::execute( Server* server, std::string &msg, int fd )
{
	(void)msg;
	(void)server;
	// (void)fd;
	// size_t j = 0;

	send(fd, "CAP * LS :\r\n", 12, 0); //empty CAP LS
	// send(fd, "CAP * LS :multi-prefix\r\n", 24, 0);//Permite ver múltiples prefijos de usuario (@%+).
	// std::cout << YEL << "Cap command executed" << RES << std::endl;

    // if (words.size() > 2)
	// {
	// 	for (size_t i = 0; i < words.size(); i++)
	// 	{
	// 		if (words[i] == "PASS")
	// 		{
	// 			messageProcesing.processMessage(server, msg, fd);
	// 			std::cout << "PASS" << std::endl;
	// 		}
	// 		// else if (words[i] == "NICK")
	// 		// {
	// 		// 	messageProcesing.processMessage(server, words[i + 1], fd);
	// 		// }
	// 		// else if (words[i] == "USER")
	// 		// {
	// 		// 	messageProcesing.processMessage(server, words[i + 1], fd);
	// 		// }
	// 		// else
	// 		// {
	// 		// 	std::cout << "something went wrong" << std::endl;
	// 		// }
			
	// 	}
	// }
    // {
	// 	if (i + 2 < words.size())
	// 	{
    //     	std::cout << "Word " << j << ": " << words[j] << std::endl;
	// 		// messageProcesing.processMessage(server, words[i + 2], fd);
	// 	}
		
	// 	j = i + 2;
    // }
}

Cap::~Cap( void ) {};