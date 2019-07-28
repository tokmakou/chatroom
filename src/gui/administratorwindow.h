#ifndef ADMINISTRATORWINDOW_H
#define ADMINISTRATORWINDOW_H

#include <QWidget>
#include <simulation/localnetconnector.h>
#include <QStringListModel>

namespace Ui {
class AdministratorWindow;
}

class AdministratorWindow : public QWidget, public IReceiver
{
    Q_OBJECT

public:
    explicit AdministratorWindow(QWidget *parent = nullptr);
    ~AdministratorWindow();
    // IReceiver interface
    void newMessage(IReceiver &server, const NetMessage &message);
    void connectionClosedWith(IReceiver &);
    std::string receiverName();

private:
    void addUserFromLineEdit();

private slots:
    void on_excludeUserPushButton_clicked();
    void on_addUserPushButton_clicked();
    void on_newUserNameLineEdit_textChanged(const QString &arg1);
    void on_newUserNameLineEdit_textEdited(const QString &arg1);


    void on_newUserNameLineEdit_returnPressed();

private:
    Ui::AdministratorWindow *ui;
    QStringListModel *stringListModel;
    IReceiver *m_server;
};

#endif // ADMINISTRATORWINDOW_H
