#include <iostream>
#include "Channel.hpp"
#include "Client.hpp"
#include "Messageprocessing.hpp"
#include "Server.hpp"

std::string			nick_1="nick_1";
std::string			nick_2="nick_2";
std::string			nick_3="nick_3";
std::string			nick_4="nick_4";

void testClient(Client & client)
{
	client.printClientVars();
}

void testChannelSetters(Channel & channel)
{

	std::string	topic1 = "Topic_1";
	std::string	key1 = "key_1";
	unsigned long	userLimit = 20;


	std::cout << "----- Test Setters Channel -----" << std::endl;
	std::cout << "getChannelName() = " << channel.getChannelName() << std::endl;
	std::cout << "_inviteChannel Var: " << channel.isInviteChannel() << std::endl;
	std::cout << "    isInviteChannel() = " << channel.isInviteChannel() << std::endl;
	std::cout << "    setInviteChannel()" << std::endl;
	channel.setInviteChannel();
	std::cout << "    isInviteChannel() = " << channel.isInviteChannel() << std::endl;
	std::cout << "    unsetInviteChannel() = " << std::endl;
	channel.unsetInviteChannel();
	std::cout << "    isInviteChannel() = " << channel.isInviteChannel() << std::endl;
	std::cout << "_topic : " << std::endl;
	std::cout << "    getTopic() = " << channel.getTopic() << std::endl;
	std::cout << "    setTopic(" << topic1 << ")"<< channel.getTopic() << std::endl;
	std::cout << "    getTopic() = " << channel.getTopic() << std::endl;
	std::cout << "_topicRestricted" << std::endl;
	std::cout << "    isTopicRestricted() = " << channel.isTopicRestricted() << std::endl;
	std::cout << "    setTopicRestricted()" << std::endl;
	channel.setTopicRestricted();
	std::cout << "    isTopicRestricted() = " << channel.isTopicRestricted() << std::endl;
	std::cout << "    unsetTopicRestricted()" << std::endl;
	channel.unsetTopicRestricted();
	std::cout << "    isTopicRestricted() = " << channel.isTopicRestricted() << std::endl;
	std::cout << "_channelKey" << std::endl;
	std::cout << "    getChannelKey() = " << channel.getChannelKey() << std::endl;
	std::cout << "    setChannelKey(" << key1 << ")" << std::endl;
	channel.setChannelKey(key1);
	std::cout << "    getChannelKey() = " << channel.getChannelKey() << std::endl;
	std::cout << "_hasUserLimit" << std::endl;
	std::cout << "    isUserLimitActived() = " << channel.isUserLimitActived() << std::endl;
	std::cout << "    setUserLimitActived()" << std::endl;
	std::cout << "    isUserLimitActived() = " << channel.isUserLimitActived() << std::endl;
	std::cout << "    unsetUserLimitActived()" << std::endl;
	channel.unsetUserLimitActived();
	std::cout << "_userLimitNumber" << std::endl;
	std::cout << "    getUserLimitNumber() = " << channel.getUserLimitNumber() << std::endl;
	std::cout << "    setUserLimitNumber(" << userLimit << ")" << std::endl;
	channel.setUserLimitNumber(userLimit);
	std::cout << "    getUserLimitNumber() = " << channel.getUserLimitNumber() << std::endl;
	std::cout << "----- END  Test Setters Channel -----" << std::endl;
}

void testChannel(Channel & channel)
{
	testChannelSetters(channel);
}

int main()
{
	Messageprocessing	messageProcesing;
	Client				client(-1, "IP_CLIENTE");
	Server				server("42_IRC", "hola", 4444);
	Channel				channel1("channel_1", nick_1);

    std::cout << "Executing Messageprocessing !" << std::endl;

	messageProcesing.processMessage("tokenPing!!");

	testClient(client);

// Channel tests
	channel1.printChannelVars();
	
	channel1.addMember(nick_2);
	channel1.addInvited(nick_3);
	channel1.addInvited(nick_4);
	channel1.addInvited(nick_3);

	channel1.printChannelVars();

	testChannel(channel1);
// TODO
// 250122 : no compila si se cambia el *.tpp
// 			revisar popr que no asigna Topic	
    return (0);
}
