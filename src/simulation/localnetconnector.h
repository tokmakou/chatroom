#ifndef LOCALNETCONNECTOR_H
#define LOCALNETCONNECTOR_H

#include <engine/serverlogic/server.h>
#include <memory>

class LocalNetConnector
{
public:
    static LocalNetConnector &instance();
    IReceiver &getServerReceiver();

private:
    LocalNetConnector();
    std::unique_ptr<IChatDataBase> m_dataBase;
    std::unique_ptr<Server> m_server;
};

#endif // LOCALNETCONNECTOR_H
