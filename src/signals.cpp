#include "Server.hpp"

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
    return;
}

void handleSIGINT(int signal) {
    (void)signal;
    std::cout << "\nSIGINT received. Shutting down the server..." << std::endl;
    // cleanup();
    return;
}


// void Server::handleSIGPIPE(int signal) {
//     std::cout << "SIGPIPE received. A client disconnected unexpectedly." << std::endl;
//     // Ignore the signal and continue running
// }

void handleSIGQUIT(int signal) {
    (void)signal;
    std::cout << "\nSIGQUIT received. Shutting down the server..." << std::endl;
    // cleanup();
    // Server::_Signal = true;//
}
