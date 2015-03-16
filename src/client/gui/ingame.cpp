#include "ingame.h"
#include "ui_ingame.h"


InGame::InGame(QWidget* parent, ClientManagerGUI* cm) :
    DefaultWidget(parent, cm), ui(new Ui::InGame), view(new CityLordView(this, cm)), buildDialog(new build(this, cm)), lastLocation(){
    ui->setupUi(this);

    ui->exitButton->setStyleSheet("background-image: url(src/resources/img/exit40_40.png)");
    ui->exitButton->setText("");

    //ui->buildButton->setEnabled(false);
    ui->buyButton->setEnabled(false);
    ui->upgradeButton->setEnabled(false);
    ui->destroyButton->setEnabled(false);
    ui->sellButton->setEnabled(false);
    /* Signaler connect */
    QObject::connect(clientManager->getSignaler(), SIGNAL(repaintView()), this, SLOT(repaintView()));
    QObject::connect(clientManager->getSignaler(), SIGNAL(buildViewMap()), this, SLOT(buildViewMap()));
    QObject::connect(clientManager->getSignaler(), SIGNAL(activeButton(std::string, Location)), this, SLOT(activeButton(std::string, Location)));
    /* Dialog connect */
    //QObject::connect(ui->buildButton, SIGNAL(clicked()), buildDialog, SLOT(exec()));
    //QObject::connect(buildDialog->getCancelButton(), SIGNAL(clicked()), buildDialog, SLOT(close()));
}

void InGame::repaintView(){
    view->repaintView();
}

void InGame::buildViewMap(){
    view->buildViewMap();
}

void InGame::moveEvent(QMoveEvent* event){
    /*const QPoint global = this->mapToGlobal(rect().center());
    buildDialog->move(global.x() - buildDialog->width() / 2, global.y() - buildDialog->height() / 2);*/
}

void InGame::activeButton(std::string fieldinfo, Location location){
    lastLocation = location;
    if(fieldinfo == "owner"){
        //ui->buildButton->setEnabled(true);
        ui->buyButton->setEnabled(false);
        ui->upgradeButton->setEnabled(true);
        ui->destroyButton->setEnabled(true);
    }else if(fieldinfo == "purchasable"){
        //ui->buildButton->setEnabled(false);
        ui->buyButton->setEnabled(true);
        ui->upgradeButton->setEnabled(false);
        ui->destroyButton->setEnabled(false);
    }else if(fieldinfo == "other"){
        //ui->buildButton->setEnabled(false);
        ui->buyButton->setEnabled(false);
        ui->upgradeButton->setEnabled(false);
        ui->destroyButton->setEnabled(false);
    }else if(fieldinfo == "notfield"){
        //ui->buildButton->setEnabled(false);
        ui->buyButton->setEnabled(false);
        ui->upgradeButton->setEnabled(false);
        ui->destroyButton->setEnabled(false);
    }
}

InGame::~InGame(){
    delete ui;
    delete view;
    delete buildDialog;
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

void InGame::openMessageBox(std::string title){
    if(clientManager->requestFailed()){
        QMessageBox::critical(this, title.c_str(), clientManager->getReason().c_str());
    }else{
        QMessageBox::information(this, title.c_str(), clientManager->getReason().c_str());
    }
}

void InGame::on_buyButton_clicked(){
    clientManager->setRequest("buy");
    clientManager->addInfo("row", std::to_string(lastLocation.getRow()));
    clientManager->addInfo("col", std::to_string(lastLocation.getCol()));
    clientManager->sendRequestAndRecv();
    openMessageBox("Buy");
    if(!clientManager->requestFailed()){
        activeButton("owner", lastLocation);
    }
}

void InGame::on_buildButton_clicked(){
    std::cout<<"HAKIMAAAAAAAAA"<<std::endl;
    /*clientManager->setRequest("Bd");
    clientManager->addInfo("row", std::to_string(lastLocation.getRow()));
    clientManager->addInfo("col", std::to_string(lastLocation.getCol()));
    QObject::connect(ui->buildButton, SIGNAL(clicked()), buildDialog, SLOT(exec()));*/
    //std::cout<<"CLICKED"<<std::endl;
    /*ui->buildButton->clicked();
    QObject::disconnect(ui->buildButton, SIGNAL(clicked()), buildDialog, SLOT(exec()));*/
}

void InGame::on_upgradeButton_clicked(){
    clientManager->setRequest("upgrade");
    clientManager->addInfo("row", std::to_string(lastLocation.getRow()));
    clientManager->addInfo("col", std::to_string(lastLocation.getCol()));
    clientManager->sendRequestAndRecv();
    openMessageBox("Upgrade");
}

void InGame::on_destroyButton_clicked()
{
    clientManager->setRequest("destroy");
    clientManager->addInfo("row", std::to_string(lastLocation.getRow()));
    clientManager->addInfo("col", std::to_string(lastLocation.getCol()));
    clientManager->sendRequestAndRecv();
    openMessageBox("Destroy");
}

void InGame::on_exitButton_clicked(){
    clientManager->setRequest("leavecity");
    clientManager->sendRequestAndRecv();
    clientManager->setCurrentWidget(ClientManagerGUI::MAINMENU);
}

void InGame::disableAllButtons(){
    ui->buyButton->setEnabled(false);
    //ui->buildButton->setEnabled(false);
    ui->upgradeButton->setEnabled(false);
    ui->sellButton->setEnabled(false);
    ui->destroyButton->setEnabled(false);
}

void InGame::updateButtons(bool buyable, bool buildable, bool upgradable, bool destroyable, bool sell){
    ui->buyButton->setEnabled(buyable);
    //ui->buildButton->setEnabled(buildable);
    ui->upgradeButton->setEnabled(upgradable);
    ui->destroyButton->setEnabled(destroyable);
    ui->sellButton->setEnabled(sell);
}
