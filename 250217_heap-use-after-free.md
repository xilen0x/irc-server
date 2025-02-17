# Error al hacer QUIT
El error aparece cuando el operador hace un Quit

### Client 1

```sh
apardo-m:lin-carlos-albert_repo/ (apardo-250125✗) $ nc 127.0.0.1 50000           [10:19:29]
pass hola
nick uno
user 1 0 * 1u
:ircserv 001  :Welcome to the IRC Network, UNO!
:ircserv 002  :Your host is ircserv, running version 1.0
:ircserv 003  :This server was created on Feb 17 2025 at 09:33:43
join #test
10:20 -!- :UNO!1 0 * 1u@127.0.0.1 JOIN #test
10:20 -!- : 353 UNO @ #test :@UNO
10:20 -!- : 366 UNO #test :END of /NAMES list
topic #test
: 331 UNO #test :No topic is set
topic #test :algo
: 332 UNO #test :algo
:UNO!127.0.0.1 TOPIC #test :algo
quit :adios
: ERROR :You have QUIT
```
> Tras hacer el QUIT , salta el error.

### Client 2

```sh
 $ nc 127.0.0.1 50000         [10:19:33]
pass hola
nick dos
user 2 0 * 2d
:ircserv 001  :Welcome to the IRC Network, DOS!
:ircserv 002  :Your host is ircserv, running version 1.0
:ircserv 003  :This server was created on Feb 17 2025 at 09:33:43
join #test
10:21 -!- :DOS!2 0 * 2d@127.0.0.1 JOIN #test
10:21 -!- : 353 DOS @ #test :@UNO DOS
10:21 -!- : 366 DOS #test :END of /NAMES list
:UNO!127.0.0.1 TOPIC #test :algo
join #42
10:26 -!- :DOS!2 0 * 2d@127.0.0.1 JOIN #42
10:26 -!- : 353 DOS @ #42 :@TRES DOS
10:26 -!- : 366 DOS #42 :END of /NAMES list
:TRES!127.0.0.1 TOPIC #42 :tres topic
:UNO!1 0 * 1u@127.0.0.1 QUIT :adios
```

### Client 3

```sh
 $ nc 127.0.0.1 50000         [10:19:33]
pass hola
nick tres
user 3 0 * 3t
:ircserv 001  :Welcome to the IRC Network, TRES!
:ircserv 002  :Your host is ircserv, running version 1.0
:ircserv 003  :This server was created on Feb 17 2025 at 09:33:43
join #42
10:24 -!- :TRES!3 0 * 3t@127.0.0.1 JOIN #42
10:24 -!- : 353 TRES @ #42 :@TRES
10:24 -!- : 366 TRES #42 :END of /NAMES list
topic #test
: 442 TRES test :You're not on that channel
topic #42
: 331 TRES #42 :No topic is set
topic #42 :tres topic
: 332 TRES #42 :tres topic
:TRES!127.0.0.1 TOPIC #42 :tres topic
:UNO!1 0 * 1u@127.0.0.1 QUIT :adios
```
### Server

