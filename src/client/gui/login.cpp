#include "login.h"
#include "ui_login.h"

Login::Login(QWidget* parent, WidgetManager* wm) :
    DefaultWidget(parent, wm), ui(new Ui::Login){

    displayDefaultBackground();
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
        widgetManager->setCurrentWidget(WidgetManager::MAINMENU);
    }else{
        ui->errorLabel->setText("Username doesn't match the password.");
    }
}

void Login::on_createAccountButton_clicked(){
    widgetManager->setCurrentWidget(WidgetManager::CREATEACCOUNT);

}

void Login::on_quitButton_clicked(){
    QApplication::quit();
}
