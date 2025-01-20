#include "Server.hpp"

//constructors
// Server::Server(){}

Server::Server(std::string serverName, std::string password, int port) :_serverName(serverName), _password(password), _port(port), _fdServer(-1) { }

//createSocket
void Server::createSocket()
{
    struct	sockaddr_in socketAddress;//estructura que almacena la dirección del socket (IP y puerto) para una conexión IPv4.
    int                 enableReuseAddr;
    // Crear y configurar el socket
	memset(socketAddress.sin_zero, 0, sizeof(socketAddress.sin_zero));//Rellena con ceros el resto de la estructura sockaddr_in.
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

void Server::listenSocket()
{
    // Escuchar conexiones entrantes
    if (listen(_fdServer, SOMAXCONN) == -1) // SOMAXCONN: n° máx de conexiones pendientes en la cola de conexiones.
	{
        throw std::runtime_error("Failed to listen on socket");
    }
    std::cout << "Server is now listening for incoming connections." << std::endl;
}

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

// loop	(standar c++98)
void Server::loop()
{
    int                 pollRet;
    struct sockaddr_in  clientAddress;
    socklen_t           clientAddressSize;
    int                 fdClient;
    struct pollfd       pollFds[1];
    char                buffer[1024];
    int                 bytesRead;

    while (true) {
        // Copiar el vector de monitoreo a un array de pollfd
        std::copy(_fdsClients.begin(), _fdsClients.end(), pollFds);

        // Esperar por eventos en los descriptores de archivo
        pollRet = poll(pollFds, _fdsClients.size(), -1);
        if (pollRet == -1) {
            throw std::runtime_error("Failed to poll for events");
        }

        // Iterar sobre los descriptores de archivo para determinar el evento
        for (std::vector<struct pollfd>::size_type i = 0; i < _fdsClients.size(); i++) { // Tipo corregido
            if (pollFds[i].revents & POLLIN) {
                // Nuevo cliente
                if (pollFds[i].fd == _fdServer) {
                    clientAddressSize = sizeof(clientAddress);
                    fdClient = accept(_fdServer, reinterpret_cast<struct sockaddr*>(&clientAddress), &clientAddressSize);
                    if (fdClient == -1) {
                        throw std::runtime_error("Failed to accept connection");
                    }
                    // Configurar el nuevo cliente como no bloqueante
                    if (fcntl(fdClient, F_SETFL, O_NONBLOCK) == -1) {
                        throw std::runtime_error("Failed to set option (O_NONBLOCK) on client socket");
                    }
                    // Agregar el nuevo cliente al vector de monitoreo
                    struct pollfd newClient;
                    newClient.fd = fdClient;
                    newClient.events = POLLIN;
                    _fdsClients.push_back(newClient);
                    std::cout << "New client connected." << std::endl;
                }
                // Cliente existente
                else {
                    // Leer datos del cliente
                    bytesRead = recv(pollFds[i].fd, buffer, sizeof(buffer), 0);
                    if (bytesRead == -1) {
                        throw std::runtime_error("Failed to read data from client");
                    }
                    else if (bytesRead == 0) {
                        // Cliente desconectado
                        close(pollFds[i].fd);
                        _fdsClients.erase(_fdsClients.begin() + i);
                        std::cout << "Client disconnected." << std::endl;
                    }
                    else {
                        // Imprimir los datos recibidos
                        buffer[bytesRead] = '\0';
                        std::cout << "Received: " << buffer << std::endl;
                    }
                }
            }
        }
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

//getters and setters
// ...


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

std::string	Server::getServerName( void ) const { return (this->_serverName); }
std::string	Server::getPassword( void ) const { return (this->_password); }
int 		Server::getPort( void ) const { return (this->_port); };
int			Server::getFdServer( void ) const { return (this->_fdServer); };