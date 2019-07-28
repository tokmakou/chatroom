#include "localnetconnector.h"
#include "chatdatabase.h"

LocalNetConnector::LocalNetConnector():
    m_dataBase(new ChatDataBase()),
    m_server(new Server(m_dataBase.get()))
{

}

LocalNetConnector &LocalNetConnector::instance()
{
    static LocalNetConnector a;
    return a;
}

IReceiver &LocalNetConnector::getServerReceiver()
{
    return *m_server.get();
}
