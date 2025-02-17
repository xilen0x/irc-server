
## Proceso

- Cliente 1 se autentica y crea el canal #test 

- Cliente 2 se autentica y se une al canal #test
- Cliente 1 crea un TOPIC en canal #test
- Cliente 3 se autentica y crea el canal #42
- Cliente 2 se une al canal #42
- Cliente 3 crea un TOPIC en canal #42
- Cliente 3 hace QUIT
- Cliente 2 hace QUIT




### Log en el server

```sh
apardo-m:lin-carlos-albert_repo/ (apardo-250125) $ ./ircserv 50000 hola          [9:44:31]
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
handleNonChannel!
========= Start Channels info === Channel Number = 1
----- CHANNEL DATA  (start)-----
_channelName = test
_inviteChannel = 0
_topic =
_topicRestricted = 0
_channelKey =
_hasUserLimit = 0
_userLimitNumber = 32766
- CHANNEL _operators:
	- DOS
- CHANNEL _memberClients:
- CHANNEL _invitedClients:
----- CHANNEL DATA  (end)-----

========= End Channels info =======

Received data: topic #test :hola

    ----
Received data: join #test

JOIN processing...
nick1111111: UNO
nick1111111: UNO
UNO has been added in _memClients map!
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
_userLimitNumber = 32766
- CHANNEL _operators:
	- DOS
- CHANNEL _memberClients:
	- UNO
- CHANNEL _invitedClients:
----- CHANNEL DATA  (end)-----

========= End Channels info =======

Received data: topic #test :hola

    ----
TODO : rigth evaluation for topicResticted
Received data: topic #test :hola

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
_topic = hola
_topicRestricted = 1
_channelKey =
_hasUserLimit = 0
_userLimitNumber = 32766
- CHANNEL _operators:
	- DOS
- CHANNEL _memberClients:
	- UNO
- CHANNEL _invitedClients:
----- CHANNEL DATA  (end)-----

----- CHANNEL DATA  (start)-----
_channelName = 42
_inviteChannel = 0
_topic =
_topicRestricted = 0
_channelKey =
_hasUserLimit = 0
_userLimitNumber = 32766
- CHANNEL _operators:
	- TRES
- CHANNEL _memberClients:
- CHANNEL _invitedClients:
----- CHANNEL DATA  (end)-----

========= End Channels info =======

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
_topic = hola
_topicRestricted = 1
_channelKey =
_hasUserLimit = 0
_userLimitNumber = 32766
- CHANNEL _operators:
	- DOS
- CHANNEL _memberClients:
	- UNO
- CHANNEL _invitedClients:
----- CHANNEL DATA  (end)-----

----- CHANNEL DATA  (start)-----
_channelName = 42
_inviteChannel = 0
_topic =
_topicRestricted = 0
_channelKey =
_hasUserLimit = 0
_userLimitNumber = 32766
- CHANNEL _operators:
	- TRES
- CHANNEL _memberClients:
	- DOS
- CHANNEL _invitedClients:
----- CHANNEL DATA  (end)-----

========= End Channels info =======

Received data: topic #42 :#42

    ----
    ----
Received data: quit :adios

    ----
QUIT  => TODO test bad format
Delete nick client from any channel. Number of Channels : 2
 - Start Channel number : 0
TRES no found in Channel[0] = test
 - Start Channel number : 1
 i,fd = 4, 6
  send  i,fd = 4, 6
 i,fd = 5, 6
  send  i,fd = 5, 6
 i,fd = 6, 6
 Set a member as operator
----- CHANNEL DATA  (start)-----
_channelName = 42
_inviteChannel = 0
_topic = #42
_topicRestricted = 1
_channelKey =
_hasUserLimit = 0
_userLimitNumber = 32766
- CHANNEL _operators:
	- DOS
- CHANNEL _memberClients:
- CHANNEL _invitedClients:
----- CHANNEL DATA  (end)-----

---- Test acces new operator : DOS
----- CLIENT DATA  (start)-----
_fdClient = 5
_ipClient = 127.0.0.1
_nick = DOS
_userName = 2 0 * 2d
_realName = *Real
_bufferInMessage =
_hasPass = 1
_hasNick = 1
_hasUser = 1
_hasAuth = 1
----- CLIENT DATA  (end)-----
 Deleted as operator
----- CHANNEL DATA  (start)-----
_channelName = 42
_inviteChannel = 0
_topic = #42
_topicRestricted = 1
_channelKey =
_hasUserLimit = 0
_userLimitNumber = 32766
- CHANNEL _operators:
	- DOS
- CHANNEL _memberClients:
- CHANNEL _invitedClients:
----- CHANNEL DATA  (end)-----

 - End Channel number : 1
    ----
fd = 6 client has QUIT from server !!!
Received data: topic #42 :dos #42

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
nick1111111: TRES
nick1111111: TRES
TRES has been added in _memClients map!
========= Start Channels info === Channel Number = 2
----- CHANNEL DATA  (start)-----
_channelName = test
_inviteChannel = 0
_topic = hola
_topicRestricted = 1
_channelKey =
_hasUserLimit = 0
_userLimitNumber = 32766
- CHANNEL _operators:
	- DOS
- CHANNEL _memberClients:
	- UNO
- CHANNEL _invitedClients:
----- CHANNEL DATA  (end)-----

----- CHANNEL DATA  (start)-----
_channelName = 42
_inviteChannel = 0
_topic = dos #42
_topicRestricted = 1
_channelKey =
_hasUserLimit = 0
_userLimitNumber = 32766
- CHANNEL _operators:
	- DOS
- CHANNEL _memberClients:
	- TRES
- CHANNEL _invitedClients:
----- CHANNEL DATA  (end)-----

========= End Channels info =======

Received data: topic #42

    ----
    ----
Received data: topic #test

    ----
Received data: quit :bybyby

    ----
QUIT  => TODO test bad format
Delete nick client from any channel. Number of Channels : 2
 - Start Channel number : 0
 i,fd = 4, 5
  send  i,fd = 4, 5
 i,fd = 5, 5
 i,fd = 6, 5
  send  i,fd = 6, 5
 Set a member as operator
=================================================================
==3938423==ERROR: AddressSanitizer: heap-use-after-free on address 0x6150000000b8 at pc 0x000000438364 bp 0x7ffe90cc1030 sp 0x7ffe90cc07f0
READ of size 3 at 0x6150000000b8 thread T0
    #0 0x438363 in memcpy (/home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/ircserv+0x438363)
    #1 0x7eff94d06123 in void std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_construct<char*>(char*, char*, std::forward_iterator_tag) (/lib/x86_64-linux-gnu/libstdc++.so.6+0x14f123)
    #2 0x4d27b6 in Client::getNick[abi:cxx11]() const /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Client.cpp:84:52
    #3 0x4d9e60 in Channel::addOpe(Client*) /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Channel.cpp:305:15
    #4 0x5245e3 in Quit::_selectMemberAsOperator(Server*, Channel*) /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/commands/Quit.cpp:16:19
    #5 0x526042 in Quit::execute(Server*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&, int) /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/commands/Quit.cpp:94:6
    #6 0x4e6910 in Messageprocessing::processMessage(Server*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, int) /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Messageprocessing.cpp:102:39
    #7 0x4eef1c in Server::receiveData(int) /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Server.cpp:168:27
    #8 0x4efba8 in Server::loop() /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Server.cpp:211:21
    #9 0x4efe6e in Server::runServer() /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Server.cpp:228:2
    #10 0x4d0dc4 in main /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/main.cpp:22:24
    #11 0x7eff948b0d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
    #12 0x7eff948b0e3f in __libc_start_main csu/../csu/libc-start.c:392:3
    #13 0x422124 in _start (/home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/ircserv+0x422124)

0x6150000000b8 is located 56 bytes inside of 464-byte region [0x615000000080,0x615000000250)
freed by thread T0 here:
    #0 0x4ce91d in operator delete(void*) (/home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/ircserv+0x4ce91d)
    #1 0x4f5e9c in __gnu_cxx::new_allocator<Client>::deallocate(Client*, unsigned long) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/ext/new_allocator.h:145:2
    #2 0x4f5e74 in __gnu_cxx::__alloc_traits<std::allocator<Client>, Client>::deallocate(std::allocator<Client>&, Client*, unsigned long) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/ext/alloc_traits.h:141:11
    #3 0x4f5e27 in std::_Vector_base<Client, std::allocator<Client> >::_M_deallocate(Client*, unsigned long) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/bits/stl_vector.h:354:4
    #4 0x4f7a70 in std::vector<Client, std::allocator<Client> >::_M_realloc_insert(__gnu_cxx::__normal_iterator<Client*, std::vector<Client, std::allocator<Client> > >, Client const&) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/bits/vector.tcc:500:7
    #5 0x4f379d in std::vector<Client, std::allocator<Client> >::push_back(Client const&) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/bits/stl_vector.h:1198:4
    #6 0x4edc9e in Server::acceptClient() /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Server.cpp:100:18
    #7 0x4efb41 in Server::loop() /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Server.cpp:208:21
    #8 0x4efe6e in Server::runServer() /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Server.cpp:228:2
    #9 0x4d0dc4 in main /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/main.cpp:22:24
    #10 0x7eff948b0d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16

previously allocated by thread T0 here:
    #0 0x4ce0bd in operator new(unsigned long) (/home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/ircserv+0x4ce0bd)
    #1 0x4f8419 in __gnu_cxx::new_allocator<Client>::allocate(unsigned long, void const*) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/ext/new_allocator.h:127:27
    #2 0x4f83a0 in __gnu_cxx::__alloc_traits<std::allocator<Client>, Client>::allocate(std::allocator<Client>&, unsigned long) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/ext/alloc_traits.h:133:18
    #3 0x4f803f in std::_Vector_base<Client, std::allocator<Client> >::_M_allocate(unsigned long) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/bits/stl_vector.h:346:20
    #4 0x4f7722 in std::vector<Client, std::allocator<Client> >::_M_realloc_insert(__gnu_cxx::__normal_iterator<Client*, std::vector<Client, std::allocator<Client> > >, Client const&) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/bits/vector.tcc:440:33
    #5 0x4f379d in std::vector<Client, std::allocator<Client> >::push_back(Client const&) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/bits/stl_vector.h:1198:4
    #6 0x4edc9e in Server::acceptClient() /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Server.cpp:100:18
    #7 0x4efb41 in Server::loop() /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Server.cpp:208:21
    #8 0x4efe6e in Server::runServer() /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/Server.cpp:228:2
    #9 0x4d0dc4 in main /home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/src/main.cpp:22:24
    #10 0x7eff948b0d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16

SUMMARY: AddressSanitizer: heap-use-after-free (/home/apardo-m/Documents/42-BCN/23-Cursus/05_circle/3_1_ft_irc/repo/lin-carlos-albert_repo/ircserv+0x438363) in memcpy
Shadow bytes around the buggy address:
  0x0c2a7fff7fc0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c2a7fff7fd0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c2a7fff7fe0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c2a7fff7ff0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c2a7fff8000: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
=>0x0c2a7fff8010: fd fd fd fd fd fd fd[fd]fd fd fd fd fd fd fd fd
  0x0c2a7fff8020: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0c2a7fff8030: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0c2a7fff8040: fd fd fd fd fd fd fd fd fd fd fa fa fa fa fa fa
  0x0c2a7fff8050: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c2a7fff8060: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
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
==3938423==ABORTING
```

