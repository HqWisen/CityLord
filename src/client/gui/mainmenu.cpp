#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent, ClientManager* cm) :
    DefaultWidget(parent, cm), ui(new Ui::MainMenu){

    displayDefaultBackground();
    displayLogo(this,376,200);
    ui->setupUi(this);
}

MainMenu::~MainMenu(){
    delete ui;
}

void MainMenu::refresh(){
}

void MainMenu::on_createButton_clicked(){
    clientManager->setCurrentWidget(ClientManager::CREATEGAME);
}

void MainMenu::on_disconnectButton_clicked(){
    clientManager->setCurrentWidget(ClientManager::LOGIN);
}

void MainMenu::on_quitButton_clicked(){
    /*clientManager->quit();
    QApplication::quit();*/
    clientManager->setCurrentWidget(ClientManager::INGAME);
}

void MainMenu::on_joinButton_clicked(){
    clientManager->setCurrentWidget(ClientManager::JOINGAME);
}

/*
void MainMenu::on_create_pushButton_clicked()
{
    QMessageBox::warning(this, "Create", "Make a Create Function");
}



void MainMenu::on_quit_pushButton_clicked()
{
    QMessageBox::warning(this, "Quit", "Make a Quit Function");
}
*/

