#ifndef LOGINWINDOW_HPP
#define LOGINWINDOW_HPP

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>
#include <QLabel>


#include <iostream>
#include<string>

#include "../../common/socket/SocketMessage.hpp"

class LoginWindow : public QWidget
{
    Q_OBJECT;
    public:
    LoginWindow();

    public slots:
    void loginFunction();
    void createFunction();

    private:
	
    QPushButton *m_loginButton;
    QPushButton *m_createButton;
    QLineEdit *m_usernameEntry;
    QLineEdit *m_pwdEntry;
};



#endif // LOGINWINDOW_HPP
