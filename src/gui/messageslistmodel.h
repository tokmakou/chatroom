#ifndef MESSAGESLISTMODEL_H
#define MESSAGESLISTMODEL_H

#include <QAbstractListModel>
#include <engine/netmessage.h>

class MessagesListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit MessagesListModel(QObject *parent = nullptr);

    void addMessage(const NetMessage &msg);
    void clear();

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QMultiMap<quint64, QString> m_messages;
};

#endif // MESSAGESLISTMODEL_H
