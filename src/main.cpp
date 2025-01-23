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

void testChannelSetGet(Channel & channel)
{

	std::string	topic1 = "Topic_1";
	std::string	key1 = "key_1";
	unsigned long	userLimit = 20;

	std::cout << "----- Test Set/Get Channel VARS -----" << std::endl;
	std::cout << "getChannelName() = " << channel.getChannelName() << std::endl;
	// _inviteChannel
	std::cout << "_inviteChannel : " << std::endl;
	std::cout << "    isInviteChannel() = " << channel.isInviteChannel() << std::endl;
	std::cout << "    setInviteChannel()" << std::endl;
	channel.setInviteChannel();
	std::cout << "    isInviteChannel() = " << channel.isInviteChannel() << std::endl;
	std::cout << "    unsetInviteChannel()" << std::endl;
	channel.unsetInviteChannel();
	std::cout << "    isInviteChannel() = " << channel.isInviteChannel() << std::endl;
	// _topic
	std::cout << "_topic : " << std::endl;
	std::cout << "    getTopic() = " << channel.getTopic() << std::endl;
	std::cout << "    setTopic(" << topic1 << ")" << std::endl;
	channel.setTopic(topic1);
	std::cout << "    getTopic() = " << channel.getTopic() << std::endl;
	// _topicRestricted
	std::cout << "_topicRestricted" << std::endl;
	std::cout << "    isTopicRestricted() = " << channel.isTopicRestricted() << std::endl;
	std::cout << "    setTopicRestricted()" << std::endl;
	channel.setTopicRestricted();
	std::cout << "    isTopicRestricted() = " << channel.isTopicRestricted() << std::endl;
	std::cout << "    unsetTopicRestricted()" << std::endl;
	channel.unsetTopicRestricted();
	std::cout << "    isTopicRestricted() = " << channel.isTopicRestricted() << std::endl;
	// _channelKey
	std::cout << "_channelKey" << std::endl;
	std::cout << "    getChannelKey() = " << channel.getChannelKey() << std::endl;
	std::cout << "    setChannelKey(" << key1 << ")" << std::endl;
	channel.setChannelKey(key1);
	std::cout << "    getChannelKey() = " << channel.getChannelKey() << std::endl;
	// _hasUserLimit
	std::cout << "_hasUserLimit" << std::endl;
	std::cout << "    isUserLimitActived() = " << channel.isUserLimitActived() << std::endl;
	std::cout << "    setUserLimitActived()" << std::endl;
	channel.setUserLimitActived();
	std::cout << "    isUserLimitActived() = " << channel.isUserLimitActived() << std::endl;
	std::cout << "    unsetUserLimitActived()" << std::endl;
	channel.unsetUserLimitActived();
	std::cout << "    isUserLimitActived() = " << channel.isUserLimitActived() << std::endl;
	// _userLimitNumber 
	std::cout << "_userLimitNumber" << std::endl;
	std::cout << "    getUserLimitNumber() = " << channel.getUserLimitNumber() << std::endl;
	std::cout << "    setUserLimitNumber(" << userLimit << ")" << std::endl;
	channel.setUserLimitNumber(userLimit);
	std::cout << "    getUserLimitNumber() = " << channel.getUserLimitNumber() << std::endl;
	// _operators
	std::cout << "_operators" << std::endl;
	std::cout << "    isOperator(nick_2) = " << channel.isOperator(nick_2) << std::endl;
	std::cout << "    addOperator(nick_1)" << std::endl;
	channel.addOperator(nick_1);
	std::cout << "    addOperator(nick_2)" << std::endl;
	channel.addOperator(nick_2);
	std::cout << "    isOperator(nick_1) = " << channel.isOperator(nick_1) << std::endl;
	std::cout << "    isOperator(nick_2) = " << channel.isOperator(nick_2) << std::endl;
	std::cout << "    deleteOperator(nick_1)" << std::endl;
	channel.deleteOperator(nick_1);
	std::cout << "    isOperator(nick_1) = " << channel.isOperator(nick_1) << std::endl;
	std::cout << "    isOperator(nick_2) = " << channel.isOperator(nick_2) << std::endl;
	std::cout << "    deleteOperator(nick_1)" << std::endl;
	channel.deleteOperator(nick_1);
	std::cout << "    deleteOperator(nick_2)" << std::endl;
	channel.deleteOperator(nick_2);
	std::cout << "    isOperator(nick_1) = " << channel.isOperator(nick_1) << std::endl;
	std::cout << "    isOperator(nick_2) = " << channel.isOperator(nick_2) << std::endl;
	// _memberClients
	std::cout << "_memberClients" << std::endl;
	std::cout << "    isMember(nick_2) = " << channel.isMember(nick_2) << std::endl;
	std::cout << "    addMember(nick_1)" << std::endl;
	channel.addMember(nick_1);
	std::cout << "    addMember(nick_2)" << std::endl;
	channel.addMember(nick_2);
	std::cout << "    isMember(nick_1) = " << channel.isMember(nick_1) << std::endl;
	std::cout << "    isMember(nick_2) = " << channel.isMember(nick_2) << std::endl;
	std::cout << "    deleteMember(nick_1)" << std::endl;
	channel.deleteMember(nick_1);
	std::cout << "    isMember(nick_1) = " << channel.isMember(nick_1) << std::endl;
	std::cout << "    isMember(nick_2) = " << channel.isMember(nick_2) << std::endl;
	std::cout << "    deleteMember(nick_1)" << std::endl;
	channel.deleteMember(nick_1);
	std::cout << "    deleteMember(nick_2)" << std::endl;
	channel.deleteMember(nick_2);
	std::cout << "    isMember(nick_1) = " << channel.isMember(nick_1) << std::endl;
	std::cout << "    isMember(nick_2) = " << channel.isMember(nick_2) << std::endl;

	// _invitedClients
	std::cout << "_invitedClients" << std::endl;
	std::cout << "    isInvited(nick_2) = " << channel.isInvited(nick_2) << std::endl;
	std::cout << "    addInvited(nick_1)" << std::endl;
	channel.addInvited(nick_1);
	std::cout << "    addInvited(nick_2)" << std::endl;
	channel.addInvited(nick_2);
	std::cout << "    isInvited(nick_1) = " << channel.isInvited(nick_1) << std::endl;
	std::cout << "    isInvited(nick_2) = " << channel.isInvited(nick_2) << std::endl;
	std::cout << "    deleteInvited(nick_1)" << std::endl;
	channel.deleteInvited(nick_1);
	std::cout << "    isInvited(nick_1) = " << channel.isInvited(nick_1) << std::endl;
	std::cout << "    isInvited(nick_2) = " << channel.isInvited(nick_2) << std::endl;
	std::cout << "    deleteInvited(nick_1)" << std::endl;
	channel.deleteInvited(nick_1);
	std::cout << "    deleteInvited(nick_2)" << std::endl;
	channel.deleteInvited(nick_2);
	std::cout << "    isInvited(nick_1) = " << channel.isInvited(nick_1) << std::endl;
	std::cout << "    isInvited(nick_2) = " << channel.isInvited(nick_2) << std::endl;
	std::cout << "----- END  Test Set/Get Channel VARS -----" << std::endl;
}

void testChannel(Channel & channel)
{
	testChannelSetGet(channel);
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
    return (0);
}
