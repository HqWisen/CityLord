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

void Login::login(){
    std::string username, password;
    username = ui->usernameLineEdit->text().toStdString();
    password = ui->passwordLineEdit->text().toStdString();
    clientManager->setRequest("login");
    clientManager->addInfo("username", username);
    clientManager->addInfo("password", password);
    clientManager->sendRequestAndRecv();
    if(clientManager->requestFailed()){
        ui->errorLabel->setText(clientManager->getFailureReason().c_str());
    }else{
        clientManager->setCurrentWidget(ClientManager::MAINMENU);
    }
}

void Login::on_loginButton_clicked(){
    login();
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
    login();
}
