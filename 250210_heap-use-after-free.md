
Posible causa: 
Usar el formato `user 2 * 0 :2d`  en lugar de `user 2 0 * :2u`

En un cliente tenemos :

```c++
pass hola
nick uno
user 1 * 0 :1u
:ircserv 001  :Welcome to the IRC Network, UNO!
:ircserv 002  :Your host is ircserv, running version 1.0
:ircserv 003  :This server was created on 2025-02-03
join #test
16:16 -!- :UNO!1 * 0 :1u@127.0.0.1 JOIN #test
16:16 -!- : 353 UNO @ #test :@UNO
16:16 -!- : 366 UNO #test :END of /NAMES list
```

En otro cliente , al hacer `join #test`se produce el error.

```c++
pass hola
nick dos
user 2 * 0 :2d
:ircserv 001  :Welcome to the IRC Network, DOS!
:ircserv 002  :Your host is ircserv, running version 1.0
:ircserv 003  :This server was created on 2025-02-03
join #test
```
Y en el server:

```c++
Buffer size: 15
line 0: user 2 * 0 :2d
Received data: join #test

Buffer size: 11
line 0: join #test
JOIN processing...
antes del FOR  i
bucle FOR i=0
FOR j=0
DOS has been added in _memClients map!
processJoin!
LLega 1!
=================================================================
==3200771==ERROR: AddressSanitizer: heap-use-after-free on address 0x611000000078 at pc 0x000000438294 bp 0x7fff52f4f3f0 sp 0x7fff52f4ebb0
READ of size 3 at 0x611000000078 thread T0
    #0 0x438293 in memcpy (/home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/ircserv+0x438293)
    #1 0x7f793f74e123 in void std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_construct<char*>(char*, char*, std::forward_iterator_tag) (/lib/x86_64-linux-gnu/libstdc++.so.6+0x14f123)
    #2 0x4d26f6 in Client::getNick[abi:cxx11]() const /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Client.cpp:83:52
    #3 0x4d97ec in Channel::getClientsList[abi:cxx11]() /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Channel.cpp:179:29
    #4 0x50a43b in processJoin(Server*, std::vector<std::pair<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::pair<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > > >, int, int, int) /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/commands/Join.cpp:160:44
    #5 0x5078a6 in Join::execute(Server*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&, int) /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/commands/Join.cpp:289:5
    #6 0x4eca70 in Messageprocessing::processMessage(Server*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, int) /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Messageprocessing.cpp:100:39
```
