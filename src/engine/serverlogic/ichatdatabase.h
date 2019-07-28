#ifndef ICHATDATABASE_H
#define ICHATDATABASE_H

#include <string>
#include <engine/netmessage.h>
#include <functional>

enum class QueryStatus
{
    Success,
    Error
};

class IChatDataBase
{
public:
    virtual ~IChatDataBase();

    struct QueryResult
    {
        QueryResult(QueryStatus status, std::string text = "");
        QueryStatus queryStatus;
        std::string messageText;
    };

    IChatDataBase();

    virtual QueryResult addUser(const std::string & /*user name*/) = 0;
    virtual QueryResult removeUser(const std::string& /*user name*/) = 0;
    virtual QueryResult addUserMessage(const std::string &uname, const NetMessage &) = 0;
    virtual bool containsUser(const std::string &/*user name*/) = 0;
    virtual void allMessagesForUser(const std::string &/*user name*/, std::function<void (const NetMessage &)> sendFunction) = 0;
};

#endif // ICHATDATABASE_H
