// //*************************** SERVER *************************** */

// #include <iostream>     // Para usar entrada y salida estándar
// #include <cstring>      // Para usar funciones como memset que sirve para llenar de 0s un buffer
// #include <sys/socket.h> // Para funciones de sockets (socket, bind, etc.)
// #include <netinet/in.h> // Para estructuras de direcciones como sockaddr_in
// #include <unistd.h>     // Para funciones como close()
// #include <vector>      // Para almacenar los sockets de los clientes
// #include <thread>      // Para manejar clientes en hilos separados

// #define PORT 8080       // Puerto en el que el servidor escuchará conexiones

// int main() {
//     int server_fd, new_socket; // Descriptores de archivo para el servidor y el cliente
//     struct sockaddr_in address; // Estructura para almacenar la dirección del servidor
//     int opt = 1;                // Opción para reutilizar el puerto
//     int addrlen = sizeof(address); // Tamaño de la estructura sockaddr_in
//     char buffer[1024] = {0};    // Buffer para almacenar datos recibidos del cliente

//     // Crear un socket usando IPv4 (AF_INET) y TCP (SOCK_STREAM)
//     if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
//         perror("Socket falló"); // Muestra un mensaje de error si la creación falla
//         exit(EXIT_FAILURE);     // Termina el programa con error
//     }

//     // Configurar el socket para reutilizar dirección y puerto
//     if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
//         perror("setsockopt falló"); // Error al configurar opciones del socket
//         exit(EXIT_FAILURE);
//     }

//     // Configurar la dirección del servidor
//     address.sin_family = AF_INET;           // Familia de direcciones IPv4
//     address.sin_addr.s_addr = INADDR_ANY;   // Aceptar conexiones de cualquier IP
//     address.sin_port = htons(PORT);         // Puerto (convertido a big-endian)

//     // Asociar el socket al puerto especificado
//     if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
//         perror("Bind falló"); // Error si no se puede asociar el socket
//         exit(EXIT_FAILURE);
//     }

//     // Escuchar conexiones entrantes (cola de hasta 3 conexiones pendientes)
//     if (listen(server_fd, 3) < 0) {
//         perror("Listen falló"); // Error al intentar escuchar
//         exit(EXIT_FAILURE);
//     }

//     std::cout << "Esperando conexión..." << std::endl;

//     // Aceptar una conexión entrante
//     if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
//         perror("Accept falló"); // Error si no se puede aceptar la conexión
//         exit(EXIT_FAILURE);
//     }

//     // Leer datos enviados por el cliente
//     read(new_socket, buffer, 1024); // Lee hasta 1024 bytes del cliente
//     std::cout << "Mensaje recibido: " << buffer << std::endl;

//     // Responder al cliente
//     const char* mensaje = "Hola desde el servidor";
//     send(new_socket, mensaje, strlen(mensaje), 0); // Envía el mensaje al cliente

//     // Cerrar la conexión con el cliente y el socket del servidor
//     close(new_socket); 
//     close(server_fd);

//     return 0; // Termina el programa
// }

#include <iostream>// Para entrada y salida estándar
#include <cstring>// Para usar funciones como memset
#include <sys/socket.h>// Para funciones de sockets (socket, bind, etc.)
#include <netinet/in.h>// Para estructuras de direcciones como sockaddr_in
#include <unistd.h>// Para funciones como close()
#include <poll.h>// Para usar la función poll
#include <vector>// Para almacenar los descriptores de archivo de los clientes
#include <fcntl.h>// Para funciones como fcntl
#include <map>// Para almacenar los datos de los clientes

#define PORT 8080
#define MAX_CLIENTS 100
#define BUFFER_SIZE 1024

// Función para configurar un socket en modo no bloqueante
void setNonBlocking(int socket) {
    int flags = fcntl(socket, F_GETFL, 0);
    fcntl(socket, F_SETFL, flags | O_NONBLOCK);
}

int main() {
    int server_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];
    std::vector<pollfd> poll_fds;  // Vector para `poll`

    // Crear socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket falló");
        exit(EXIT_FAILURE);
    }

    // Configurar el socket para reutilizar dirección y puerto
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt falló");
        exit(EXIT_FAILURE);
    }

    // Configurar dirección del servidor
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Asociar el socket al puerto
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind falló");
        exit(EXIT_FAILURE);
    }

    // Escuchar conexiones
    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("Listen falló");
        exit(EXIT_FAILURE);
    }

    // Configurar socket en modo no bloqueante
    setNonBlocking(server_fd);

    // Agregar el socket del servidor a la lista de `poll`
    pollfd server_poll_fd = {server_fd, POLLIN, 0};//POLLIN: Se activa cuando hay datos para leer
    poll_fds.push_back(server_poll_fd);//Agrega el socket del servidor a la lista de `poll`

    std::cout << "Servidor escuchando en el puerto " << PORT << "..." << std::endl;

    while (true) {
        // Llamada a `poll` para monitorear actividad
        int activity = poll(poll_fds.data(), poll_fds.size(), -1);
        if (activity < 0) {
            perror("Error en poll");
            continue;
        }

        // Verificar actividad en cada descriptor
        for (size_t i = 0; i < poll_fds.size(); ++i) {
            if (poll_fds[i].revents & POLLIN) // Se activa cuando hay datos para leer
            {
                // Nueva conexión en el socket del servidor
                if (poll_fds[i].fd == server_fd) {
                    int new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
                    if (new_socket < 0) {
                        perror("Accept falló");
                        continue;
                    }

                    std::cout << "Nuevo cliente conectado: " << new_socket << std::endl;

                    // Configurar el nuevo socket en modo no bloqueante
                    setNonBlocking(new_socket);

                    // Agregar nuevo socket a la lista de `poll`
                    pollfd client_poll_fd = {new_socket, POLLIN, 0};
                    poll_fds.push_back(client_poll_fd);
                } 
                // Datos desde un cliente existente
                else {
                    int client_socket = poll_fds[i].fd;//Obtiene el descriptor del cliente
                    int bytes_read = read(client_socket, buffer, BUFFER_SIZE);
                    if (bytes_read <= 0) {
                        // Cliente desconectado
                        std::cout << "Cliente desconectado: " << client_socket << std::endl;
                        close(client_socket);
                        poll_fds.erase(poll_fds.begin() + i);
                        --i;  // Ajustar índice después de eliminar
                    } else {
                        // Procesar mensaje del cliente
                        buffer[bytes_read] = '\0';
                        std::cout << "Mensaje del cliente " << client_socket << ": " << buffer << std::endl;

                        // Responder al cliente
                        const char* respuesta = "Mensaje recibido por el servidor.";
                        send(client_socket, respuesta, strlen(respuesta), 0);
                    }
                }
            }
        }
    }

    close(server_fd);
    return 0;
}
//*************************** SERVER *************************** */