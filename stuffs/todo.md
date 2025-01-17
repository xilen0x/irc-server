# ESTRUCTURA PROYECTO IRC-SERVER

## 1. Conceptos Clave para Entender el Proyecto

*   Protocolo IRC (Internet Relay Chat):

        Estudia cómo funciona, incluyendo comandos básicos (NICK, JOIN, PRIVMSG, etc.) y las respuestas.
        Familiarízate con los RFC 1459 y RFC 2812, que describen el protocolo IRC.

## Introduction
IRC is a global, distributed, real-time chat system that operates over the Internet. An
IRC network consists of a set of interconnected servers. Once users are connected to an IRC
server, they can converse with other users connected to any server in the IRC network. IRC
provides for group communication, via named channels, as well as personal communication
through “private” messages. 

An IRC network is composed of a set of nodes interconnected by virtual links in an arbitrary
topology. Each node runs a process that we will call a routing daemon. Each routing daemon
maintains a list of IRC users available to the system.

## Definitions
• **nodeID** – unique identifier that identifies an IRC server, or node. In the first project,
the nodeID for the standalone IRC server should be 1.

• **destination** – IRC nickname or channel as a null terminated character string. As
per the IRC RFC, destinations will be at most 9 characters long and may not contain
spaces.

• **IRC port** – The TCP port on the IRC server that talks to clients.

## The IRC Server
Your server will implement a subset of the original IRC protocol. The original IRC protocol
is defined in RFC 1459[3]. Because RFC 1459 omits some details that are required to imple-
ment an IRC server, we have provided an annotated version of the RFC[4]. For this project,
you should always refer to the annotated version of the RFC, not the original version.
We have chosen a subset of the protocol that will provide you with experience developing a
concurrent network application without spending an inordinate amount of time implement-
ing lots of features. Specifically, your server must implement the following commands:

### Basic Commands
• **NICK** – Give the user a nickname or change the previous one. Your server should
report an error message if a user attempts to use an already-taken nickname.

• **USER** – Specify the username, hostname, and real name of a user.

• **QUIT** – End the client session. The server should announce the client’s departure to
all other users sharing the channel with the departing client.

### Channel Commands
• **JOIN** – Start listening to a specific channel. Although the standard IRC protocol
allows a client to join multiple channels simultaneously, your server should restrict a
client to be a member of at most one channel. Joining a new channel should implicitly
cause the client to leave the current channel.

• **PART** – Depart a specific channel. Though a user may only be in one channel at a
time, PART should still handle multiple arguments. If no such channel exists or it exists
but the user is not currently in that channel, send the appropriate error message.

• **LIST** – List all existing channels on the local server only. Your server should ignore
parameters and list all channels and the number of users on the local server in each
channel.

### Advanced Commands
• **PRIVMSG** – Send messages to users. The target can be either a nickname or a
channel. If the target is a channel, the message will be broadcast to every user on
the specified channel, except the message originator. If the target is a nickname, the
message will be sent only to that user.

• **WHO** – Query information about clients or channels. In this project, your server only
needs to support querying channels on the local server. It should do an exact match on
the channel name and return the users on that channel.












#################################################################################

*   Sockets en Red:

        Aprende a usar sockets en C++ (manejo de conexiones, envío y recepción de datos).
        Comprende conceptos como TCP/IP, puertos y direcciones IP.
*   Programación Concurrente:

        Uso de select, poll o hilos para manejar múltiples clientes simultáneamente.
*   Manipulación de Cadenas:

        Parsing de mensajes para interpretar comandos y argumentos.
*   Gestión de Memoria:

        Buenas prácticas para evitar fugas y asegurar estabilidad en un servidor a largo plazo.

##  2. Diseño y Planificación

*    Definir Funcionalidades Requeridas:

    Identifica los comandos obligatorios que tu servidor debe manejar.
    Incluye autenticación, gestión de canales y mensajes privados.

*    Estructura General del Proyecto:

    Divide en módulos como servidor, cliente, manejo de comandos y parsing.

*    Diagrama de Flujo:

    Diseña cómo los mensajes fluyen entre cliente y servidor.

## 3. Configuración del Entorno

*    Configura tu entorno con las herramientas necesarias (compilador de C++, debugger, herramientas de red como netcat).
*    Asegúrate de tener una Makefile para compilar el proyecto de manera eficiente.

## 4. Desarrollo

*    Módulo por Módulo:

    -   Servidor Básico:
            Implementa la creación de sockets, bind, listen y accept.

    -   Gestión de Conexiones:
            Usa select o poll para manejar múltiples clientes.
        
    -    Parsing de Mensajes:
            Diseña una función para analizar los comandos recibidos.
        
    -    Gestión de Usuarios y Canales:
            Implementa estructuras de datos para almacenar información de usuarios y canales.
        
    -    Respuestas a Comandos:
            Agrega respuestas estándar para comandos como PING, JOIN, PRIVMSG, etc.

*    Documentación:
        Comenta el código y asegura que siga las normas de estilo de 42.

*    Pruebas Unitarias:
        Testea cada módulo antes de integrarlo.

## 5. Optimización y Depuración

    * Usa herramientas como Valgrind para detectar fugas de memoria.
    * Asegúrate de manejar correctamente los errores y excepciones.
    * Optimiza el rendimiento para soportar múltiples clientes.

## 6. Entrega y Preparación para Evaluación

    * Verifica que el proyecto cumple todos los requisitos.
    * Realiza una sesión de pruebas final con compañeros para simular un uso real.