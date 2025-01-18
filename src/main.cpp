#include <iostream>
#include "../inc/Messageprocessing.hpp"


int main()
{
	Messageprocessing	messageProcesing;

    std::cout << "Execute Messageprocessing !" << std::endl;

	messageProcesing.processMessage("Hola amigo!!");
    return (0);
}