### Cliente 1

```sh
apardo-m:lin-carlos-albert_repo/ (apardo-250125) $ nc 127.0.0.1 50000              [9:43:56]
pass hola
nick uno
user 1 0 * 1u
:ircserv 001  :Welcome to the IRC Network, UNO!
:ircserv 002  :Your host is ircserv, running version 1.0
:ircserv 003  :This server was created on Feb 16 2025 at 09:44:31
topic #test :hola
: 442 UNO test :You're not on that channel
join #test
09:47 -!- :UNO!1 0 * 1u@127.0.0.1 JOIN #test
09:47 -!- : 353 UNO @ #test :@DOS UNO
09:47 -!- : 366 UNO #test :END of /NAMES list
topic #test :hola
: 482 UNO #test :You're not a channel operator
:DOS!127.0.0.1 TOPIC #test :hola
:TRES!3 0 * 3t@127.0.0.1 QUIT :adios
:DOS!2 0 * 2d@127.0.0.1 QUIT :bybyby
```

### Cliente 2

```sh
apardo-m:lin-carlos-albert_repo/ (apardo-250125) $ nc 127.0.0.1 50000           [9:45:35]
pass hola
nick dos
user 2 0 * 2d
:ircserv 001  :Welcome to the IRC Network, DOS!
:ircserv 002  :Your host is ircserv, running version 1.0
:ircserv 003  :This server was created on Feb 16 2025 at 09:44:31
join #test
09:46 -!- :DOS!2 0 * 2d@127.0.0.1 JOIN #test
09:46 -!- : 353 DOS @ #test :@DOS
09:46 -!- : 366 DOS #test :END of /NAMES list
topic #test :hola
: 332 DOS #test :hola
:DOS!127.0.0.1 TOPIC #test :hola
join #42
09:49 -!- :DOS!2 0 * 2d@127.0.0.1 JOIN #42
09:49 -!- : 353 DOS @ #42 :@TRES DOS
09:49 -!- : 366 DOS #42 :END of /NAMES list
:TRES!127.0.0.1 TOPIC #42 :#42
:TRES!3 0 * 3t@127.0.0.1 QUIT :adios
:DOS, you are the new operator for Channel 42
topic #42 :dos #42
: 332 DOS #42 :dos #42
:DOS!127.0.0.1 TOPIC #42 :dos #42
quit :bybyby
: ERROR :You have QUIT

```
### Cliente 3

