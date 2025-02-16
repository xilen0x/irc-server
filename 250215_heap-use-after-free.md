## 25012 13:15 Error Tras hacer merge con la rama de Carlos

## Cliente Uno

```sh
pass hola
nick uno
user 1 0 * 1u
:ircserv 001  :Welcome to the IRC Network, UNO!
:ircserv 002  :Your host is ircserv, running version 1.0
:ircserv 003  :This server was created on Feb 15 2025 at 13:19:10
join #test
13:25 -!- :UNO!1 0 * 1u@127.0.0.1 JOIN #test
13:25 -!- : 353 UNO @ #test :@UNO
13:25 -!- : 366 UNO #test :END of /NAMES list
topic #test :asdfasdf afsdfasdf aadffjkj asfdsfk kdkdjf
: 332 UNO #test :asdfasdf afsdfasdf aadffjkj asfdsfk kdkdjf
:UNO!127.0.0.1 TOPIC #test :asdfasdf afsdfasdf aadffjkj asfdsfk kdkdjf
quit :adios
: ERROR :You have QUIT

```

## Cliente dos

```sh
pass hola
nick dos
user 2 0 * 2d
:ircserv 001  :Welcome to the IRC Network, DOS!
:ircserv 002  :Your host is ircserv, running version 1.0
:ircserv 003  :This server was created on Feb 15 2025 at 13:19:10
join #test
13:26 -!- :DOS!2 0 * 2d@127.0.0.1 JOIN #test
13:26 -!- : 353 DOS @ #test :@UNO DOS
13:26 -!- : 366 DOS #test :END of /NAMES list
topic #test
: 331 DOS #test :No topic is set
:UNO!127.0.0.1 TOPIC #test :asdfasdf afsdfasdf aadffjkj asfdsfk kdkdjf
topic #test
: 332 DOS #test :asdfasdf afsdfasdf aadffjkj asfdsfk kdkdjf
:UNO!1 0 * 1u@127.0.0.1 QUIT :adios
:DOS, you are the new operator for Channel test
topic #test :algo por decir sin sentido
: 332 DOS #test :algo por decir sin sentido
:DOS!127.0.0.1 TOPIC #test :algo por decir sin sentido
topic #test
: 332 DOS #test :algo por decir sin sentido
quit
: ERROR :You have QUIT

```

Tras hacer el **quit**, salta el errror.


## Error :
```sh
==3830840==ERROR: AddressSanitizer: heap-use-after-free on address 0x6040000009d0 at pc 0x00000043a51e bp 0x7ffef78c8370 sp 0x7ffef78c7b38
READ of size 26 at 0x6040000009d0 thread T0
    #0 0x43a51d in fwrite (/home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/ircserv+0x43a51d)
    #1 0x7f5cd5fc3b64 in std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long) (/lib/x86_64-linux-gnu/libstdc++.so.6+0x13cb64)
    #2 0x4db305 in Channel::printChannelVars() /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Channel.cpp:397:27
    #3 0x523355 in Quit::execute(Server*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&, int) /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/commands/Quit.cpp:96:20
    #4 0x4e5ec0 in Messageprocessing::processMessage(Server*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, int) /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Messageprocessing.cpp:102:39
    #5 0x4ee4cc in Server::receiveData(int) /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Server.cpp:168:27
    #6 0x4ef158 in Server::loop() /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Server.cpp:211:21
    #7 0x4ef41e in Server::runServer() /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Server.cpp:228:2
    #8 0x4d0dc4 in main /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/main.cpp:22:24
    #9 0x7f5cd5b80d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
    #10 0x7f5cd5b80e3f in __libc_start_main csu/../csu/libc-start.c:392:3
    #11 0x422124 in _start (/home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/ircserv+0x422124)

0x6040000009d0 is located 0 bytes inside of 43-byte region [0x6040000009d0,0x6040000009fb)
freed by thread T0 here:
    #0 0x4ce91d in operator delete(void*) (/home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/ircserv+0x4ce91d)
    #1 0x4d8376 in Channel::~Channel() /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Channel.cpp:105:1
    #2 0x4f9b78 in __gnu_cxx::new_allocator<Channel>::destroy(Channel*) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/ext/new_allocator.h:177:36
    #3 0x4f969c in __gnu_cxx::__alloc_traits<std::allocator<Channel>, Channel>::destroy(std::allocator<Channel>&, Channel*) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/ext/alloc_traits.h:148:11
    #4 0x4fb6fd in std::vector<Channel, std::allocator<Channel> >::_M_erase(__gnu_cxx::__normal_iterator<Channel*, std::vector<Channel, std::allocator<Channel> > >) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/bits/vector.tcc:177:7
    #5 0x4f40cd in std::vector<Channel, std::allocator<Channel> >::erase(__gnu_cxx::__normal_iterator<Channel*, std::vector<Channel, std::allocator<Channel> > >) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/bits/stl_vector.h:1434:16
    #6 0x4f0b49 in Server::deleteChannel(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >) /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Server.cpp:337:23
    #7 0x521d42 in Quit::_selectMemberAsOperator(Server*, Channel*) /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/commands/Quit.cpp:28:12
    #8 0x5232e2 in Quit::execute(Server*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&, int) /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/commands/Quit.cpp:94:6
    #9 0x4e5ec0 in Messageprocessing::processMessage(Server*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, int) /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Messageprocessing.cpp:102:39
    #10 0x4ee4cc in Server::receiveData(int) /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Server.cpp:168:27
    #11 0x4ef158 in Server::loop() /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Server.cpp:211:21
    #12 0x4ef41e in Server::runServer() /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Server.cpp:228:2
    #13 0x4d0dc4 in main /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/main.cpp:22:24
    #14 0x7f5cd5b80d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16

previously allocated by thread T0 here:
    #0 0x4ce0bd in operator new(unsigned long) (/home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/ircserv+0x4ce0bd)
    #1 0x7f5cd5fd2fee in std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_assign(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&) (/lib/x86_64-linux-gnu/libstdc++.so.6+0x14bfee)

```
