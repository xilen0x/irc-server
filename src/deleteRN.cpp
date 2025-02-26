#include <iostream> 
#include <string>
#include <vector>
#include "Server.hpp"

/*
 * Delete "\r\n" or "\r" or "\n" in 'msg'
 */
 
void deleteRN(std::string &msg)
{
    std::size_t pos;
    std::string tmpString;
    
    pos = msg.find_last_of("\r");
    if (pos > msg.size())
    {
        pos = msg.find_last_of("\n");
        if (pos > msg.size())
            return;
    }
    tmpString = msg.substr(0, pos);
    msg.clear();
    msg = tmpString;
}
