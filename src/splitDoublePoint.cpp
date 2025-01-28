#include <string>
#include <vector>

/*
 * If ´:' is in 'msg'
 * 	Divide 'msg' in two substrings in a 'std::vector<std::string>' 
 * else
 *  return 'msg' in 'std::vector<std::string>'
 */
std::vector<std::string> splitByDoublePoint(const std::string & msg)
{
  std::vector<std::string> result;
  
  std::size_t pos = msg.find(":");
  if (pos < msg.size())
  {
    result.push_back(msg.substr(0, pos - 1));
    result.push_back(msg.substr(pos + 1));
  }
  else
    result.push_back(msg);
  
  return(result);
}

/*
int main ()
{
  std::vector<std::string> splitedMessage;
  
  std::string msg="PRIVMSG apm :This is the message";

  splitedMessage = splitByDoublePoint(msg);
  std::cout << splitedMessage[0] << std::endl;
  std::cout << splitedMessage[1] << std::endl;

  return 0;
}
*/
