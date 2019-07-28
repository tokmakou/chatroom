#include "server.h"
#include <stdexcept>
#include <algorithm>

Server::Server(IChatDataBase *chatDataBase):
    m_chatDataBase(chatDataBase)
{
    if (!chatDataBase)
        throw std::runtime_error("initialising chat server without database");
}

void Server::newMessage(IReceiver &sender, const NetMessage &message)
{

    switch (message.command) {
    case MessageCommand::Message:
    {
        auto result = m_chatDataBase->addUserMessage(sender.receiverName(), message);
        if (result.queryStatus == QueryStatus::Success)
            std::for_each(m_clients.begin(), m_clients.end(), [this, &message](IReceiver *receiver){
                receiver->newMessage(*this, message);
            });
        break;
    }

    case MessageCommand::AddUser:
    {
        auto result = m_chatDataBase->addUser(message.messageText);
        sender.newMessage(*this, NetMessage(MessageCommand::ServiceMessage, result.messageText));
        break;
    }

    case MessageCommand::RemoveUser:
    {
        auto result = m_chatDataBase->removeUser(message.messageText);
        sender.newMessage(*this, NetMessage(MessageCommand::ServiceMessage, result.messageText));

        for(auto it = m_clients.begin(); it != m_clients.end(); )
            if(it.operator*()->receiverName() == message.messageText)
            {
                it.operator*()->newMessage(*this, NetMessage(MessageCommand::ServiceMessage, "Вы исключены из чата"));
                it.operator*()->connectionClosedWith(*this);
                it = m_clients.erase(it);
            }
            else
                ++it;

        break;
    }

    case MessageCommand::ConnectionRequest:
    {
        if (m_chatDataBase->containsUser(message.messageText))
        {
            if (std::find_if(m_clients.begin(), m_clients.end(), [&sender](IReceiver *client){
                             return (client->receiverName() == sender.receiverName());})
                    == m_clients.end())
            {
                m_clients.insert(&sender);
                sender.connectionAllowed(*this);
                sender.newMessage(*this, NetMessage(MessageCommand::SuccessConnection, ""));
                m_chatDataBase->allMessagesForUser(sender.receiverName(), [&sender, this](const NetMessage& m){
                    sender.newMessage(*this, m);
                });
            }
            else {
                sender.newMessage(*this, NetMessage(MessageCommand::ServiceMessage, "User "
                                                      + sender.receiverName() + " is already chatting"));
            }

        }
        else {
            sender.newMessage(*this, NetMessage(MessageCommand::ServiceMessage, "User "
                                                  + sender.receiverName() + " not found"));
        }
    }

    default: break;
    }
}

void Server::connectionClosedWith(IReceiver &receiver)
{
    m_clients.erase(&receiver);
    receiver.connectionClosedWith(*this);
}

std::string Server::receiverName()
{
    return "*server*";
}
