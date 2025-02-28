
#ifndef REPLIES_HPP
# define REPLIES_HPP

# define CRLF "\r\n"
# define LOCALHOST "127.0.0.1"
# define SP " "

// COMMANDS
# define PONG(token) ("PONG 127.0.0.1 " + token + CRLF)

// MESSAGES SERVER TO CLIENT
#define MSG_TOPIC_BROAD_ALL(nickAuthor, channel, topic) (":" + nickAuthor + "!" + LOCALHOST + " TOPIC #" + channel + " :" + topic + CRLF)

#define MSG_INVITED(invitingnick, username, invitedname, channelname) (":" + invitingnick + "!" + username + "@" + LOCALHOST +" INVITE " + invitedname + " #" + channelname + CRLF)
#define MSG_QUIT_CHANNEL_REASON(nickname, username, reason) (":" + nickname + "!" + username + "@" + LOCALHOST +" QUIT :" + reason + CRLF)
#define MSG_QUIT_CHANNEL_NO_REASON(nickname, username) (":" + nickname + "!" + username + "@" + LOCALHOST +" QUIT :" + CRLF)
#define MSG_QUIT_CHANGE_OPERATOR(nickname, channel) (":" + nickname + ", you are the new operator for Channel " + channel + CRLF)
#define MSG_PRIVMSG_TO_CHANNEL(nickSender, channel, msg) (":" + nickSender + " PRIVMSG #" + channel + " :" + msg + CRLF)
#define MSG_PRIVMSG_TO_NICK(nickSender, nickname, msg) (":" + nickSender + " PRIVMSG " + nickname + " :" + msg + CRLF)
#define ERR_QUIT_MSG ": ERROR :You have QUIT\r\n"
#define ERR_KICK_MSG ": ERROR :You have been KICKED\r\n"

// REPLIES
#define RPL_WELCOME(server, nickname) ":" + server + " 001 " + WHI + " :Welcome to the IRC Network, " + nickname + "!" + RES + "\r\n"
#define RPL_YOURHOST(server) ":" + server + " 002 " + " :Your host is " + server + ", running version 1.0" + "\r\n"
#define RPL_CREATED(server) ":" + server + " 003 " + " :This server was created on " + __DATE__ + " at " + __TIME__ + "\r\n"
#define RPL_CHANNELMODEIS(nickname, channelname, option, param) (": 324 " + nickname + " #" + channelname + " option: " + option + " param: " + param + CRLF)
#define RPL_CREATIONTIME(nickname, channelname, creationtime) ": 329 " + nickname + " #" + channelname + " " + creationtime + CRLF
#define RPL_NICKCHANGE(oldnickname, nickname) (":" + oldnickname + " NICK " + nickname + CRLF)
#define RPL_NOTOPIC(nickname, channelname) (": 331 " + nickname + " #" +channelname + " :No topic is set" + CRLF)
#define RPL_TOPIC(nickname, channelname, topic) (": 332 " + nickname + " #" +channelname + " :" + topic + CRLF)
#define RPL_JOINMSG(hostname, ipaddress, channelname) (":" + hostname + "@" + ipaddress + " JOIN #" + channelname + CRLF)
#define RPL_NAMREPLY(nickname, channelname, clientslist) (": 353 " + nickname + " @ #" + channelname + " :" + clientslist + CRLF)
#define RPL_ENDOFNAMES(nickname, channelname) (": 366 " + nickname + " #" + channelname + " :END of /NAMES list" + CRLF)
#define RPL_TOPICIS(nickname, channelname, topic) (": 332 " + nickname + " #" +channelname + " :" + topic + "\r\n")
#define RPL_INVITING(invitingnick, channelname, invitednick) (": 341 " + invitingnick + " " + invitednick + " #" + channelname + " :" + invitingnick + " INVITE " + invitednick + " into #" + channelname + CRLF)
#define RPL_INFO(nickname) (nickname + " : 371 " + " :can join ONLY ONE channel at a time" + CRLF)

