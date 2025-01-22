# [Small IRC Server [ft_irc 42 The Network]](https://medium.com/@afatir.ahmedfatir/small-irc-server-ft-irc-42-network-7cee848de6f9)

[Github AhmedFatir](https://github.com/AhmedFatir/ft_irc)

Original Index([link](https://medium.com/@afatir.ahmedfatir/small-irc-server-ft-irc-42-network-7cee848de6f9))
- Part 1: Create all the necessary classes and methods for the project.
- Part 2: Create a socket and handle the server signals.
- Part 3: Use the poll() function to check if an event has occurred.
- Part 4: accepting new clients.
- Part 5: receive new data from a registered client

Terms:
- Sockets (types) and bind to a specific port
- listen for incoming connections
- handle client connections
- signals handling


**Socket** : Essentially, a socket is a file descriptor

> A socket is an endpoint that enables two processes to communicate with each other, either on the same machine or across a network. It acts as an interface between the application layer and the transport layer of the networking stack.


A **Sockect** must be bind with an address.

> **Don´t explain**: The remaining part is just handling the data received from the client, as required by the ft_irc subject, by writing logical code and implementing error handling. In case you are confused about the rest of the project and the basic commands that need to be handled (**PASS, NICK, USER, JOIN, PART, TOPIC, INVITE, KICK, QUIT, MODE, and PRIVMSG**).

### Clients to test server

[irssi](https://irssi.org/), [HexChat](https://hexchat.github.io/), [mIRC](https://www.mirc.com/), [WeeChat](https://weechat.org/), [LimeChat for Mac](http://limechat.net/mac/)


### IP concepts

This complentary links aren't in the article.

- [Linux IP](https://man7.org/linux/man-pages/man7/ip.7.html) Concepts for **INADDR_ANY** , **`struct sockaddr_in`** , **`struct in_addr`**	, etc.
- [netinet/in.h - Internet address family](https://pubs.opengroup.org/onlinepubs/009695399/basedefs/netinet/in.h.html)

### Functions
 
The author doesn´t describe all allowed functions. 


No mention functions , but used :

- [htons](https://man7.org/linux/man-pages/man3/htonl.3p.html) used to convert the port to network byte order (big endian)
- [inet_ntoa](https://man7.org/linux/man-pages/man3/inet_aton.3.html) used to convert the ip address to string

No mention functions and **not used** :

- [htonl](https://man7.org/linux/man-pages/man3/htonl.3p.html)
- [ntohs](https://man7.org/linux/man-pages/man3/htonl.3p.html) 
- [ntohl](https://man7.org/linux/man-pages/man3/htonl.3p.html) 
- [gethostbyname](https://man7.org/linux/man-pages/man3/gethostbyname.3.html)
- [getprotobyname](https://man7.org/linux/man-pages/man3/getprotobyname.3.html)
- [connect](https://man7.org/linux/man-pages/man2/connect.2.html)
- [getsockname](https://man7.org/linux/man-pages/man2/getsockname.2.html)
- [send](https://man7.org/linux/man-pages/man2/sendmsg.2.html)
- [fstat](https://man7.org/linux/man-pages/man2/stat.2.html)
- [close](https://man7.org/linux/man-pages/man2/close.2.html)
- [lseek](https://man7.org/linux/man-pages/man2/lseek.2.html)
- [freeaddrinfo](https://man7.org/linux/man-pages/man3/getaddrinfo.3.html)
- [getaddrinfo](https://man7.org/linux/man-pages/man3/getaddrinfo.3.html)
- [inet_addr](https://man7.org/linux/man-pages/man3/inet_aton.3.html)

#### To stop server program
- [signal](https://man7.org/linux/man-pages/man2/signal.2.html) or [sigaction](https://man7.org/linux/man-pages/man2/sigaction.2.html) to manage **CTRL+C** and **CTRL+\ **.

#### Configure server with sockets

- [socket](https://man7.org/linux/man-pages/man2/socket.2.html)
- [setsockopt](https://man7.org/linux/man-pages/man3/setsockopt.3p.html) to set options to `socket`
- [fcntl](https://man7.org/linux/man-pages/man2/fcntl.2.html) **Only valid: fcntl(fd, F_SETFL, O_NONBLOCK)** for **non-blocking** mode.i Itś uses for each *fd* acepted
- [bind](https://man7.org/linux/man-pages/man2/bind.2.html) to assign a specific address and port to a socket.
- [listen](https://man7.org/linux/man-pages/man2/listen.2.html) for passive sockets. So server can do *Passive Open Operations*.

#### Server communication

-  (Must use only once in the code) [poll](https://man7.org/linux/man-pages/man2/poll.2.html) (or equivalent) expects events from **fd list** in *timeout* limited time . Returns:
    - **0** for no events in *timeout* 
	- **-1** for error . **errno** value is activated.
	- The total number of *fd* with events.
- [accept](https://man7.org/linux/man-pages/man2/accept.2.html) for new clients and returns:
    - a new file descriptor representing the client socket
	- **-1** as error.
- [recv](https://man7.org/linux/man-pages/man2/recv.2.html) to receive data from a connected socket 

## Manage CTRL+C and CTRL+\

```cpp
    signal(SIGINT, Server::SignalHandler); //-> catch the signal (ctrl + c)
    signal(SIGQUIT, Server::SignalHandler); //-> catch the signal (ctrl + \)
```

**Server** is a class for server.

## TCP and UDP

In TCP and UDP, a port number is represented by a 16-bit unsigned integer, and there are three types of ports:

1. Ports 0 to 1023 are reserved for specific services and protocols, such as **HTTP** (port 80),**FTP** (port 21), and **SSH** (port 22). They require administrative privileges to use
2. Ports numbered 1024 to 49151 can be registered for specific purposes and are used by non-standard applications and services.
3. Dynamic or private ports (49152 to 65535) are used by client applications for outgoing connections. These ports are dynamically allocated by the operating system to clients when they initiate outgoing connections.

## Description **structs** used

Structs ( See [sockaddr, sockaddr_storage, sockaddr_in, sockaddr_in6, sockaddr_un, socklen_t, in_addr, in6_addr, in_addr_t, in_port_t, socket address](https://man7.org/linux/man-pages/man3/sockaddr.3type.html) ) :
- [struct sockaddr_in](https://man7.org/linux/man-pages/man3/sockaddr.3type.html) : struct object that contains important information about the server address
- [struct in_addr](https://man7.org/linux/man-pages/man3/sockaddr.3type.html)
- [struct pollfd](https://man7.org/linux/man-pages/man2/poll.2.html) :  structure used for monitoring file descriptors for I/O events. It’s commonly employed with the **`poll()`** system call to perform multiplexed I/O, allowing a program to efficiently wait for events on multiple file descriptors simultaneously without having to resort to blocking I/O operations.


Some interesting variables descriptions of this structs:
- **`sin_family`**: An integer representing the address family. For **IPv4**, this is typically set to **`AF_INET`**.
- **`sin_addr`**: A structure **`in_addr`** containing the **IPv4** address. This structure typically has a single member, representing the IPv4 address in network byte order.**`INADDR_ANY`** It represents “any” IP address, meaning the socket will be bound to all available network interfaces on the host.
- **`events`** A bitmask specifies the events to monitor for the given file descriptor. Common events include read, write, error, and hang-up events. like **`POLLIN`**:(any readable data available) or **`POLLHUP`**:(file descriptor was “hung up” or closed)
- **`revents`** A bitmask indicating the events that occurred for the given file descriptor. This member is typically filled in by the **`poll()`** function upon return and indicates the events that triggered the poll.


## Active and Passive sockets

![active_pasive.webp](active_pasive.webp)
Active VS Passive

### Active Socket (IRC Client) (for Bonus)

- An active socket in IRC represents the client-side connection to an IRC server. The IRC client initiates communication by connecting to the IRC server using a TCP/IP connection. Once connected, the client can send commands and messages to the server and receive responses. The IRC client socket handles user input, sends messages to the server, and processes server responses.

### Passive Socket (IRC Server)  (Used in this project)

- A passive socket in IRC represents the server-side listening socket that accepts incoming connections from IRC clients. The IRC server listens for incoming connections on a specific port, When a connection request is received from an IRC client, the server socket accepts the connection, creating a new socket for communication with that client. The IRC server socket manages multiple client connections simultaneously, handling commands and messages from each connected client and broadcasting messages to all clients as needed.

## Function Description

### socket() 

```cpp
int socket(int domain, int type, int protocol);
```

The **`socket()`** function is a system call used to create a new socket of a specified type (such as stream or datagram) and returns a file descriptor that can be used to refer to that socket in subsequent system calls.

- **`domain`**  Specifies the communication domain or address family for the socket. Common values include **`AF_INET`** for **IPv4** communication and **`AF_INET6`** for **IPv6** communication.
- **`type`** Specifies the type of communication semantics for the socket. Common values include **`SOCK_STREAM`** for **TCP** sockets (providing reliable, bidirectional, byte-stream communication) and **`SOCK_DGRAM`** for **UDP** sockets (providing datagram-oriented communication).
- **`protocol`** Specifies the specific protocol to be used with the socket. For most socket types, this argument is set to 0, indicating that the system should choose an appropriate protocol based on the specified domain and type.


### setsockopt()

```cpp
int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
```

The **`setsockopt()`** function is used to set options on a socket. These options are : **`SO_REUSEADDR`**, **`SOL_SOCKET`**, **`IPPROTO_TCP`** for TCP-specific options or **`IPPROTO_IP`** for IP-specific options, **`SO_REUSEADDR`** , **`TIME_WAIT`** 

### fcntl()

```cpp
int fcntl(int fd, int cmd, ... /* arg */ );
```

- **`fd`** is The file descriptor on which to operate.
- **`cmd`** is The operation to perform. In this case, it's **F_SETFL**, indicating that you want to set the file status flags.

**fcntl()** is used to set the **O_NONBLOCK** flag on the server socket file descriptor. This flag sets the socket to **non-blocking** mode, which means that operations such as read() and write() on the socket will return immediately, even if there is no data available to read or the write operation cannot be completed immediately. and this provides a flexible and efficient mechanism for handling I/O operations asynchronously without blocking the program’s execution.

> For instance, if you are connected to a server through the **NetCut(nc)** tool and you type something in the terminal but don't hit the send button, and then you attempt to shut down the server, you will not be able to do so, because there is a reading operation in progress.

### bind()

```cpp
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

The **`bind()`** function enables you to assign a specific address and port to a socket, thus providing it with a unique identity on the network. By associating a socket with an address and port, you enable other processes to communicate with it over the network.

He use **`struct sockaddr`** that lets manage **IPv4**,**IPv6**, and other address types supported by different protocols

### listen() for passive sockets

```cpp
int listen(int sockfd, int backlog);
```

- **`sockfd`**: The file descriptor of the socket that has been created and bound using bind(). 
- **`backlog`**: The maximum length of the queue of pending connections. This parameter determines the maximum number of connection requests that can be queued by the operating system while the server is handling existing connections.

### poll() 

```cpp
int poll(struct pollfd *fds, nfds_t nfds, int timeout);
```

- **fds**: An array of struct pollfd structures, each representing a file descriptor to be monitored.
- **nfds**: The number of elements in the **fds** array.
- **timeout**: The maximum time to wait for an event to occur, in milliseconds. A value of **-1** means wait indefinitely, **0** means return immediately, and a positive value specifies a timeout period.

The **poll()** function is used to monitor changes in the status of file descriptors. It blocks until an event occurs on one or more of the monitored file descriptors, or until the specified timeout expires.

When an event occurs (e.g., data becomes available for reading, a connection is established, or a socket becomes ready for writing) on one or more of the monitored file descriptors, the operating system notifies the **poll()** function.
If an event occurs on one or more file descriptors, **poll()** returns the number of file descriptors for which events occurred. If no events occurred before the timeout expires, **poll()** returns 0. However, if an error occurs, **poll()** returns -1 and the specific error is indicated by the errno value.
the **poll()** is designed to efficiently handle multiple file descriptors using efficient data structures and algorithms. It blocks the calling process until an event occurs, thus avoiding the need for busy waiting or polling and minimizing CPU usage.

### accept()  Accept new clients

If **accept()** succeeds, it returns a new file descriptor representing the client socket. This file descriptor is used for communication with the client.

```cpp
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

- **`sockfd`**: The file descriptor of the server socket that is listening for incoming connections.
- **`addr`**: A pointer to a **`struct sockaddr`** structure where the address of the connecting client will be stored. This allows the server to identify the IP address and port number of the client that initiated the connection.
- **`addrlen`**: A pointer to a **`socklen_t`** variable that specifies the size of the addr structure. Upon return, it will be updated with the actual size of the address stored in **`addr`**.

### recv() recive data from a socket

The **recv()** function is used in socket programming to receive data from a connected socket. It's commonly used in TCP (Transmission Control Protocol) socket communication to read data sent by the remote peer.

```cpp
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
```

- **`sockfd`**: The file descriptor of the socket from which to receive data.
- **`buf`**: A pointer to the buffer where the received data will be stored.
- **`len`**: The maximum number of bytes to receive and store in the buffer.
- **`flags`**: Optional flags to control the behavior of the **`recv()`** function (e.g., specifying additional receive options): In **`recv()`**, the flags parameter provides additional receive options for explicit control over the operation. Available flags are **`MSG_WAITALL`**, **`MSG_DONTWAIT`**, **`MSG_PEEK`**, and **`MSG_TRUNC`**. By selecting the right flags, you can tailor the receive operation to your needs, making it more efficient and versatile.
