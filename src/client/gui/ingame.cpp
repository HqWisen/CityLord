#include "ingame.h"
#include "ui_ingame.h"


InGame::InGame(QWidget* parent, ClientManagerGUI* cm) :
    DefaultWidget(parent, cm), ui(new Ui::InGame), view(new CityLordView(this)){
    view->setClientManager(clientManager);
    ui->setupUi(this);
    QObject::connect(clientManager->getRepaintSignaler(), SIGNAL(repaintView()), this, SLOT(repaintView()));
    QObject::connect(clientManager->getRepaintSignaler(), SIGNAL(activeButton(std::string, Location)), this, SLOT(activeButton(std::string, Location)));
    ui->exitButton->setStyleSheet("background-image: url(src/resources/img/exit40_40.png)");
    ui->exitButton->setText("");

    ui->buildButton->setEnabled(false);
    ui->buyButton->setEnabled(false);
    ui->upgradeButton->setEnabled(false);
    ui->destroyButton->setEnabled(false);
    ui->sellButton->setEnabled(false);
}
void InGame::repaintView(){
    view->repaintView();
}

void InGame::activeButton(std::string info, Location location){
    lastLocation = location;
    if(info == "owner"){
        ui->buildButton->setEnabled(true);
        ui->buyButton->setEnabled(false);
        ui->upgradeButton->setEnabled(true);
        ui->destroyButton->setEnabled(true);
    }else if(info == "purchasable"){
        ui->buildButton->setEnabled(false);
        ui->buyButton->setEnabled(true);
        ui->upgradeButton->setEnabled(false);
        ui->destroyButton->setEnabled(false);
    }else if(info == "other"){
        ui->buildButton->setEnabled(false);
        ui->buyButton->setEnabled(false);
        ui->upgradeButton->setEnabled(false);
        ui->destroyButton->setEnabled(false);
    }else if(info == "notfield"){
        ui->buildButton->setEnabled(false);
        ui->buyButton->setEnabled(false);
        ui->upgradeButton->setEnabled(false);
        ui->destroyButton->setEnabled(false);
    }
}

InGame::~InGame(){
    delete ui;
    delete view;
}

void InGame::refresh(){
}

void InGame::updateMoney(int amount){
    if(amount>0){ui->moneyLabel->setStyleSheet("QLabel { color:rgb(0, 220, 0); }");}
    else{ui->moneyLabel->setStyleSheet(ui->moneyLabel->styleSheet() + "QLabel { color : red; }");};\
    std::ostringstream moneyStr;
    moneyStr << amount << " $";
    ui->moneyLabel->setText(QString::fromStdString(moneyStr.str()));
}

void InGame::updateTime(int time){
    int hours,minutes;
    hours=time/60;
    minutes=time%60;

    std::ostringstream timeStr;
    timeStr << hours <<" : "<< minutes;
    //std::string timeStr = std::to_string(hours) + " : " + std::to_string(minutes);
    ui->timeLabel->setText(QString::fromStdString(timeStr.str()));
}

void InGame::on_buyButton_clicked(){
    clientManager->setRequest("buy");
    clientManager->addInfo("row", std::to_string(lastLocation.getRow()));
    clientManager->addInfo("col", std::to_string(lastLocation.getCol()));
    clientManager->sendRequestAndRecv();
    QMessageBox::warning(this, "Buy", clientManager->getAnswerInfos().c_str());
    activeButton("owner", lastLocation);
}

void InGame::on_buildButton_clicked()
{

    clientManager->setRequest("build");
    clientManager->addInfo("row", std::to_string(lastLocation.getRow()));
    clientManager->addInfo("col", std::to_string(lastLocation.getCol()));
    clientManager->setCurrentWidget(ClientManagerGUI::BUILD);
}

void InGame::on_upgradeButton_clicked()
{
    clientManager->setRequest("upgrade");
    clientManager->addInfo("row", std::to_string(lastLocation.getRow()));
    clientManager->addInfo("col", std::to_string(lastLocation.getCol()));
    clientManager->sendRequestAndRecv();
    QMessageBox::warning(this, "Upgrade", clientManager->getAnswerInfos().c_str());

}

void InGame::on_destroyButton_clicked()
{
    clientManager->setRequest("destroy");
    clientManager->addInfo("row", std::to_string(lastLocation.getRow()));
    clientManager->addInfo("col", std::to_string(lastLocation.getCol()));
    clientManager->sendRequestAndRecv();
    QMessageBox::warning(this, "Destroy", clientManager->getAnswerInfos().c_str());

}


void InGame::disableAllButtons(){
    ui->buyButton->setEnabled(false);
    ui->buildButton->setEnabled(false);
    ui->upgradeButton->setEnabled(false);
    ui->sellButton->setEnabled(false);
    ui->destroyButton->setEnabled(false);
}

void InGame::on_exitButton_clicked(){
    clientManager->setCurrentWidget(ClientManagerGUI::MAINMENU);
}
