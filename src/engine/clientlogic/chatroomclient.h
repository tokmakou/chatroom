#ifndef CHATROOMCLIENT_H
#define CHATROOMCLIENT_H

#include <engine/ireceiver.h>

class ChatRoomClient: public IReceiver
{
public:
    ChatRoomClient();
    ~ChatRoomClient();

    void connect(IReceiver &server);
    void disconnect();
    void sendMessage(const NetMessage &message);

    virtual void connectionClosed() {}
    virtual void successConnection() {}

private:
    // IReceiver interface
    void connectionClosedWith(IReceiver &server) final;
    void connectionAllowed(IReceiver &server) final;

    IReceiver *m_server;
};

#endif // CHATROOMCLIENT_H
