#include "Server.hpp"
#include <arpa/inet.h>//para inet_ntoa que convierte una direccion ip en una cadena

    // Function to accept a new client connection
    void Server::acceptClient()
    {
        struct sockaddr_in  clientAddress;
        socklen_t           clientAddressSize;
        int                 fdClient;
        struct pollfd       clientPoll;
        Client              newClient;

        clientAddressSize = sizeof(clientAddress);
        fdClient = accept(_fdServer, (struct sockaddr*)&clientAddress, &clientAddressSize);
        if (fdClient == -1) {
            throw std::runtime_error("Failed to accept new client");
        }

        // Configure the client socket as non-blocking
        if (fcntl(fdClient, F_SETFL, O_NONBLOCK) == -1) {
            throw std::runtime_error("Failed to set option (O_NONBLOCK) on client socket");
        }

        // Add the client to the list of monitored FDs
        clientPoll.fd = fdClient;//
        clientPoll.events = POLLIN;
        clientPoll.revents = 0;

        newClient.setFdClient(fdClient);
        newClient.setIpClient(inet_ntoa(clientAddress.sin_addr));
        _clients.push_back(newClient);
        _fdsClients.push_back(clientPoll);
        std::cout << "New client connected\n";
    }

    // Function to remove a client based on its file descriptor
    void Server::clearClients(int fd, std::string msg)
    {
        // Manual find-if loop to find the client based on fd
        std::vector<struct pollfd>::iterator it = _fdsClients.begin();
        for (; it != _fdsClients.end(); ++it) {
            if (it->fd == fd) {
                break;  // Found the client
            }
        }

        // If found, erase the client from the list
        if (it != _fdsClients.end()) {
            _fdsClients.erase(it);
        }
        
        // Close the socket of the client
        close(fd);
        std::cout << msg;
    }

    void Server::receiveData(int fd)
    {
        // Receive data from the client
        char buffer[1024];
        int bytesRead = recv(fd, buffer, sizeof(buffer), 0);
        if (bytesRead == -1) {
            throw std::runtime_error("Failed to receive data from client");
        }
        else if (bytesRead == 0) {
            clearClients(fd, "Client disconnected\n");
        }
        else {
            buffer[bytesRead] = '\0';
            std::cout << "Received data: " << buffer << std::endl;
        }

        
    }

    // void Server::clean()
    // {
    //     // Cerrar el socket y limpiar recursos
    //     if (_fdServer != -1) {
    //         close(_fdServer);
    //         _fdServer = -1;
    //     }
    //     std::cout << "Server resources cleaned up." << std::endl;
    // }

    int parseInput(std::string serverName, std::string password, int port)
    {
        (void)serverName;
        (void)password;
        
        if (port <= 0 || port > 65535)
        {
            std::cerr << "Invalid port number." << std::endl;
            return (1);
        }
        //... other checks





        return (0);
    }