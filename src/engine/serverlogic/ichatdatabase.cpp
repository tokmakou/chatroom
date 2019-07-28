#include "ichatdatabase.h"

IChatDataBase::~IChatDataBase()
{

}

IChatDataBase::IChatDataBase()
{

}

IChatDataBase::QueryResult::QueryResult(QueryStatus status, std::string text):
    queryStatus(status),
    messageText(text)

{

}
