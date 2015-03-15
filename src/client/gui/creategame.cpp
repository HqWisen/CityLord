#include "creategame.h"
#include "ui_creategame.h"

const std::string CreateGame::MAP1PICTURE = "src/resources/img/citybay360_250.jpg";
const std::string CreateGame::MAP2PICTURE = "src/resources/img/roadred360_250.jpg";
const std::string CreateGame::MAP3PICTURE = "src/resources/img/equaland360_250.jpg";
const std::string CreateGame::CLICKCOLOR = "#B70101";
const std::string CreateGame::UNCLICKCOLOR = "black";


CreateGame::CreateGame(QWidget* parent, ClientManagerGUI* cm) :
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
    ui->map3Button->setStyleSheet(getStyleSheet(MAP3PICTURE, UNCLICKCOLOR));
    ui->map1Button->setText("CITYBAY");
    ui->map2Button->setText("ROADRED");
    ui->map3Button->setText("EQUALAND");
    ui->createButton->setEnabled(false);
}


void CreateGame::on_map1Button_clicked(){
    ui->map1Button->setStyleSheet(getStyleSheet(MAP1PICTURE, CLICKCOLOR));
    ui->map2Button->setStyleSheet(getStyleSheet(MAP2PICTURE, UNCLICKCOLOR));
    ui->map3Button->setStyleSheet(getStyleSheet(MAP3PICTURE, UNCLICKCOLOR));
    ui->createButton->setEnabled(true);
    choice = 1;
}

void CreateGame::on_map2Button_clicked(){
    ui->map1Button->setStyleSheet(getStyleSheet(MAP1PICTURE, UNCLICKCOLOR));
    ui->map2Button->setStyleSheet(getStyleSheet(MAP2PICTURE, CLICKCOLOR));
    ui->map3Button->setStyleSheet(getStyleSheet(MAP3PICTURE, UNCLICKCOLOR));
    ui->createButton->setEnabled(true);
    choice = 2;
}

void CreateGame::on_map3Button_clicked(){
    ui->map1Button->setStyleSheet(getStyleSheet(MAP1PICTURE, UNCLICKCOLOR));
    ui->map2Button->setStyleSheet(getStyleSheet(MAP2PICTURE, UNCLICKCOLOR));
    ui->map3Button->setStyleSheet(getStyleSheet(MAP3PICTURE, CLICKCOLOR));
    ui->createButton->setEnabled(true);
    choice = 3;
}

void CreateGame::on_createButton_clicked(){
    clientManager->setRequest("createcity");
    clientManager->addInfo("number", std::to_string(choice));
    clientManager->sendRequestAndRecv();
    if(clientManager->requestFailed()){
        // TODO handle failure
    }else{
        clientManager->setCurrentWidget(ClientManagerGUI::JOINGAME);
    }
}

void CreateGame::on_cancelButton_clicked(){
    clientManager->setCurrentWidget(ClientManagerGUI::MAINMENU);
}

QString CreateGame::getStyleSheet(std::string picture, std::string color){
    std::string result = "";
    result += "background-image: url(" + picture + ");";
    result += "background-color:"+color+";";
    result += "font: bold 50px; color:"+color+";";
    result += "border : 4px solid "+color+";";
    return result.c_str();
}
