#include "Server.hpp"


bool Server::_Signal = false;

void handleSIGINT(int signal) {
    std::cout << "\nSIGINT (" << signal << ") received. Shutting down the server..." << std::endl;
    // Server::_Signal = true;
}


// void Server::handleSIGPIPE(int signal) {
//     std::cout << "SIGPIPE received. A client disconnected unexpectedly." << std::endl;
//     // Ignore the signal and continue running
// }

void handleSIGQUIT(int signal) {
    std::cout << "\nSIGQUIT (" << signal << ") received. Shutting down the server..." << std::endl;
    // Server::_Signal = true;
}
