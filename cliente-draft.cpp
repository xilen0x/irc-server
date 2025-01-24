//*************************** CLIENT ***************************//

#include <iostream>     // Para entrada y salida estándar
#include <cstring>      // Para usar funciones como memset
#include <sys/socket.h> // Para funciones de sockets (socket, connect, etc.)
#include <arpa/inet.h>  // Para inet_pton (convertir IP a formato binario)
#include <unistd.h>     // Para funciones como close()

#define PORT 8080       // Puerto al que se conectará el cliente

int main() {
    int sock_fd = 0;                  // Descriptor de archivo para el socket
    struct sockaddr_in serv_addr;  // Estructura para almacenar la dirección del servidor
    const char* mensaje = "Hola desde el cliente"; // Mensaje que se enviará al servidor
    char buffer[1024] = {0};       // Buffer para recibir la respuesta del servidor

    
    std::string exit = "";
    while (exit != "exit")
    {
        // Crear un socket usando IPv4 (AF_INET) y TCP (SOCK_STREAM)
        if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            std::cerr << "Socket falló" << std::endl; // Mensaje de error si el socket no se crea
            return -1; // Termina el programa con error
        }

        // Configurar la dirección del servidor
        serv_addr.sin_family = AF_INET;        // Familia de direcciones IPv4
        serv_addr.sin_port = htons(PORT);     // Puerto (convertido a big-endian)

        // Convertir la dirección IP a formato binario y asignarla a la estructura
        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
            std::cerr << "Dirección inválida" << std::endl; // Error si la IP no es válida
            return -1;
        }
        std::string option = "";
        // Conectar al servidor
        if (connect(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
            std::cerr << "Conexión falló" << std::endl; // Error si no se puede conectar
            return -1;
        }

        // Enviar mensaje al servidor
        send(sock_fd, mensaje, strlen(mensaje), 0); // Envía el mensaje al servidor
        std::cout << "Mensaje enviado" << std::endl;

        // Leer respuesta del servidor
        read(sock_fd, buffer, 1024); // Lee hasta 1024 bytes del servidor
        std::cout << "Respuesta del servidor: " << buffer << std::endl;

        //opcion de salida
        std::cout << "Escribe 'exit' para salir" << std::endl;
        std::cin >> option;
        if (option == "exit")
            exit = "exit";
    }
    // Cerrar el socket
    close(sock_fd);

    return 0; // Termina el programa
}