```sh
apardo-m:lin-carlos-albert_repo/ (apardo-250125✗) $ ./ircserv 50000 hola         [10:19:26]
IRC server is running. Press Ctrl+C to stop.
Server successfully connected on port 50000.
Waiting for incoming connections...
New client connected
Received data: pass hola

Correct password!
Received data: nick uno

Correct nick format!
1st set a global nick: UNO
Received data: user 1 0 * 1u

Correct user format!
Received data: join #test

JOIN processing...
handleNonChannel!
========= Start Channels info === Channel Number = 1
----- CHANNEL DATA  (start)-----
_channelName = test
_inviteChannel = 0
_topic =
_topicRestricted = 0
_channelKey =
_hasUserLimit = 0
_userLimitNumber = 32767
- CHANNEL _operators:
	- UNO
- CHANNEL _memberClients:
- CHANNEL _invitedClients:
----- CHANNEL DATA  (end)-----

========= End Channels info =======

New client connected
Received data: pass hola

Correct password!
Received data: nick dos

Correct nick format!
1st set a global nick: DOS
Received data: user 2 0 * 2d

Correct user format!
Received data: join #test

JOIN processing...
nick1111111: DOS
nick1111111: DOS
DOS has been added in _memClients map!
processJoin!
LLega 1!
LLega 2!
========= Start Channels info === Channel Number = 1
----- CHANNEL DATA  (start)-----
_channelName = test
_inviteChannel = 0
_topic =
_topicRestricted = 0
_channelKey =
_hasUserLimit = 0
_userLimitNumber = 32767
- CHANNEL _operators:
	- UNO
- CHANNEL _memberClients:
	- DOS
- CHANNEL _invitedClients:
----- CHANNEL DATA  (end)-----

========= End Channels info =======

Received data: topic #test

    ----
    ----
Received data: topic #test :algo

    ----
    ----
New client connected
Received data: pass hola

Correct password!
Received data: nick tres

Correct nick format!
1st set a global nick: TRES
Received data: user 3 0 * 3t

Correct user format!
Received data: join #42

JOIN processing...
nick1111111: TRES
handleNonChannel!
========= Start Channels info === Channel Number = 2
----- CHANNEL DATA  (start)-----
_channelName = test
_inviteChannel = 0
_topic = algo
_topicRestricted = 1
_channelKey =
_hasUserLimit = 0
_userLimitNumber = 32767
- CHANNEL _operators:
	- UNO
- CHANNEL _memberClients:
	- DOS
- CHANNEL _invitedClients:
----- CHANNEL DATA  (end)-----

----- CHANNEL DATA  (start)-----
_channelName = 42
_inviteChannel = 0
_topic =
_topicRestricted = 0
_channelKey =
_hasUserLimit = 0
_userLimitNumber = 32767
- CHANNEL _operators:
	- TRES
- CHANNEL _memberClients:
- CHANNEL _invitedClients:
----- CHANNEL DATA  (end)-----

========= End Channels info =======

Received data: topic #test

    ----
Received data: topic #42

    ----
    ----
Received data: join #42

JOIN processing...
nick1111111: DOS
nick1111111: DOS
nick1111111: DOS
DOS has been added in _memClients map!
processJoin!
LLega 1!
LLega 2!
========= Start Channels info === Channel Number = 2
----- CHANNEL DATA  (start)-----
_channelName = test
_inviteChannel = 0
_topic = algo
_topicRestricted = 1
_channelKey =
_hasUserLimit = 0
_userLimitNumber = 32767
- CHANNEL _operators:
	- UNO
- CHANNEL _memberClients:
	- DOS
- CHANNEL _invitedClients:
----- CHANNEL DATA  (end)-----

----- CHANNEL DATA  (start)-----
_channelName = 42
_inviteChannel = 0
_topic =
_topicRestricted = 1
_channelKey =
_hasUserLimit = 0
_userLimitNumber = 32767
- CHANNEL _operators:
	- TRES
- CHANNEL _memberClients:
	- DOS
- CHANNEL _invitedClients:
----- CHANNEL DATA  (end)-----

========= End Channels info =======

Received data: topic #42 :tres topic

    ----
    ----
Received data: quit :adios

    ----
QUIT  => TODO test bad format
Delete nick client from any channel. Number of Channels : 2
 - Start Channel number : 0
 i,fd = 4, 4
 i,fd = 5, 4
  send  i,fd = 5, 4
 i,fd = 6, 4
  send  i,fd = 6, 4
 Set a member as operator
=================================================================
==4042057==ERROR: AddressSanitizer: heap-use-after-free on address 0x615000000420 at pc 0x000000438364 bp 0x7fffd0fe5d70 sp 0x7fffd0fe5530
READ of size 3 at 0x615000000420 thread T0
    #0 0x438363 in memcpy (/home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/ircserv+0x438363)
    #1 0x7f6202104123 in void std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_construct<char*>(char*, char*, std::forward_iterator_tag) (/lib/x86_64-linux-gnu/libstdc++.so.6+0x14f123)
    #2 0x4d27b6 in Client::getNick[abi:cxx11]() const /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Client.cpp:84:52
    #3 0x4d9e60 in Channel::addOpe(Client*) /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Channel.cpp:305:15
    #4 0x5251d3 in Quit::_selectMemberAsOperator(Server*, Channel*) /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/commands/Quit.cpp:16:19
    #5 0x526c32 in Quit::execute(Server*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&, int) /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/commands/Quit.cpp:94:6
    #6 0x4e6f90 in Messageprocessing::processMessage(Server*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, int) /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Messageprocessing.cpp:102:39
    #7 0x4ef59c in Server::receiveData(int) /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Server.cpp:168:27
    #8 0x4f0228 in Server::loop() /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Server.cpp:211:21
    #9 0x4f04ee in Server::runServer() /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Server.cpp:228:2
    #10 0x4d0dc4 in main /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/main.cpp:22:24
    #11 0x7f6201caed8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
    #12 0x7f6201caee3f in __libc_start_main csu/../csu/libc-start.c:392:3
    #13 0x422124 in _start (/home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/ircserv+0x422124)

0x615000000420 is located 288 bytes inside of 464-byte region [0x615000000300,0x6150000004d0)
freed by thread T0 here:
    #0 0x4ce91d in operator delete(void*) (/home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/ircserv+0x4ce91d)
    #1 0x4f757c in __gnu_cxx::new_allocator<Client>::deallocate(Client*, unsigned long) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/ext/new_allocator.h:145:2
    #2 0x4f7554 in __gnu_cxx::__alloc_traits<std::allocator<Client>, Client>::deallocate(std::allocator<Client>&, Client*, unsigned long) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/ext/alloc_traits.h:141:11
    #3 0x4f7507 in std::_Vector_base<Client, std::allocator<Client> >::_M_deallocate(Client*, unsigned long) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/bits/stl_vector.h:354:4
    #4 0x4f9150 in std::vector<Client, std::allocator<Client> >::_M_realloc_insert(__gnu_cxx::__normal_iterator<Client*, std::vector<Client, std::allocator<Client> > >, Client const&) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/bits/vector.tcc:500:7
    #5 0x4f438d in std::vector<Client, std::allocator<Client> >::push_back(Client const&) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/bits/stl_vector.h:1198:4
    #6 0x4ee31e in Server::acceptClient() /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Server.cpp:100:18
    #7 0x4f01c1 in Server::loop() /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Server.cpp:208:21
    #8 0x4f04ee in Server::runServer() /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Server.cpp:228:2
    #9 0x4d0dc4 in main /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/main.cpp:22:24
    #10 0x7f6201caed8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16

previously allocated by thread T0 here:
    #0 0x4ce0bd in operator new(unsigned long) (/home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/ircserv+0x4ce0bd)
    #1 0x4f9af9 in __gnu_cxx::new_allocator<Client>::allocate(unsigned long, void const*) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/ext/new_allocator.h:127:27
    #2 0x4f9a80 in __gnu_cxx::__alloc_traits<std::allocator<Client>, Client>::allocate(std::allocator<Client>&, unsigned long) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/ext/alloc_traits.h:133:18
    #3 0x4f971f in std::_Vector_base<Client, std::allocator<Client> >::_M_allocate(unsigned long) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/bits/stl_vector.h:346:20
    #4 0x4f8e02 in std::vector<Client, std::allocator<Client> >::_M_realloc_insert(__gnu_cxx::__normal_iterator<Client*, std::vector<Client, std::allocator<Client> > >, Client const&) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/bits/vector.tcc:440:33
    #5 0x4f438d in std::vector<Client, std::allocator<Client> >::push_back(Client const&) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/bits/stl_vector.h:1198:4
    #6 0x4ee31e in Server::acceptClient() /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Server.cpp:100:18
    #7 0x4f01c1 in Server::loop() /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Server.cpp:208:21
    #8 0x4f04ee in Server::runServer() /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Server.cpp:228:2
    #9 0x4d0dc4 in main /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/main.cpp:22:24
    #10 0x7f6201caed8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16

SUMMARY: AddressSanitizer: heap-use-after-free (/home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/ircserv+0x438363) in memcpy
Shadow bytes around the buggy address:
  0x0c2a7fff8030: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0c2a7fff8040: fd fd fd fd fd fd fd fd fd fd fd fa fa fa fa fa
  0x0c2a7fff8050: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c2a7fff8060: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0c2a7fff8070: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
=>0x0c2a7fff8080: fd fd fd fd[fd]fd fd fd fd fd fd fd fd fd fd fd
  0x0c2a7fff8090: fd fd fd fd fd fd fd fd fd fd fa fa fa fa fa fa
  0x0c2a7fff80a0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c2a7fff80b0: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0c2a7fff80c0: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0c2a7fff80d0: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:              cc
==4042057==ABORTING
```

