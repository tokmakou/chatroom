#include "userwindow.h"
#include "ui_userwindow.h"
#include <QMessageBox>
#include <QDateTime>
#include <QKeyEvent>
#include <QAbstractScrollArea>

UserWindow::UserWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserWindow)
{
    ui->setupUi(this);
    connectionSatusChanged(false);
    QObject::connect(ui->messageTextEdit, & MessageTextEdit::textEditingFinished,
                     this, &UserWindow::on_sendMessagePushButton_clicked);

    ui->messagesListView->setModel(&m_messageModel);
}

UserWindow::~UserWindow()
{
    delete ui;
}

void UserWindow::newMessage(IReceiver &sender, const NetMessage &message)
{

    switch (message.command) {
    case MessageCommand::ServiceMessage:
    {
        QMessageBox msgBox(this);
        msgBox.setText(QString::fromStdString(sender.receiverName() + ": " + message.messageText));
        msgBox.exec();
        break;
    }
    case MessageCommand::SuccessConnection:
    {
        if (&LocalNetConnector::instance().getServerReceiver() == &sender)
            connectionSatusChanged(true);
        break;
    }
    case MessageCommand::Message:
    {
        m_messageModel.addMessage(message);
        ui->messagesListView->scrollToBottom();
        break;
    }


    default: break;
    }
}

std::string UserWindow::receiverName()
{
    return ui->userNamelineEdit->text().toStdString();
}

void UserWindow::connectionClosed()
{
    connectionSatusChanged(false);
}

void UserWindow::connectionSatusChanged(bool status)
{
    ui->userNamelineEdit->setEnabled(!status);
    ui->connectPushButton->setEnabled(!status);

    ui->disconnectPushButton->setEnabled(status);
    ui->messageTextEdit->setEnabled(status);
    ui->messagesListView->setEnabled(status);
    ui->sendMessagePushButton->setEnabled(status);

    m_messageModel.clear();
}

void UserWindow::on_connectPushButton_clicked()
{
    if (ui->userNamelineEdit->text() == "") return;

    ChatRoomClient::connect(LocalNetConnector::instance().getServerReceiver());
}

void UserWindow::on_disconnectPushButton_clicked()
{
    ChatRoomClient::disconnect();
}

void UserWindow::on_sendMessagePushButton_clicked()
{
    if (ui->messageTextEdit->toPlainText() == "") return;

    NetMessage message(MessageCommand::Message);
    message.messageText = QString::number(QDateTime::currentMSecsSinceEpoch()).toStdString() + "->" + receiverName() +
            "->" + ui->messageTextEdit->toPlainText().toStdString();
    sendMessage(message);

    ui->messageTextEdit->setPlainText("");
}

MessageTextEdit::MessageTextEdit(QWidget *parent):
    QTextEdit (parent)
{

}

void MessageTextEdit::keyPressEvent(QKeyEvent *event)
{

    switch (event->key()) {
    case Qt::Key_Return:

        if (m_shiftPressing)
            QTextEdit::keyPressEvent(event);
        else
            textEditingFinished();

        break;

    case Qt::Key_Shift:
        m_shiftPressing = true;
        QTextEdit::keyPressEvent(event);
        break;

    default:
        QTextEdit::keyPressEvent(event);
    }
}

void MessageTextEdit::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Shift)
            m_shiftPressing = false;

    QTextEdit::keyPressEvent(event);
}
