#ifndef SERVER_H
#define SERVER_H

#include <engine/ireceiver.h>
#include "ichatdatabase.h"
#include <set>

class Server: public IReceiver
{
public:
    Server(IChatDataBase *chatDataBase);

    // IReceiver interface
    void newMessage(IReceiver &sender, const NetMessage &message) final;
    void connectionClosedWith(IReceiver &receiver) final;
    std::string receiverName() final;

private:
    IChatDataBase *m_chatDataBase;
    std::set <IReceiver *> m_clients;
};

#endif // SERVER_H
