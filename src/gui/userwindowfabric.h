#ifndef USERWINDOWFABRIC_H
#define USERWINDOWFABRIC_H

#include <QWidget>

namespace Ui {
class UserWindowFabric;
}

class UserWindowFabric : public QWidget
{
    Q_OBJECT

public:
    explicit UserWindowFabric(QWidget *parent = nullptr);
    ~UserWindowFabric();

private slots:
    void on_pushButton_clicked();

private:
    Ui::UserWindowFabric *ui;
};

#endif // USERWINDOWFABRIC_H
