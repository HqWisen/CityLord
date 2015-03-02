#ifndef LOGIN_H
#define LOGIN_H

#include "widgetmanager.h"
#include <QWidget>
#include <QStackedWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget*, WidgetManager*, QStackedWidget*);
    ~Login();

private slots:
    void on_loginButton_clicked();

private:
    Ui::Login *ui;
    WidgetManager* widgetManager;
    QStackedWidget* stackedWidget;
};

#endif // LOGIN_H
