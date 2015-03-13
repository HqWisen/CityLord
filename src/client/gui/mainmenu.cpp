#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent, ClientManagerGUI* cm) :
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
    clientManager->setCurrentWidget(ClientManagerGUI::CREATEGAME);
}

void MainMenu::on_disconnectButton_clicked(){
    clientManager->setCurrentWidget(ClientManagerGUI::LOGIN);
}

void MainMenu::on_quitButton_clicked(){
    clientManager->quit();
    QApplication::quit();
}

void MainMenu::on_joinButton_clicked(){
    clientManager->setCurrentWidget(ClientManagerGUI::JOINGAME);
}

