
#include "Messageprocessing.hpp"
#include "Server.hpp"
#include <ctime>
#include "irc.hpp"

// Get the current time as a formatted string (HH:MM)
std::string getCurrentTime()
{
    std::time_t now = std::time(0);
    std::tm* now_tm = std::localtime(&now);

    char buffer[6]; // for "HH:MM"
    std::strftime(buffer, sizeof(buffer), "%H:%M", now_tm);//formats the time

    return std::string(buffer);
}

// Format an IRC message with a timestamp
std::string formatIRCMessage(const std::string& message)
{
    std::string timestamp = getCurrentTime();
    return timestamp + " -!- " + message;
}

int parseInput(std::string password, int port)
{
    if (port < 49152 || port > 65535)
    {
        std::cerr << "Invalid port number. Must be beetwen 49152 and 65535" << std::endl;
        return (1);
    }
    if (std::strlen(password.c_str()) < 4)
    {
        std::cerr << "Password must be at least 4 characters long" << std::endl;
        return (1);
    }
    return (0);
}

void removeAnsiCodes(std::string &str) {
    size_t pos;
    while ((pos = str.find("\033[")) != std::string::npos) { // "\033[" es equivalente a "\e["
        size_t end = str.find('m', pos);  // Buscar el final del código ANSI
        if (end != std::string::npos) {
            str.erase(pos, end - pos + 1); // Eliminar el código ANSI
        } else {
            break; // Evitar bucles infinitos si no hay 'm'
        }
    }
}

std::string trimRight(std::string &str)
{
    size_t pos = str.find_last_not_of(" \t\v\r\n");//find the last character that is not a white space
    if (pos == std::string::npos)//if there is no white space
        return ("");
    return (str.substr(0, pos + 1));//return the string from the beginning to the last character that is not a white space
}

// to remove the first white spaces of a string
std::string trimLeft(std::string &str)
{
	size_t pos = str.find_first_not_of(" \t\v\r\n");
	if (pos == std::string::npos)
		return ("");
	return (str.substr(pos));
}

static char to_upper(char c)
{
	return (std::toupper(static_cast<unsigned char>(c)));
}

std::string uppercase(std::string &s)
{
	std::transform(s.begin(), s.end(), s.begin(), to_upper);
	return (s);
}

//checkNickInUse can be a public function on Server class
bool checkNickInUse(std::vector<Client> clients, std::string &s)
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		std::string str = clients[i].getNick();
		if (uppercase(str) == uppercase(s))
			return (true);
	}
	return (false);
}

std::string sanitizeInput(const std::string& msg) 
{
    std::string msgSanitized;

    for (size_t i = 0; i < msg.size(); i++) 
	{
        if (msg[i] == '\r' || msg[i] == '\n') 
			continue;
        msgSanitized += msg[i];
    }
    return (msgSanitized);
}

bool validateNick(std::string &s) {
    s = sanitizeInput(s); // Limpiar el nick antes de validarlo

    if (s.size() > 9 || s.empty())
        return (false);
    const std::string allowedChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_[]{}\\|^";
    const std::string prohibited = " &#:@!*\t";
    if (prohibited.find(s[0]) != std::string::npos)
        return (false);
    for (size_t i = 1; i < s.size(); i++) {
        if (allowedChars.find(s[i]) == std::string::npos)
            return (false);//if the character is not in the allowedChars string
    }
    if (uppercase(s) == "NICKSERV" || uppercase(s) == "CHANSERV")
        return (false);
    return (true);
}

//Function that check if the client is authenticated
int isAuthenticated(Client* client, Server* server, int fd) {
    if (client->getHasAuth()) {
        return (1);
    }
    else
    {
        server->sendResp(ERR_NOTREGISTERED(std::string("*")), fd);//451
        return (0);
    }
    return (1);
}

void	printChannelsInfo(Server *server)
{
	Channel *channel;

	std::cout << "========= Start Channels info === Channel Number = " << server->getChannels().size() << std::endl;//debug
	for (size_t i = 0; i < server->getChannels().size(); i++)
	{
		channel = server->getChannelsByNumPosInVector(i);
		channel->printChannelVars();
	}   
	std::cout << "========= End Channels info =======\n" << std::endl;//debug
}
