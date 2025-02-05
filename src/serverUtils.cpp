
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
    if (port < 1024 || port > 65535)
    {
        std::cerr << "Invalid port number. Must be beetwen 1024 and 65535" << std::endl;
        return (1);
    }
    if (std::strlen(password.c_str()) < 4)
    {
        std::cerr << "Password must be at least 4 characters long" << std::endl;
        return (1);
    }
    return (0);
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
