#ifndef LOGIN_H
#define LOGIN_H

#include "defaultwidget.h"

namespace Ui {
class Login;
}

class Login : public DefaultWidget{
    Q_OBJECT
public:
    explicit Login(QWidget*, ClientManager*);
    ~Login();
    void refresh() override;
private slots:
    void on_loginButton_clicked();
    void on_createAccountButton_clicked();
    void on_quitButton_clicked();

    void on_passwordLineEdit_returnPressed();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
