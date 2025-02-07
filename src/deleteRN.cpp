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

/*
int main ()
{
  std::vector<std::string> splitedMessage;
  
  std::string msg1="PRIVMSG apm :Message 1\r\n";
  std::string msg2="PRIVMSG apm :Message 2\r";
  std::string msg3="PRIVMSG apm :Message 3\n";
 
  deleteRN(msg1);
  deleteRN(msg2);
  deleteRN(msg3);
  
  std::cout << msg1 << std::endl;
  std::cout << msg2 << std::endl;
  std::cout << msg3 << std::endl;
  return 0;
}
*/
