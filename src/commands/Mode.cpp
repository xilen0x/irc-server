#include <cstdlib> 
#include <limits>
#include "Mode.hpp"

#define MIN_CLIENTS_IN_CHANNEL 1

#define NO_IN_CHANNEL_LIMITS "NoInChannelLimits"
#define ERR_PARAM "ErrParam"
#define	ERR_PARAM_NO_NEED "ErrParamNoNeed"


/* ------------------- PRIVATE MEMBER FUNCTIONS ------------------*/

std::string	Mode::_intToString( int num )
{
	std::ostringstream convert;   // stream used for the conversion
	convert << num;      // insert the textual representation of 'Number' in the characters in the stream
	return (convert.str()) ;
}


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

std::string Mode::limit_mode(Channel *ch, char sign, std::string param, int maxLimitUser)
{
	int	limit;
	std::string strOption;
	
	strOption.clear();
	if ( sign == '+' && _isInt(param))
	{
		limit = std::atoi(param.c_str());
		if (limit >= MIN_CLIENTS_IN_CHANNEL && limit <= maxLimitUser)
		{
			ch->setUserLimitActived();
			ch->setUserLimitNumber(limit);
			ch->setModeOption(4, true);
			strOption = modeOption_push(param, sign, 'l');
		}
		else
			strOption = NO_IN_CHANNEL_LIMITS;
	}
	else if ( sign == '-' && param.empty())
	{
			ch->unsetUserLimitActived();
			ch->setUserLimitNumber(MAX_USER_LIMIT_NUMBER);
			ch->setModeOption(4, false);
			strOption = modeOption_push(param, sign, 'l');
	}
	else if (sign == '+' && !_isInt(param)) 
		strOption = ERR_PARAM;
	else
		strOption = ERR_PARAM_NO_NEED;
	ch->printChannelVars(); //debug

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
	if (sign == '+' && (!ch->getHasChannelKey() || (ch->getHasChannelKey() && ch->getChannelKey() != key)))
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

// the following is the example of the format of channel mode command:
/*
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
void Mode::execute( Server* server, std::string &msg , int fd)
{

	std::string 		channelName;
	std::string 		option;
	std::string 		param;
	std::stringstream 	optionChain;
	char				sign = '\0';
	int 				status = 0;

	if (isAuthenticated(server->getClient(fd), server, fd))
	{
		msg = trimLeft(msg);
		msg = msg.substr(4);
		msg = trimLeft(msg);
		msg = trimRight(msg);
		if (!msg.empty() && (msg.size() >= 2 && (msg.substr(0, 2) == "+i" || msg.substr(0, 2) == "-i"))) 
		{
			// std::cout << "it's not channel mode but user mode!" << std::endl;//debug
			return ;
		}
		else if (msg.empty() || (!msg.empty() && (msg.size() < 2 && (msg[0] == '#' || msg[0] == '&')))) {
			server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "MODE"), fd);
			std::cout << "[LOG][ERROR] input channelname and channel mode option are incorrect!" << std::endl;//debug
			return ;
		}
		else if (!msg.empty() && (msg[0] != '#' && msg[0] != '&'))
		{
			server->sendResp(FAIL_BADPARAMSFORMAT(msg), fd);//aqui entra de forma automatica irssi
			std::cout << "[LOG][ERROR] input channelname is incorrect!" << std::endl;//debug
			return ;
		}
		else
			msg = msg.substr(1);
		// std::cout << "mode msg: " << msg << std::endl; //debug
		if (!getModeArgs(msg, channelName, option, param)) // mychannel +i / mychannel +k password
		{
			std::string modeMsg = FAIL_BADPARAMSFORMAT(msg);
			server->sendResp(modeMsg, fd);
			return ;
		}
		if (param == "" && (option == "+k" || option == "-k" || option == "+o" || option == "-o" || option == "+l"))
		{
			std::string modeMsg = FAIL_BADPARAMSFORMAT(msg);
			server->sendResp(modeMsg, fd);
			return ;
		}
		if (!param.empty() && (option == "+i" || option == "-i" || option == "+t" || option == "-t" || option == "-l"))
		{
			std::string modeMsg = FAIL_BADPARAMSFORMAT(msg);
			server->sendResp(modeMsg, fd);
			return ;
		}
		Client *cl = server->getClient(fd);
		std::string nick = cl->getNick();
		// the channelName doesn't exist 403
		if (!server->getChannelByChannelName(channelName))
		{
			std::string chaErrMsg = ERR_NOSUCHCHANNEL(nick, channelName);
			server->sendResp(chaErrMsg, fd);
			return ;
		}
		// if the inviting client doesn't in this channel 442
		if (!server->getChannelByChannelName(channelName)->getCliInChannel(nick))
		{
			std::string chaErrMsg = ERR_NOTONCHANNEL(nick, channelName);
			server->sendResp(chaErrMsg, fd);
			return ;
		}
		//if the invitor isn't operator of this channel 482
		if (!server->getChannelByChannelName(channelName)->isOpe(nick))
		{
			std::string chaErrMsg = ERR_CHANOPRIVSNEEDED(nick, channelName);
			server->sendResp(chaErrMsg, fd);
			return ;
		}
		Channel *channel = server->getChannelByChannelName(channelName);
		//if the option of MODE is empty
		if (option.empty())
		{
			std::string chaErrMsg = RPL_CHANNELMODEIS(nick, channelName, option, param);
			server->sendResp(chaErrMsg, fd);
			return ;
		}
		else
		{
			if (option.size() == 2 && (option[0] == '+' || option[0] == '-'))
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
						std::string chaErrMsg = ERR_INVALIDKEY(nick, channelName);
						server->sendResp(chaErrMsg, fd);
						return ;
					}
					if (restr == "NoMatchKey")
					{
						std::string chaErrMsg = FAIL_NOMATCHCHANNELKEY(msg);
						server->sendResp(chaErrMsg, fd);
						return ;
					}
					optionChain << restr;
				}
				else if (option[1] == 'o')
				{
					optionChain << changeOperatorPrivilege(server, channel, sign, param, optionChain.str(), status);
				}
				else if (option[1] == 'l' )
				{
					int maxUserLimit = MAX_USER_LIMIT_NUMBER;

					std::string restr = limit_mode(channel, sign, param, maxUserLimit);
					if (restr == NO_IN_CHANNEL_LIMITS)
					{
						server->sendResp(FAIL_NOINTORMAXLIMITUSERCHANNEL(param, _intToString(MAX_USER_LIMIT_NUMBER)),fd);
						return ;
					}
					if (restr == ERR_PARAM)
					{
						msg = "MODE #" + msg;
						server->sendResp(FAIL_PARAM(msg),fd);
						return;
					}
					if (restr == ERR_PARAM_NO_NEED)
					{
						msg = "MODE #" + msg;
						server->sendResp(FAIL_NOPARAMNEED(msg),fd);
						return;
					}
					optionChain << restr;
				}
				else
				{
					std::string chaErrMsg = ERR_UNKNOWNMODE(nick, channelName, option);
					server->sendResp(chaErrMsg, fd);
					return ;
				}
			}
			else
			{
				server->sendResp(FAIL_BADOPTIONFORMAT(option), fd);
				return ;
			}
			std::string chain = optionChain.str();
			if (status == -1)
			{
				server->sendResp(ERR_ERRONEUSNICKNAME(std::string(param)), fd);
				return ;
			}
		//	std::string chaMsg = RPL_CHANGEMODE(server->getServerName(), channelName);
			std::string chaMsg = RPL_CHANGEMODE(server->getServerName(), channelName + " "  + option);
			server->sendBroadAllInChannel(chaMsg, server->getChannelByChannelName(channelName));
		
		}
	}
}
