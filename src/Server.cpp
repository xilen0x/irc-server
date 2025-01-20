#include "Server.hpp"

Server::Server(std::string serverName, std::string password, int port) :_serverName(serverName), _password(password), _port(port), _fdServer(-1) { }

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
                clearClients(_fdsClients[i].fd, "Client disconnected\n", _fdsClients);
            }
            else if (revents & POLLIN) {  // There is data to read
                if (_fdsClients[i].fd == _fdServer) {  // New incoming connection
                    acceptNewClient(_fdServer, _fdsClients);
                }
                else {  // Message from an existing client
                    receiveNewData(_fdsClients[i].fd, _fdsClients);
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
	// clean();
}

Server::~Server( void )
{
	std::cout << "~Server => TODO" << std::endl;
}

//getters and setters
std::string	Server::getServerName( void ) const { return (this->_serverName); }
std::string	Server::getPassword( void ) const { return (this->_password); }
int 		Server::getPort( void ) const { return (this->_port); };
int			Server::getFdServer( void ) const { return (this->_fdServer); };