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

void CreateAccount::on_cancelButton_clicked(){
    clientManager->setCurrentWidget(ClientManager::LOGIN);
}

