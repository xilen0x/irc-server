
#include "Cap.hpp"


void Cap::execute(Server* server, std::string &msg, int fd) {
    (void)msg;
    (void)server;

    std::string response = ":ircserv CAP * LS :\r\n";
    send(fd, response.c_str(), response.length(), 0);
}


Cap::~Cap( void ) {};
