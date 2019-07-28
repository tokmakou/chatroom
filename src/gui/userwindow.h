#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QWidget>
#include <simulation/localnetconnector.h>
#include <engine/clientlogic/chatroomclient.h>
#include <QTextEdit>
#include "messageslistmodel.h"

namespace Ui {
class UserWindow;
}

class MessageTextEdit: public QTextEdit
{
    Q_OBJECT
public:
    explicit MessageTextEdit(QWidget *parent = nullptr);

signals:
    void textEditingFinished();

public:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    bool m_shiftPressing = false;
};

class UserWindow : public QWidget, public ChatRoomClient
{
    Q_OBJECT
public:
    explicit UserWindow(QWidget *parent = nullptr);
    ~UserWindow() override;

    // IReceiver interface
    void newMessage(IReceiver &, const NetMessage &message) override;
    std::string receiverName() override;

    // ChatRoomClient interface
    void connectionClosed() override;

private slots:
    void on_connectPushButton_clicked();
    void on_disconnectPushButton_clicked();

    void on_sendMessagePushButton_clicked();

private:
    Ui::UserWindow *ui;
    void connectionSatusChanged(bool status);
    MessagesListModel m_messageModel;
};

#endif // USERWINDOW_H
