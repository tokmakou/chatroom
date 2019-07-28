#include "administratorwindow.h"
#include "ui_administratorwindow.h"
#include <QMessageBox>

AdministratorWindow::AdministratorWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdministratorWindow),
    stringListModel(new QStringListModel),
    m_server(&LocalNetConnector::instance().getServerReceiver())
{
    ui->setupUi(this);

    QRegularExpression regex("^[a-zA-Z0-9]*$");
    QValidator *validator = new QRegularExpressionValidator(regex, this);
    ui->newUserNameLineEdit->setValidator(validator);

    ui->userListView->setModel(stringListModel);
}

AdministratorWindow::~AdministratorWindow()
{
    delete ui;
}

void AdministratorWindow::newMessage(IReceiver &, const NetMessage &message)
{
    if (message.command == MessageCommand::ServiceMessage)
    {
        QMessageBox msgBox(this);
        msgBox.setText(QString::fromStdString(message.messageText));
        msgBox.exec();

        auto messageQString = QString::fromStdString(message.messageText);
        auto stringList = stringListModel->stringList();

        if (messageQString.contains(QRegularExpression("User [^>]+ successfully added")))
        {
            if (!stringList.contains(messageQString.split(" ").at(1)))
            {
                stringList << messageQString.split(" ").at(1);
                stringListModel->setStringList(stringList);
            }
        }

        if (QString::fromStdString(message.messageText).contains(QRegularExpression("User [^>]+ successfully removed")))
        {
            stringList.removeOne(messageQString.split(" ").at(1));
            stringListModel->setStringList(stringList);
        }
    }
}

void AdministratorWindow::connectionClosedWith(IReceiver &)
{

}

std::string AdministratorWindow::receiverName()
{
    return "*server ui*";
}

void AdministratorWindow::addUserFromLineEdit()
{
    if (ui->newUserNameLineEdit->text() == "") return;
    m_server->newMessage(*this, NetMessage(MessageCommand::AddUser,
                         ui->newUserNameLineEdit->text().toStdString()));
    ui->newUserNameLineEdit->setText("");
}

void AdministratorWindow::on_excludeUserPushButton_clicked()
{
    auto userNameForRemove = ui->userListView->selectionModel()->currentIndex().data().toString();

    if (userNameForRemove != "")
        m_server->newMessage(*this,
                             NetMessage(MessageCommand::RemoveUser, userNameForRemove.toStdString()));
}

void AdministratorWindow::on_addUserPushButton_clicked()
{
    addUserFromLineEdit();
}

void AdministratorWindow::on_newUserNameLineEdit_textEdited(const QString &arg1)
{
    ui->addUserPushButton->setEnabled(arg1 != "");
}

void AdministratorWindow::on_newUserNameLineEdit_textChanged(const QString &arg1)
{
    ui->addUserPushButton->setEnabled(arg1 != "");
}

void AdministratorWindow::on_newUserNameLineEdit_returnPressed()
{
    addUserFromLineEdit();
}