// ERRORS
#define ERR_NOSUCHNICK(nickname) (": 401 " + nickname + " :No such nick/channel" + CRLF )
#define ERR_NOSUCHCHANNEL(nickname, channelname) (": 403 " + nickname + " #" + channelname + " :No such channel" + CRLF)
#define ERR_TOOMANYCHANNELS(nickname) (": 405 " + nickname + RED + " :You have joined too many channels" + RES + CRLF)
#define ERR_NOTEXTTOSEND(nickname) (": 412 " + nickname + RED + " :No text to send" + RES + CRLF)
#define ERR_NICKINUSE(nickname) (": 433 " + nickname + YEL + " :Nickname is already in use" + RES + CRLF)
#define ERR_ERRONEUSNICKNAME(nickname) (": 432 " + nickname + RED + " :Erroneus nickname" + RES + CRLF)
#define ERR_UNKNOWNCOMMAND(nickname, command) (": 421 " + nickname + " " + command + " :Unknown command" + CRLF)
#define ERR_NOTONCHANNEL(nickname, channelname) (": 442 " + nickname + " #" + channelname + " :You're not on that channel" + CRLF)
#define ERR_USERONCHANNEL(nickname, channelname) (": 443 " + nickname + " #" + channelname + " :is already on channel" + CRLF)
#define ERR_NOTREGISTERED(nickname) (": 451 " + nickname + YEL + " :You have not registered!" + RES + CRLF)
#define ERR_NEEDMOREPARAMS(nickname, command) ": 461 " + nickname  + " " + command + YEL + " :Not enough parameters" + RES + CRLF
#define ERR_ALREADYREGISTERED(nickname) (": 462 " + nickname + YEL + " :You may not reregister" + RES + CRLF )
#define ERR_PASSWDMISMATCH(nickname) ": 464 " + nickname + RED + " :Password incorrect" + RES + CRLF
#define ERR_CHANNELISFULL(nickname, channelname) (": 471 " + nickname + " #" + channelname + RED + " :Cannot join channel (+l)" + RES + CRLF )
#define ERR_UNKNOWNMODE(nickname, channelname, mode) ": 472 " + nickname + " #" + channelname + " " + mode + " :is not a recognised channel mode" + CRLF
#define ERR_INVITEONLYCHAN(nickname, channelname) (": 473 " + nickname + " #" + channelname + RED + " :Cannot join channel (+i)" + RES + CRLF )
#define ERR_BADCHANNELKEY(nickname, channelname) (": 475 " + nickname + " #" + channelname + RED + " :Cannot join channel (+k)" + RES + CRLF )
#define ERR_CHANOPRIVSNEEDED(nickname, channelname) (": 482 " + nickname + " #" + channelname + RED + " :You're not a channel operator" RES + CRLF)
#define ERR_USERNOTINCHANNEL(nickname, channelname) (": 441 " + nickname + " #" + channelname + " :They aren't on that channel" + CRLF)
#define ERR_INVALIDKEY(nickname, channelname) (": 525 " + nickname + " #" + channelname + RED + " :Key is not well-formed" + RES + CRLF )

// PERSONALIZED ERRORS & REPLIES
#define ERR_SERVERDOWN(nickname) (": ERROR :Closing Link: " + nickname + " (Server shutdown)" + CRLF)
#define ERR_USERSYNTAXERROR(nickname, command) (": " + nickname + " " + command + " :Syntax error. Usage: " + YEL + "USER <username> 0 * : <realname>" + RES + CRLF)
#define RPL_KICK(nickname, channelname, user, comment) (": " + nickname + " KICK #" + channelname + " " + user + " :" + comment + CRLF)
#define RPL_INVITEINFO(nickname) (nickname + " :can invite ONY ONE client in ONLY ONE channel at a time" + CRLF)
#define RPL_CHANGEMODE(server, channelname) (":" + server + " MODE #" + channelname + CRLF)

//FAILS
#define FAIL_LOTPARAMS(msg) (": FAIL " + msg + " :" + YEL + "A Lot of Params!!" + RES + CRLF)
#define FAIL_BADPARAMSFORMAT(msg) (": FAIL " + msg + " :" + "Bad Parameters Format!" + CRLF)
#define FAIL_NOTINT(msg) (": FAIL " + msg + " :" + YEL + "Not positive integer provided!!" + RES + CRLF)
#define FAIL_NOINTORMAXLIMITUSERCHANNEL(msg, limit) (": FAIL " + msg + " :" + YEL + "Not positive integer provided or his limit can´t be set. This Server has MAX LIMIT PER CHANNEL in " + limit + " clients." + RES + CRLF)
#define FAIL_NOMATCHCHANNELKEY(msg) (": FAIL " + msg + " :" + YEL + "Not match channel key!" + RES + CRLF )
#define FAIL_BADOPTIONFORMAT(modeoption) (": FAIL " + modeoption + " :" + YEL + "Bad channel mode!" + RES + CRLF)
#define FAIL_NOPARAMNEED(msg) (": FAIL "+ msg + " :" + YEL + "No parameter needed!" + RES + CRLF)
#define FAIL_PARAM(msg) (": FAIL "+ msg + " :" + YEL + "Bad parameters!" + RES + CRLF)

#endif
