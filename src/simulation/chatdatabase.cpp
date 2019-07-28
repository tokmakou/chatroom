#include "chatdatabase.h"
#include <algorithm>

ChatDataBase::ChatDataBase()
{

}

IChatDataBase::QueryResult ChatDataBase::addUser(const std::string &uname)
{
    auto insertionResult = m_users.insert(std::make_pair(uname,
                                                         std::chrono::duration_cast<std::chrono::milliseconds>
                                                         (std::chrono::system_clock::now().time_since_epoch())));

    if (insertionResult.second)
        return QueryResult(QueryStatus::Success, "User " + uname + " successfully added");
    else
        return QueryResult(QueryStatus::Error, "User named " + uname + " already exists");
}

IChatDataBase::QueryResult ChatDataBase::removeUser(const std::string &uname)
{
    auto user = m_users.find(uname);

    if (user == m_users.end())
        return QueryResult(QueryStatus::Error, "User with name '" + uname + "' not found");
    else
    {
        m_users.erase(user);
        return QueryResult(QueryStatus::Success, "User " + uname + " successfully removed");
    }
}

IChatDataBase::QueryResult ChatDataBase::addUserMessage(const std::string &uname, const NetMessage &message)
{
    if (m_users.find(uname) != m_users.end()){

        UserMessages &messages = m_messages[uname];

        std::string messageText = message.messageText;
        messageText = messageText.substr(messageText.find("->") + 2, messageText.size());
        messageText = messageText.substr(messageText.find("->") + 2, messageText.size());

        messages.insert(std::make_pair(
                            std::chrono::duration_cast<std::chrono::milliseconds>
                            (std::chrono::system_clock::now().time_since_epoch()),
                            messageText));

        return QueryResult(QueryStatus::Success);
    }
    else
        return QueryResult(QueryStatus::Error);
}

void ChatDataBase::allMessagesForUser(const std::string &uname, std::function<void (const NetMessage &)> sendFunction)
{
    auto userIterator = m_users.find(uname);
    std::chrono::milliseconds userRegisteredTime;

    if (userIterator == m_users.end())
        return;
    else
        userRegisteredTime = userIterator->second;

    for (auto userMessageMap: m_messages){
        std::for_each(userMessageMap.second.lower_bound(userRegisteredTime), userMessageMap.second.end(),
                      [&sendFunction, &userMessageMap](const UserMessages::value_type &message){
            sendFunction(NetMessage(MessageCommand::Message,
                                    std::to_string(message.first.count()) + "->"
                                    + userMessageMap.first + "->"
                                    + message.second));
        });
    };
}

bool ChatDataBase::containsUser(const std::string &user){
    return (m_users.find(user) != m_users.end());
}
