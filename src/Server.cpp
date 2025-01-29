#include "Server.hpp"
#include <arpa/inet.h>//para inet_ntoa que convierte una direccion ip en una cadena
#include "Messageprocessing.hpp"

Server::Server(std::string serverName, std::string password, int port) :_serverName(serverName), _password(password), _port(port), _fdServer(-1)
{
	// std::cout << "Server() => Set initial values" << std::endl;
}

//Function that creates the socket(_fdServer) and configures it.
void Server::createSocket()
{
    struct	sockaddr_in socketAddress;//estructura que almacena la dirección del socket (IP y puerto) para una conexión IPv4.
    int                 enableReuseAddr;
    
    // Crear y configurar el socket
	std::memset(socketAddress.sin_zero, 0, sizeof(socketAddress.sin_zero));//Rellena con ceros el resto de la estructura sockaddr_in.
	socketAddress.sin_family = AF_INET;//Especifica que el socket usará el protocolo IPv4.
	socketAddress.sin_port = htons(_port);//Establece el puerto del socket, convirtiéndolo a formato de red (big-endian) usando htons.
	socketAddress.sin_addr.s_addr = INADDR_ANY;//Establece la dirección IP del socket, en este caso, INADDR_ANY, que indica que el socket escuchará en todas las interfaces de red.

    // Crear el df para el socket
	_fdServer = socket(AF_INET, SOCK_STREAM, 0); 
	if (_fdServer == -1)
		throw(std::logic_error("Failed to create socket"));

    // Configurar la reutilización de direcciones
	enableReuseAddr = 1;
	if(setsockopt(_fdServer, SOL_SOCKET, SO_REUSEADDR, &enableReuseAddr, sizeof(enableReuseAddr)) == -1) // configuramos el socket con SO_REUSEADDR para poder reutilizar puertos o ips
		throw(std::runtime_error("Failed to set option (SO_REUSEADDR) on socket"));

    // Configurar el socket como no bloqueante
	if (fcntl(_fdServer, F_SETFL, O_NONBLOCK) == -1)
		throw(std::runtime_error("Failed to set option (O_NONBLOCK) on socket"));

    // Vincular el socket a la dirección y puerto especificados
    if (bind(_fdServer, reinterpret_cast<struct sockaddr*>(&socketAddress), sizeof(socketAddress)) == -1) {
        throw std::runtime_error("Failed to bind socket");
    }
    std::cout << "Socket created successfully." << std::endl;
}

//Function that listens for incoming connections.
void Server::listenSocket()
{
    // Escuchar conexiones entrantes
    if (listen(_fdServer, SOMAXCONN) == -1) // SOMAXCONN: n° máx de conexiones pendientes en la cola de conexiones.
	{
        throw std::runtime_error("Failed to listen on socket");
    }
    std::cout << "Server is now listening for incoming connections." << std::endl;
}

//Function that fills the pollfd structure and adds it to the monitoring vector.
void Server::fillPollfd()
{
    // Configurar pollfd y agregar al vector de monitoreo
    struct pollfd serPoll;
    
    serPoll.fd = _fdServer;//Establece el descriptor de archivo a monitorear.
    serPoll.events = POLLIN;//Establece los eventos a monitorear en el descriptor de archivo.
    _fdsClients.push_back(serPoll);//Agrega el pollfd al vector de monitoreo.
    std::cout << "Server successfully connected on port " << _port << "." << std::endl;
	std::cout << "Waiting for incoming connections..." << std::endl;
}

