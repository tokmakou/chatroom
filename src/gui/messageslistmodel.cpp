#include "messageslistmodel.h"
#include "QDebug"

MessagesListModel::MessagesListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void MessagesListModel::addMessage(const NetMessage &msg)
{
    auto messageQString = QString::fromStdString(msg.messageText);
    auto time = messageQString.left(messageQString.indexOf("->")).toULongLong();
    messageQString = messageQString.right(messageQString.size() - messageQString.indexOf("->") - 2);

    auto index = std::distance(m_messages.begin(), m_messages.upperBound(time));

    beginInsertRows(QModelIndex(), int(index), int(index));
    m_messages.insert(time, messageQString);
    endInsertRows();
}

void MessagesListModel::clear()
{
    if (m_messages.empty()) return;
    beginRemoveRows(QModelIndex(), 0, m_messages.size() - 1);
    m_messages.clear();
    endRemoveRows();
}

int MessagesListModel::rowCount(const QModelIndex &parent) const
{
    return m_messages.size();
}

QVariant MessagesListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() > m_messages.size())
        return QVariant();

    if (role == Qt::DisplayRole)
        return (m_messages.begin() + index.row()).value();

    return QVariant();

}
