#ifndef NETMESSAGE_H
#define NETMESSAGE_H

#include <string>

enum class MessageCommand
{
    Message,
    AddUser,
    RemoveUser,
    ServiceMessage,
    ConnectionRequest,
    SuccessConnection
};

struct NetMessage
{
    NetMessage();
    NetMessage(MessageCommand cmd, const std::string &text = "");

    MessageCommand command;
    std::string messageText;
};

#endif // NETMESSAGE_H
