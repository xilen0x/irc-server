#include <cstdlib> 
#include <limits>
#include "Mode.hpp"

#define MIN_CLIENTS_IN_CHANNEL 1

/* ------------------- PRIVATE MEMBER FUNCTIONS ------------------*/
/*
 * <cstdlib> : std::strtol
 * <limits>  : std::numeric_limits<int>
 */

bool    Mode::_isInt( const std::string &str )
{
    const char  *stmp;
    char        *endptr;
    long        num;

    stmp = str.c_str();
    num = std::strtol(stmp, &endptr, 10);
    if (endptr != str && *endptr == '\0' && \
            num <= std::numeric_limits<int>::max() && \
            num >= std::numeric_limits<int>::min())
        return (true);
    return (false);
}


std::string Mode::limit_mode(Channel *ch, char sign, std::string param)
{
	// Limit range : Minimum:1   MaxLimit: 2147483647
	//	https://modern.ircdocs.horse/#channel-modes

	int	limit;
	std::string strOption;
	
	strOption = "";
	if (_isInt(param))
	{
		limit = std::atoi(param.c_str());
		if (limit >= MIN_CLIENTS_IN_CHANNEL && limit <= std::numeric_limits<int>::max())
		{
			ch->setUserLimitActived();
			ch->setUserLimitNumber(limit);
			ch->setModeOption(4, true);
			strOption = modeOption_push(param, sign, 'l');
			ch->printChannelVars(); //debug
		}
	}
	else
		std::cout << "param=" << param << " NO es INT" << std::endl;
	return (strOption);
}

