#include "userwindowfabric.h"
#include "ui_userwindowfabric.h"
#include "userwindow.h"

UserWindowFabric::UserWindowFabric(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserWindowFabric)
{
    ui->setupUi(this);
}

UserWindowFabric::~UserWindowFabric()
{
    delete ui;
}

void UserWindowFabric::on_pushButton_clicked()
{
    auto userWindow = new UserWindow();
    userWindow->setAttribute(Qt::WA_DeleteOnClose);
    userWindow->show();
}
