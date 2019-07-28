#include <QApplication>
#include <gui/administratorwindow.h>
#include <gui/userwindowfabric.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AdministratorWindow adminstratorWindow;
    adminstratorWindow.show();

    UserWindowFabric userWindowFabric;
    userWindowFabric.show();


    return a.exec();
}