Mode::~Mode( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

std::string Mode::modeOption_push(std::string optionChain, char sign, char option)
{
	std::stringstream ss;
	ss.clear();
	char last = '\0';
	for (size_t i = 0; i < optionChain.size(); i++)
	{
		if (optionChain[i] == '+' || optionChain[i] == '-')
			last = optionChain[i];
	}
	if (last != sign)
		ss << sign << option;
	else
		ss << option;
	return ss.str();
}

std::string Mode::inviteOnly_mode(Channel *ch, char sign, std::string optionChain)
{
	std::string strOption;
	strOption.clear();
	if (sign == '+' && !ch->isInviteChannel() && !ch->getModeOption(0))
	{
		ch->setInviteChannel();
		ch->setModeOption(0, true);
		strOption = modeOption_push(optionChain, sign, 'i');
	}
	else if (sign == '-' && ch->isInviteChannel() && ch->getModeOption(0))
	{
		ch->unsetInviteChannel();
		ch->setModeOption(0, false);
		strOption = modeOption_push(optionChain, sign, 'i');
	}	
	return strOption;
}

bool isValidKey(std::string key)
{
	if (key.empty())
		return false;
	for (size_t i = 0; i < key.size(); i++)
	{
		if (key[i] < 33 || key[i] > 126 || key[i] == 44)
			return false;
	}
	return true;
}

std::string Mode::key_mode(Channel *ch, char sign, std::string key, std::string optionChain)
{
	std::string strOption;
	strOption.clear();
	if (!isValidKey(key))
	{
		std::cout << "[Error]: Channel Key " << key << " is invalid!" << std::endl;
    	return "InvalidKey";
	}
	if (sign == '+' && !ch->getHasChannelKey())
	{
		ch->setHasChannelKey(true);
		ch->setChannelKey(key);
		ch->setModeOption(2, true);
		strOption = modeOption_push(optionChain, sign, 'k');
	}
	else if (sign == '-' && ch->getHasChannelKey() && ch->getChannelKey() != key)
	{
		return "NoMatchKey";
	}
	else if (sign == '-' && ch->getHasChannelKey())
	{
		ch->setHasChannelKey(false);
		ch->setChannelKey("");
		ch->setModeOption(2, false);
		strOption = modeOption_push(optionChain, sign, 'k');
	}
	return strOption;
}

// Function to handle the change of operator privilege(MODE #channel +(-)o nick)
std::string Mode::changeOperatorPrivilege(Server *server, Channel *ch, char sign, std::string nick, std::string optionChain, int &status)
{
	std::string strOption;
	strOption.clear();
	nick = uppercase(nick);
	ch->printChannelVars();//debug
	Client *client = server->getClientByNick(nick);
	if (!client) {
    	std::cout << "[Error]: Client with nick " << nick << " not found!" << std::endl;
		status = -1;
    	return "";
	}
	if (sign == '+')
	{
		ch->addOpe(client);
		std::cout << "PRIVILEGE ADDED" << std::endl;//debug
		printChannelsInfo(server);//debug
		//quitar desdd memClients
		ch->deleteMem(nick);
		std::cout << "MEMBER DELETED FROM CHANNEL" << std::endl;//debug
		ch->setModeOption(3, true);
		strOption = modeOption_push(optionChain, sign, 'o');
		printChannelsInfo(server);//debug
		status = 1;	
	}
	else if (sign == '-')
	{
		ch->deleteOpe(nick);
		std::cout << "PRIVILEGE DELETED" << std::endl;//debug
		printChannelsInfo(server);//debug
		//agregar a memClients
		ch->addMem(client);
		std::cout << "MEMBER ADDED TO CHANNEL" << std::endl;//debug
		ch->setModeOption(3, false);
		strOption = modeOption_push(optionChain, sign, 'o');
		printChannelsInfo(server);//debug
		status = 1;
	}
	else {
		std::cout << "[Error]: invalid sign!" << std::endl;
		status = -1;
	}
	return (strOption);
}

std::string Mode::topic_mode(Channel *ch, char sign, std::string optionChain)
{
	std::string strOption;
	strOption.clear();
	if (sign == '+' && !ch->isTopicRestricted() && !ch->getModeOption(1))
	{
		ch->setTopicRestricted();
		ch->setModeOption(1, true);
		strOption = modeOption_push(optionChain, sign, 't');
	}
	else if (sign == '-' && ch->isTopicRestricted() && ch->getModeOption(1))
	{
		ch->unsetTopicRestricted();
		ch->setModeOption(1, false);
		strOption = modeOption_push(optionChain, sign, 't');
	}
	return strOption;
}

/*
void Mode::getModeArgs(std::string msg, std::string &channelName, std::string &option, std::string &param)
{
	std::istringstream ss(msg);
	ss >> channelName;
	ss >> option;
	size_t pos = msg.find_first_not_of(channelName + option + " \t\v");
	if (pos != std::string::npos)
		param = msg.substr(pos);
}
*/

bool Mode::getModeArgs(std::string msg, std::string &channelName, std::string &option, std::string &param)
{
	std::istringstream ss(msg);
	std::vector<std::string> tokens;
	std::string token;

	while (ss >> token)
		tokens.push_back(token);
	if (tokens.size() < 2 || tokens.size() > 3)
		return false;
	channelName = tokens[0];
	option = tokens[1];
	param = (tokens.size() == 3) ? tokens[2] : "";
	return true;
}

void Mode::execute( Server* server, std::string &msg , int fd)
{
	/* // the following is the example of the format of channel mode command:
	MODE #mychannel +i
	MODE #mychannel +o Bob / MODE #mychannel -o Bob
	MODE #mychannel +k secret123
	MODE #mychannel +l 25
	mode #mychannel +t
	MODE #mychannel -i
	MODE #mychannel -o Bob
	MODE #mychannel -k secret123
	MODE #mychannel -l
	mode #mychannel -t

	*/
	std::string 		channelName;
	std::string 		option;
	std::string 		param;
	std::stringstream 	optionChain;
	char				sign = '\0';
	int 				status = 0;
	
	std::cout << "Mode command is called!" << std::endl;//debug
	msg = trimLeft(msg);
	msg = msg.substr(4);
	msg = trimLeft(msg);
	msg = trimRight(msg);
	// #mychannel +i/+i/-i
	if (!msg.empty() && (msg.size() >= 2 && (msg.substr(0, 2) == "+i" || msg.substr(0, 2) == "-i"))) {
		std::cout << "it's not channel mode but user mode!" << std::endl;//debug
		return ;
	}
	else if (msg.empty() || (!msg.empty() && (msg.size() < 2 && (msg[0] == '#' || msg[0] == '&')))) {
		server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "MODE"), fd);
		std::cout << "input channelname and channel mode option are incorrect!" << std::endl;//debug
		return ;
	}
	else if (!msg.empty() && (msg[0] != '#' && msg[0] != '&'))
	{
		server->sendResp(FAIL_BADPARAMSFORMAT(msg), fd);
		std::cout << "input channelname is incorrect!" << std::endl;//debug
		return ;
	}
	else
		msg = msg.substr(1); // mychannel +i remove the first # or &
	std::cout << "mode msg: " << msg << std::endl; //debug
	if (!getModeArgs(msg, channelName, option, param)) // mychannel +i / mychannel +k password
	{
		std::string modeMsg = formatIRCMessage(FAIL_BADPARAMSFORMAT(msg));
		server->sendResp(modeMsg, fd);
		return ;
	}
	std::cout << "mode msg=" << msg << std::endl; //debug
	std::cout << "option:" << option << std::endl; //debug
	std::cout << "param:"  << param << std::endl; //debug
	if (param == "" && (option == "+k" || option == "-k" || option == "+o" || option == "-o" || option == "+l"))
	{
		std::string modeMsg = formatIRCMessage(FAIL_BADPARAMSFORMAT(msg));
		server->sendResp(modeMsg, fd);
		return ;
	}
	if (!param.empty() && (option == "+i" || option == "-i" || option == "+t" || option == "-t" || option == "-l"))
	{
		std::string modeMsg = formatIRCMessage(FAIL_BADPARAMSFORMAT(msg));
		server->sendResp(modeMsg, fd);
		return ;
	}
	Client *cl = server->getClient(fd);
	std::string nick = cl->getNick();
	// the channelName doesn't exist 403
	if (!server->getChannelByChannelName(channelName))
	{
		std::string chaErrMsg = formatIRCMessage(ERR_NOSUCHCHANNEL(nick, channelName));
		server->sendResp(chaErrMsg, fd);
		return ;
	}
	// if the inviting client doesn't in this channel 442
	if (!server->getChannelByChannelName(channelName)->getCliInChannel(nick))
	{
		std::string chaErrMsg = formatIRCMessage(ERR_NOTONCHANNEL(nick, channelName));
		server->sendResp(chaErrMsg, fd);
		return ;
	}
	//if the invitor isn't operator of this channel 482
	if (!server->getChannelByChannelName(channelName)->isOpe(nick))
    {
		std::string chaErrMsg = formatIRCMessage(ERR_CHANOPRIVSNEEDED(nick, channelName));
		server->sendResp(chaErrMsg, fd);
		return ;
	}
	Channel *channel = server->getChannelByChannelName(channelName);
	//if the option of MODE is empty
	if (option.empty())
	{
		std::string chaErrMsg = formatIRCMessage(RPL_CHANNELMODEIS(nick, channelName, option, param));
		server->sendResp(chaErrMsg, fd);
        return ;
	}
	else
	{

		if (option.size() == 2 && (option[0] == '+' || option[0] == '-'))//*o
		{
			sign = option[0];
			if (option[1] == 'i')
				optionChain << inviteOnly_mode(channel, sign, optionChain.str());
			else if (option[1] == 't')
			{
				optionChain << topic_mode(channel, sign, optionChain.str());
			}
			else if (option[1] == 'k')
			{
				std::string restr = key_mode(channel, sign, param, optionChain.str());		
				if (restr == "InvalidKey") // the set channel key is invalid 525
				{
					std::string chaErrMsg = formatIRCMessage(ERR_INVALIDKEY(nick, channelName));
					server->sendResp(chaErrMsg, fd);
        			return ;
				}
				if (restr == "NoMatchKey")
				{
					std::string chaErrMsg = formatIRCMessage(FAIL_NOMATCHCHANNELKEY(msg));
					server->sendResp(chaErrMsg, fd);
					return ;
				}
				optionChain << restr;
			}
			else if (option[1] == 'o')
			{
				optionChain << changeOperatorPrivilege(server, channel, sign, param, optionChain.str(), status);
			}
			else if (option[1] == 'l' && sign == '+') //WIP by apardo-m
			{
				optionChain << limit_mode(channel, sign, param);
				if (optionChain.str().empty())
					server->sendResp(FAIL_NOTINT(param),fd);
			}
			else
			{
				//std::string chaErrMsg = formatIRCMessage(ERR_UNKNOWNMODE(nick, channelName, option[i]));
				std::string chaErrMsg = formatIRCMessage(ERR_UNKNOWNMODE(nick, channelName, option)); // sign is need because I undesrtand that  "-l" option is not used IRC protocol by apardo-m
				server->sendResp(chaErrMsg, fd);
        		return ;
			}
		}
		else
		{
			server->sendResp(formatIRCMessage(FAIL_BADOPTIONFORMAT(option)), fd);
			return ;
		}
		std::string chain = optionChain.str(); //+i
		if (status == -1)
		{
			server->sendResp(ERR_ERRONEUSNICKNAME(std::string(param)), fd);
			return ;
		}
		if (chain.empty()) //Sent to a client to inform them of the currently-set modes of a channel: "<client> <channel> <modestring> <mode arguments>..."
		{
			std::string chaMsg = formatIRCMessage(RPL_CHANNELMODEIS(nick, channelName, option, param));
			server->sendResp(chaMsg, fd);
			return ;
		}	
		std::string chaMsg = formatIRCMessage(RPL_CHANGEMODE(server->getServerName(), channelName, chain, param));
		server->sendBroadAllInChannel(chaMsg, server->getChannelByChannelName(channelName));
	}	
}
