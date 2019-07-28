#ifndef IRECEIVER_H
#define IRECEIVER_H

#include "netmessage.h"

/*!
 * \brief The IReceiver class
 * Получателем может быть и сервер и клиент
 */
class IReceiver
{   
public:
    IReceiver();
    virtual ~IReceiver();

    virtual void newMessage(IReceiver &, const NetMessage&) = 0;
    virtual void connectionClosedWith(IReceiver&) = 0;
    virtual void connectionAllowed(IReceiver&/*server*/) {}
    virtual std::string receiverName() = 0;
};

#endif // IRECEIVER_H
