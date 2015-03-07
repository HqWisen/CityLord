#include "creategame.h"
#include "ui_creategame.h"

const std::string CreateGame::MAP1PICTURE = "src/resources/img/citybay.jpg";
const std::string CreateGame::MAP2PICTURE = "src/resources/img/roadred.jpg";
const std::string CreateGame::CLICKCOLOR = "#B70101";
const std::string CreateGame::UNCLICKCOLOR = "black";


CreateGame::CreateGame(QWidget* parent, ClientManager* cm) :
    DefaultWidget(parent, cm), ui(new Ui::CreateGame){

    displayDefaultBackground();
    ui->setupUi(this);
    refresh();

}

CreateGame::~CreateGame(){
    delete ui;
}

void CreateGame::refresh(){
    ui->map1Button->setStyleSheet(getStyleSheet(MAP1PICTURE, UNCLICKCOLOR));
    ui->map2Button->setStyleSheet(getStyleSheet(MAP2PICTURE, UNCLICKCOLOR));
    ui->map1Button->setText("CITYBAY");
    ui->map2Button->setText("ROADRED");
    ui->createButton->setEnabled(false);
}


void CreateGame::on_map1Button_clicked(){
    ui->map1Button->setStyleSheet(getStyleSheet(MAP1PICTURE, CLICKCOLOR));
    ui->map2Button->setStyleSheet(getStyleSheet(MAP2PICTURE, UNCLICKCOLOR));
    ui->createButton->setEnabled(true);
    choice = 1;
}

void CreateGame::on_map2Button_clicked(){
    ui->map1Button->setStyleSheet(getStyleSheet(MAP1PICTURE, UNCLICKCOLOR));
    ui->map2Button->setStyleSheet(getStyleSheet(MAP2PICTURE, CLICKCOLOR));
    ui->createButton->setEnabled(true);
    choice = 2;
}

void CreateGame::on_createButton_clicked(){
    clientManager->setRequest("createcity");
    clientManager->addInfo("number", std::to_string(choice));
    clientManager->sendRequestAndRecv();
    if(clientManager->requestFailed()){
        // TODO handle failure
    }else{
        clientManager->setCurrentWidget(ClientManager::MAINMENU);
    }
}

void CreateGame::on_cancelButton_clicked(){
    clientManager->setCurrentWidget(ClientManager::MAINMENU);
}

QString CreateGame::getStyleSheet(std::string picture, std::string color){
    std::string result = "";
    result += "background-image: url(" + picture + ");";
    result += "background-color:"+color+";";
    result += "font: bold 50px; color:"+color+";";
    result += "border : 4px solid "+color+";";
    return result.c_str();
}
