#include "chatroomclient.h"

void ChatRoomClient::connect(IReceiver &server)
{
    server.newMessage(*this,
                      NetMessage(MessageCommand::ConnectionRequest,
                                 receiverName()));
}

void ChatRoomClient::disconnect()
{
    if (m_server)
        m_server->connectionClosedWith(*this);
}

void ChatRoomClient::sendMessage(const NetMessage &message){
    if (m_server)
        m_server->newMessage(*this, message);
}

void ChatRoomClient::connectionClosedWith(IReceiver &server)
{
    if (m_server == &server)
        connectionClosed();
    m_server = nullptr;
}

void ChatRoomClient::connectionAllowed(IReceiver &server)
{
    m_server = &server;
}

ChatRoomClient::ChatRoomClient():
    m_server(nullptr)
{

}

ChatRoomClient::~ChatRoomClient()
{
    if (m_server)
        m_server->connectionClosedWith(*this);
}
