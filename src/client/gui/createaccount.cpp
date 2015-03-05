#include "createaccount.h"
#include "ui_createaccount.h"

CreateAccount::CreateAccount(QWidget* parent, ClientManager* cm) :
    DefaultWidget(parent, cm), ui(new Ui::CreateAccount){

    displayDefaultBackground();
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
    clientManager->setRequest("createaccount");
    clientManager->addInfo("username", ui->usernameLineEdit->text().toStdString());
    clientManager->sendRequestAndRecv();
    if(clientManager->requestFailed()){
        ui->errorLabel->setText(QString(clientManager->getFailureReason().c_str()));
    }else{
        clientManager->setCurrentWidget(ClientManager::LOGIN);
    }
}

void CreateAccount::on_cancelButton_clicked(){
    clientManager->setCurrentWidget(ClientManager::LOGIN);
}