```sh
apardo-m:lin-carlos-albert_repo/ (apardo-250125✗) $ nc 127.0.0.1 50000          [9:14:02]
pass hola
nick tres
user 3 0 * 3t
:ircserv 001  :Welcome to the IRC Network, TRES!
:ircserv 002  :Your host is ircserv, running version 1.0
:ircserv 003  :This server was created on Feb 16 2025 at 09:44:31
join #42
09:49 -!- :TRES!3 0 * 3t@127.0.0.1 JOIN #42
09:49 -!- : 353 TRES @ #42 :@TRES
09:49 -!- : 366 TRES #42 :END of /NAMES list
topic #42 :#42
: 332 TRES #42 :#42
:TRES!127.0.0.1 TOPIC #42 :#42
quit :adios
: ERROR :You have QUIT

apardo-m:lin-carlos-albert_repo/ (apardo-250125) $ nc 127.0.0.1 50000           [9:51:55]
pass hola
nick tres
user 3 0 * 3t
:ircserv 001  :Welcome to the IRC Network, TRES!
:ircserv 002  :Your host is ircserv, running version 1.0
:ircserv 003  :This server was created on Feb 16 2025 at 09:44:31
join #42
09:52 -!- :TRES!3 0 * 3t@127.0.0.1 JOIN #42
09:52 -!- : 332 TRES #42 :dos #42
09:52 -!- : 353 TRES @ #42 :@DOS TRES
09:52 -!- : 366 TRES #42 :END of /NAMES list
topic #42
: 332 TRES #42 :dos #42
topic #test
: 442 TRES test :You're not on that channel
:DOS!2 0 * 2d@127.0.0.1 QUIT :bybyby

```

