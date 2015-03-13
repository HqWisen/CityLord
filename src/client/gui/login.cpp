#include "login.h"
#include "ui_login.h"

Login::Login(QWidget* parent, ClientManagerGUI* cm) :
    DefaultWidget(parent, cm), ui(new Ui::Login){

    //displayDefaultBackground();
    displayLogo(this,376,357);
    ui->setupUi(this);
    setWindowOpacity(0);
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
        clientManager->setCurrentWidget(ClientManagerGUI::MAINMENU);
    }
}

void Login::on_loginButton_clicked(){
    login();
}

void Login::on_createAccountButton_clicked(){
    clientManager->setCurrentWidget(ClientManagerGUI::CREATEACCOUNT);
}

void Login::on_quitButton_clicked(){
    clientManager->quit();
    QApplication::quit();
}

void Login::on_passwordLineEdit_returnPressed()
{
    login();
}