// Function to accept a new client connection
void Server::acceptClient()
{
        struct sockaddr_in  clientAddress;
        socklen_t           clientAddressSize;
        int                 connectionSocket;
        struct pollfd       clientPoll;
        Client              newClient;

        clientAddressSize = sizeof(clientAddress);
        connectionSocket = accept(_fdServer, (struct sockaddr*)&clientAddress, &clientAddressSize);
        if (connectionSocket == -1) {
            throw std::runtime_error("Failed to accept new client");
        }

        // Configure the client socket as non-blocking
        if (fcntl(connectionSocket, F_SETFL, O_NONBLOCK) == -1) {
            throw std::runtime_error("Failed to set option (O_NONBLOCK) on client socket");
        }

        // Add the client to the list of monitored FDs
        clientPoll.fd = connectionSocket;//
        clientPoll.events = POLLIN;
        clientPoll.revents = 0;

        newClient.setFdClient(connectionSocket);
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

// Receive data from the client
void Server::receiveData(int fd)
{
    char                buffer[1024];
    int                 bytesRead;
    Messageprocessing   messageProcesing;
    
    bytesRead = recv(fd, buffer, sizeof(buffer), 0);
    if (bytesRead == -1) {
        throw std::runtime_error("Failed to receive data from client");
    }
    else if (bytesRead == 0) {
        clearClients(fd, "Client disconnected\n");
    }
    else {
        buffer[bytesRead] = '\0';
        std::cout << "Received data: " << buffer << std::endl;
        messageProcesing.processMessage(this, buffer, fd);
    }
}

//Function that loops to monitor events on the fd.
void Server::loop()
{
    while (true)
    {
        int pollRet;  // Stores the return value of the poll() function
        int revents;  // Stores the events that occurred in the fd

        // Wait for events on the file descriptors
        pollRet = poll(_fdsClients.data(), _fdsClients.size(), -1);
        if (pollRet == -1) {
            throw std::runtime_error("The function poll() failed");
        }

        // Iterate over the file descriptors to determine the event
        for (size_t i = 0; i < _fdsClients.size(); i++)
        {
            revents = _fdsClients[i].revents;

            // If no events, skip to the next iteration
            if (revents == 0) 
                continue;

            // Handle errors or unexpected disconnections
            if ((revents & POLLERR) == POLLERR || (revents & POLLHUP) == POLLHUP) 
            {
                std::cout << "Socket error or client disconnection\n";
                clearClients(_fdsClients[i].fd, "Client disconnected\n");
            }
            else if (revents & POLLIN) {  // There is data to read
                if (_fdsClients[i].fd == _fdServer) {  // New incoming connection
                    acceptClient();
                }
                else {  // Message from an existing client
                    receiveData(_fdsClients[i].fd);
                }
                // Mark all fds as ready to write
                for (size_t j = 1; j < _fdsClients.size(); j++) {
                    _fdsClients[j].events |= POLLOUT;
                }
            }
        }
    }
}
 
void Server::runServer()
{
	createSocket();
	listenSocket();
	fillPollfd();
	loop();
}

void Server::sendResp(std::string resp, int fd)
{
	if(send(fd, resp.c_str(), resp.size(), 0) == -1)
		std::cerr << "Response failed!" << std::endl;
}

Server::~Server( void )
{
	// TODO : Close connections if are open 
	
	// std::cout << "------ ~Server() => Clear _fdServer, _clients, _channels" << std::endl;
	this->_fdsClients.clear();
	this->_clients.clear();
	this->_channels.clear();
	// std::cout << "------ ~Server() => End Clear _fdServer, _clients, _channels" << std::endl;
}

//-----------------------------Getters & Setters-----------------------------//
std::string	Server::getServerName( void ) const { return (this->_serverName); }
std::string	Server::getPassword( void ) const { return (this->_password); }
int 		Server::getPort( void ) const { return (this->_port); };
int			Server::getFdServer( void ) const { return (this->_fdServer); };
std::vector<Channel> Server::getChannels( void ) const{ return (this->_channels); }
std::vector<Client> Server::getClients( void ) const { return (this->_clients); }

void 		Server::addClient( Client newClient ) { this->_clients.push_back(newClient); }
void 		Server::addChannel( Channel newChannel ){ this->_channels.push_back(newChannel); }
