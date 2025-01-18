#include <iostream>
#include "../inc/Messageprocessing.hpp"


int main()
{
	Messageprocessing	messageProcesing;

    std::cout << "Execute Messageprocessing !" << std::endl;

	messageProcesing.processMessage("tokenPing!!");
    return (0);
}
