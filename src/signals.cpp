#include "Server.hpp"


bool Server::_Signal = false;

void cleanup() {

    Server server;
    std::cout << "Cerrando conexiones..." << std::endl;

    // Notificar a los clientes antes de cerrar
    std::string msg = "Servidor cerrándose. Adiós!\n";
    for (size_t i = 0; i < server.getClients().size(); ++i) {
        server.sendResp(msg, server.getClients()[i].getFdClient());
        close(server.getClients()[i].getFdClient());
    }

    // Cerrar el socket del servidor
    close(server.getFdServer());
    std::cout << "Conexiones cerradas." << std::endl;
}

void handleSIGINT(int signal) {
    std::cout << "\nSIGINT (" << signal << ") received. Shutting down the server..." << std::endl;
    cleanup();
    Server::_Signal = true;
}


// void Server::handleSIGPIPE(int signal) {
//     std::cout << "SIGPIPE received. A client disconnected unexpectedly." << std::endl;
//     // Ignore the signal and continue running
// }

void handleSIGQUIT(int signal) {
    std::cout << "\nSIGQUIT (" << signal << ") received. Shutting down the server..." << std::endl;
    // Server::_Signal = true;
}
