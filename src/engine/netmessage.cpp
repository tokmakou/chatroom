#include "netmessage.h"

NetMessage::NetMessage()
{

}

NetMessage::NetMessage(MessageCommand cmd, const std::string &text):
    command(cmd),
    messageText(text)
{

}
