#include "createaccount.h"
#include "ui_createaccount.h"

CreateAccount::CreateAccount(QWidget* parent, ClientManagerGUI* cm) :
    DefaultWidget(parent, cm), ui(new Ui::CreateAccount){

    displayDefaultBackground();
    displayLogo(this,376,200);
    //displayLogo(this,376,357);
    ui->setupUi(this);
}
CreateAccount::~CreateAccount(){
    delete ui;
}

void CreateAccount::refresh(){
    ui->errorLabel->setText("");
    ui->usernameLineEdit->setText("");
    ui->passwordLineEdit->setText("");
    ui->retypePasswordLineEdit->setText("");
}

void CreateAccount::on_createButton_clicked(){
    std::string username, password, retypePassword;
    username = ui->usernameLineEdit->text().toStdString();
    password = ui->passwordLineEdit->text().toStdString();
    retypePassword = ui->retypePasswordLineEdit->text().toStdString();
    if(username.empty()){
        ui->errorLabel->setText("Username can't be empty.");
    }else if(password.empty()){
        ui->errorLabel->setText("Password can't be empty.");
    }else if(password != retypePassword){
        ui->errorLabel->setText("Password and retype password are different.");
    }else{
        clientManager->setRequest("createaccount");
        clientManager->addInfo("username", username);
        clientManager->addInfo("password", password);
        clientManager->sendRequestAndRecv();
        if(clientManager->requestFailed()){
            ui->errorLabel->setText(QString(clientManager->getReason().c_str()));
        }else{
            clientManager->setCurrentWidget(ClientManagerGUI::MAINMENU);
            std::string message = "The account '"+username+"' has been successfully created !";
            QMessageBox::information(this, "Create account", message.c_str());

        }
    }
}

void CreateAccount::on_cancelButton_clicked(){
    clientManager->setCurrentWidget(ClientManagerGUI::LOGIN);
}

