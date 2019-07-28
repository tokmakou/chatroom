#ifndef CHATDATABASE_H
#define CHATDATABASE_H

#include <engine/serverlogic/ichatdatabase.h>
#include <unordered_map>
#include <map>
#include <chrono>

class ChatDataBase: public IChatDataBase
{
public:
    ChatDataBase();

    // IChatDataBase interface
    QueryResult addUser(const std::string &uname) final;
    QueryResult removeUser(const std::string &uname) final;
    QueryResult addUserMessage(const std::string &uname, const NetMessage &message) final;
    void allMessagesForUser(const std::string &uname, std::function<void (const NetMessage &)> sendFunction) final;
    bool containsUser(const std::string &user);


private:
    using UserMessages = std::map<std::chrono::milliseconds, std::string>;
    std::unordered_map<std::string, UserMessages> m_messages;
    std::map<std::string, std::chrono::milliseconds> m_users;
};

#endif // CHATDATABASE_H
