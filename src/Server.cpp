#include "../inc/Server.hpp"

//constructors
Server::Server()
{}

Server::Server(int port, std::string password) : _port(port), _password(password), _fdServer(-1)
{}

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
    if (listen(_fdServer, SOMAXCONN) == -1) {
        throw std::runtime_error("Failed to listen on socket");
    }
    std::cout << "Server is now listening for incoming connections." << std::endl;
}

void Server::fillPollfd()
{
    // Configurar pollfd y agregar al vector de monitoreo
    struct pollfd serPoll;
    
    serPoll.fd = _fdServer;
    serPoll.events = POLLIN;
    _pollFds.push_back(serPoll);
}

void Server::serverConnected()
{
    // Mensajes informativos de estado
    std::cout << "Server successfully connected on port " << _port << "." << std::endl;
}


void Server::clean()
{
    // Cerrar el socket y limpiar recursos
    if (_fdServer != -1) {
        close(_fdServer);
        _fdServer = -1;
    }
    std::cout << "Server resources cleaned up." << std::endl;
}


// loop	
void Server::loop()
{

	//poll

	//accept

	//recv

	//send

	//close
}

//getters and setters
// ...


Server::~Server()
{
    clean();
}