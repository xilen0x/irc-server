
#ifndef REPLIES_HPP
# define REPLIES_HPP

# define CRLF "\r\n"

// COMMANDS

# define PONG(token) ("PONG 127.0.0.1 " + token + CRLF)

// RESPLIES

#define RPL_WELCOME(server, nickname) ":" + server + " 001 " + WHI + " :Welcome to the IRC Network, " + nickname + "!" + RES + "\r\n"
#define RPL_YOURHOST(server) ":" + server + " 002 " + " :Your host is " + server + ", running version 1.0" + "\r\n"
#define RPL_CREATED(server) ":" + server + " 003 " + " :This server was created on 2025-02-03" + "\r\n"
// #define RPL_UMODEIS(hostname, channelname, mode, user)  ":" + hostname + " MODE " + channelname + " " + mode + " " + user + CRLF
// #define RPL_CREATIONTIME(nickname, channelname, creationtime) ": 329 " + nickname + " #" + channelname + " " + creationtime + CRLF
// #define RPL_CHANNELMODES(nickname, channelname, modes) ": 324 " + nickname + " #" + channelname + " " + modes + CRLF
// #define RPL_CHANGEMODE(hostname, channelname, mode, arguments) (":" + hostname + " MODE #" + channelname + " " + mode + " " + arguments + CRLF)
#define RPL_NICKCHANGE(oldnickname, nickname) (":" + oldnickname + " NICK " + nickname + CRLF)
// #define RPL_JOINMSG(hostname, ipaddress, channelname) (":" + hostname + "@" + ipaddress + " JOIN #" + channelname + CRLF)
// #define RPL_NAMREPLY(nickname, channelname, clientslist) (": 353 " + nickname + " @ #" + channelname + " :" + clientslist + CRLF)
// #define RPL_ENDOFNAMES(nickname, channelname) (": 366 " + nickname + " #" + channelname + " :END of /NAMES list" + CRLF)
// #define RPL_TOPICIS(nickname, channelname, topic) (": 332 " + nickname + " #" +channelname + " :" + topic + "\r\n")


// ERRORS

// #define ERR_NEEDMODEPARM(channelname, mode) (": 696 #" + channelname + " * You must specify a parameter for the key mode. " + mode + CRLF)
// #define ERR_INVALIDMODEPARM(channelname, mode) ": 696 #" + channelname + " Invalid mode parameter. " + mode + CRLF
// #define ERR_KEYSET(channelname) ": 467 #" + channelname + " Channel key already set. " + CRLF
// #define ERR_UNKNOWNMODE(nickname, channelname, mode) ": 472 " + nickname + " #" + channelname + " " + mode + " :is not a recognised channel mode" + CRLF
// #define ERR_CHANNELNOTFOUND(nickname, channelname) (": 403 " + nickname + " " + channelname + " :No such channel" + CRLF)
// #define ERR_NOTOPERATOR(channelname) (": 482 #" + channelname + " :You're not a channel operator" + CRLF)
// #define ERR_NOSUCHNICK(channelname, name) (": 401 #" + channelname + " " + name + " :No such nick/channel" + CRLF )
// #define ERR_NONICKNAME(nickname) (": 431 " + nickname + " :No nickname given" + CRLF )
#define ERR_NICKINUSE(nickname) (": 433 " + nickname + YEL + " :Nickname is already in use" + RES + CRLF)
#define ERR_ERRONEUSNICK(nickname) (": 432 " + nickname + RED + " :Erroneus nickname" + RES + CRLF)
#define ERR_NOTREGISTERED(nickname) (": 451 " + nickname + YEL + " :You have not registered!" + RES + CRLF)
// #define ERR_CMDNOTFOUND(nickname, command) (": 421 " + nickname + " " + command + " :Unknown command" + CRLF)

#define ERR_NEEDMOREPARAMS(nickname, command) ": 461 " + nickname  + " " + command + YEL + " :Not enough parameters" + RES + CRLF
#define ERR_ALREADYREGISTERED(nickname) (": 462 " + nickname + YEL + " :You may not reregister" + RES + CRLF )//( need PASS and NICK )
#define ERR_PASSWDMISMATCH(nickname) ": 464 " + nickname + RED + " :Password incorrect" + RES + CRLF

#endif  