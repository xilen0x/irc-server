
#include "Messageprocessing.hpp"

#define PASS "PASS"
#define PING "PING"


// Public

Messageprocessing::Messageprocessing( void )
{
	std::cout << "Messageprocessing => Creating _command Map" << std::endl;
	this->_commands[PASS] = new Pass();
	this->_commands[PING] = new Ping();
}

Messageprocessing::~Messageprocessing( void )
{
	std::cout << "~Messageprocessing => Delete _commands" << std::endl;
	for (std::map<std::string, ICommand*>::iterator it = _commands.begin(); it != _commands.end(); ++it)
    {
        delete it->second;
    } 
}

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void	Messageprocessing::processMessage(std::string message)
{
	// TODO
	//
	// 1 - Parssing message
	// 2 - Detect COMMAND
	// 3 - Execute COMMAND
	
	std::cout << "processMessage(std:string message) with message = " << message << std::endl;
	std::cout << "----- PING test -----" << std::endl;
	this->_commands[PING]->execute(message);
	std::cout << "----- end PING test -----" << std::endl;   
}
