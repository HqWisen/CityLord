#include "login.h"
#include "ui_login.h"

Login::Login(QWidget* parent, ClientManager* cm) :
    DefaultWidget(parent, cm), ui(new Ui::Login){

    displayDefaultBackground();
    displayLogo(this,376,357);
    ui->setupUi(this);
}

Login::~Login(){
    delete ui;
}

void Login::refresh(){
    ui->errorLabel->setText("");
    ui->usernameLineEdit->setText("");
    ui->passwordLineEdit->setText("");
}

void Login::on_loginButton_clicked(){
    if(ui->usernameLineEdit->text()=="Fish" && ui->passwordLineEdit->text()=="123"){
        ui->errorLabel->setText("");
        clientManager->setCurrentWidget(ClientManager::MAINMENU);
    }else{
        ui->errorLabel->setText("Username doesn't match the password.");
    }
}

void Login::on_createAccountButton_clicked(){
    clientManager->setCurrentWidget(ClientManager::CREATEACCOUNT);
}

void Login::on_quitButton_clicked(){
    clientManager->quit();
    QApplication::quit();
}

void Login::on_passwordLineEdit_returnPressed()
{
    if(ui->usernameLineEdit->text()=="Fish" && ui->passwordLineEdit->text()=="123"){
        ui->errorLabel->setText("");
        clientManager->setCurrentWidget(ClientManager::MAINMENU);
    }else{
        ui->errorLabel->setText("Username doesn't match the password.");
    }
}
