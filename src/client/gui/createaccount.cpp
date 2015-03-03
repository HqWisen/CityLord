#include "createaccount.h"
#include "ui_createaccount.h"

CreateAccount::CreateAccount(QWidget* parent, WidgetManager* wm) :
    DefaultWidget(parent, wm), ui(new Ui::CreateAccount){

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
    widgetManager->setCurrentWidget(WidgetManager::LOGIN);
}

