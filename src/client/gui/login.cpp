#include "login.h"
#include "ui_login.h"

Login::Login(QWidget* parent, WidgetManager* wm, QStackedWidget* sw) :
    QWidget(parent), ui(new Ui::Login), widgetManager(wm), stackedWidget(sw)
{
    QWidget *frame = new QWidget(this);
    frame->setGeometry(0, 0, 1152, 864);
    frame->setStyleSheet("background-image: url(src/resources/img/BgCityBig.jpg)");

    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginButton_clicked(){
    if(ui->usernameLineEdit->text()=="Fish" && ui->passwordLineEdit->text()=="123"){
        ui->errorLabel->setText("");
        stackedWidget->setCurrentWidget(widgetManager->getMainMenuPage());
    }else{
        ui->errorLabel->setText("Username doesn't match the password.");
    }
}
