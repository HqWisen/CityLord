#include "ingame.h"
#include "ui_ingame.h"


InGame::InGame(QWidget* parent, ClientManagerGUI* cm) :
    DefaultWidget(parent, cm), ui(new Ui::InGame), view(new CityLordView(this, cm)),
    buildDialog(new build(this, cm)), sellDialog(new sell(this, cm, &lastLocation)),
    catalog(new CatalogGui(this, cm, view, &lastLocation)), lastLocation(), sabotageMode(false){
    ui->setupUi(this);

    ui->exitButton->setStyleSheet("background-image: url(src/resources/img/exit40_40.png)");
    ui->exitButton->setText("");

    //ui->buildButton->setEnabled(false);
    ui->buyButton->setEnabled(false);
    ui->upgradeButton->setEnabled(false);
    ui->destroyButton->setEnabled(false);
    ui->sellButton->setEnabled(false);
    selectField(SocketMessage("notfield"), lastLocation);
    /* Signaler connect */
    QObject::connect(clientManager->getSignaler(), SIGNAL(repaintView()), this, SLOT(repaintView()));
    QObject::connect(clientManager->getSignaler(), SIGNAL(buildViewMap()), this, SLOT(buildViewMap()));
    QObject::connect(clientManager->getSignaler(), SIGNAL(selectField(SocketMessage,Location)), this, SLOT(selectField(SocketMessage, Location)));
    QObject::connect(clientManager->getSignaler(), SIGNAL(updateMoney(int)), this, SLOT(updateMoney(int)));
    QObject::connect(clientManager->getSignaler(), SIGNAL(updateTime(QString)), this, SLOT(updateTime(QString)));
    QObject::connect(clientManager->getSignaler(), SIGNAL(createVisitor(int, QString)), this, SLOT(createVisitor(int, QString)));
    QObject::connect(clientManager->getSignaler(), SIGNAL(moveVisitor(int, QString)), this, SLOT(moveVisitor(int, QString)));
    QObject::connect(clientManager->getSignaler(), SIGNAL(removeVisitor(int)), this, SLOT(removeVisitor(int)));
    QObject::connect(clientManager->getSignaler(), SIGNAL(updateScene(QGraphicsPixmapItem*, QPointF)), this, SLOT(updateScene(QGraphicsPixmapItem*, QPointF)));

}

void InGame::repaintView(){
    view->repaintView();
}

void InGame::refresh(){
    buildDialog->refresh();
}

void InGame::updateScene(QGraphicsPixmapItem* item, QPointF point){
    view->updateScene(item, point);
}

void InGame::updateMoney(int amount){
    if(amount>0){
        ui->moneyLabel->setStyleSheet("QLabel {background:transparent; color:rgb(0, 220, 0); font:bold 26pt;}");
    }else{
        ui->moneyLabel->setStyleSheet("QLabel {background:transparent; color:red; font:bold 26pt;");
    }
    std::ostringstream moneyStr;
    moneyStr << amount << ClientManager::CURRENCY;
    ui->moneyLabel->setText(QString::fromStdString(moneyStr.str()));
}

void InGame::updateTime(QString time){
    ui->timeLabel->setText(time);
}

void InGame::createVisitor(int id, QString locstr){
    //std::cout<<"CREATE INGAME VISITOR "<<id<< " in "<<locstr.toStdString()<<std::endl;
    view->createVisitor(id, Location::parse(locstr.toStdString()));
}

void InGame::moveVisitor(int id, QString locstr){
    //std::cout<<"MOVING INGAME VISITOR "<<id<< " in "<<locstr.toStdString()<<std::endl;
    view->moveVisitor(id, Location::parse(locstr.toStdString()));
}

void InGame::removeVisitor(int id){
    //std::cout<<"DELETING INGAME VISITOR "<<id<<std::endl;
    view->removeVisitor(id);
}

void InGame::buildViewMap(){
    clientManager->setRequest("playerinfo");
    clientManager->sendRequestAndRecv();
    ui->nicknameLabel->setText(clientManager->getInfo("nickname").c_str());
    ui->idLabel->setText(clientManager->getInfo("playerid").c_str());
    ui->colorLabel->setText(clientManager->getInfo("color").c_str());
    clientManager->setCurrentPlayerID(std::stoi(clientManager->getInfo("playerid")));
    updateMoney(std::stoi(clientManager->getInfo("money")));
    view->buildViewMap();
}

void InGame::activeButton(std::string fieldstatus){
    if(fieldstatus == "owner"){
        ui->buildButton->setEnabled(true);
        ui->buyButton->setEnabled(false);
        ui->upgradeButton->setEnabled(true);
        ui->destroyButton->setEnabled(true);
        ui->sellButton->setEnabled(true);
    }else if(fieldstatus == "purchasable"){
        ui->buildButton->setEnabled(false);
        ui->buyButton->setEnabled(true);
        ui->upgradeButton->setEnabled(false);
        ui->destroyButton->setEnabled(false);
        ui->sellButton->setEnabled(false);
    }else if(fieldstatus == "other"){
        ui->buildButton->setEnabled(false);
        ui->buyButton->setEnabled(false);
        ui->upgradeButton->setEnabled(false);
        ui->destroyButton->setEnabled(false);
        ui->sellButton->setEnabled(false);
    }else if(fieldstatus == "notfield"){
        ui->buildButton->setEnabled(false);
        ui->buyButton->setEnabled(false);
        ui->upgradeButton->setEnabled(false);
        ui->destroyButton->setEnabled(false);
        ui->sellButton->setEnabled(false);
    }
}

void InGame::selectField(SocketMessage selectmessage, Location location){
    lastLocation = location;
    std::string fieldstatus = selectmessage.getTopic();
    int price;

    // Button activation
    activeButton(fieldstatus);

    // Show infos
    if(fieldstatus == "notfield"){
        ui->ownerTitle->setText("");
        ui->priceTitle->setText("");
        ui->ownerLabel->setText("");
        ui->priceLabel->setText("");
        ui->noFieldLabel->setText("No Field\nSelected");
    }else{
        std::string ownertext = selectmessage.get("ownername")+" | "\
                        +selectmessage.get("ownerid")+" | "+selectmessage.get("ownercolor");
        ui->noFieldLabel->setText("");
        ui->ownerTitle->setText("Owner:");
        ui->priceTitle->setText("Price:");
        ui->ownerLabel->setText(ownertext.c_str());
        price = clientManager->getDifficulty(stoi(selectmessage.get("fieldprice")));
        ui->priceLabel->setText(ClientManager::strCurrency(price).c_str());
    }
    if(selectmessage.get("typeindex").empty()){
        ui->typeLabel->setText("");
        ui->attractivenessTitle->setText("");
        ui->attractivenessLabel->setText("");
        ui->levelTitle->setText("");
        ui->levelLabel->setText("");
        ui->timeTitle->setText("");
        ui->openLabel->setText("");
        ui->closeLabel->setText("");
        ui->visitorTitle->setText("");
        ui->visitorLabel->setText("");
        ui->incomeTitle->setText("");
        ui->incomeLabel->setText("");
        ui->dailyCostTitle->setText("");
        ui->dailyCostLabel->setText("");
        ui->buildingPriceTitle->setText("");
        ui->buildingPriceLabel->setText("");
        ui->destructionCostTitle->setText("");
        ui->destructionCostLabel->setText("");
        ui->noBuidlingLabel->setText("No Building");
    }else{
        std::string tmp;
        ui->typeLabel->setText(BuildingType::getTypeByIndex(std::stoi(selectmessage.get("typeindex"))).NAME.c_str());
        ui->levelTitle->setText("Level");
        ui->levelLabel->setText(selectmessage.get("level").c_str());
        ui->attractivenessTitle->setText("Attract.");
        ui->attractivenessLabel->setText(selectmessage.get("attractiveness").c_str());
        ui->timeTitle->setText("Open from       to");
        ui->openLabel->setText(selectmessage.get("opentime").c_str());
        ui->closeLabel->setText(selectmessage.get("closetime").c_str());
        ui->visitorTitle->setText("Visitors:");
        tmp = selectmessage.get("visitorcounter")+"/"+selectmessage.get("capacity");
        ui->visitorLabel->setText(tmp.c_str());
        ui->incomeTitle->setText("+                   per visitor");
        price = clientManager->getAdvantage(stoi(selectmessage.get("income")));
        ui->incomeLabel->setText(ClientManager::strCurrency(price).c_str());
        ui->dailyCostTitle->setText("-                    day charges");
        price = clientManager->getDifficulty(stoi(selectmessage.get("dailycost")));
        ui->dailyCostLabel->setText(ClientManager::strCurrency(price).c_str());
        ui->buildingPriceTitle->setText("Price:");
        price = clientManager->getDifficulty(stoi(selectmessage.get("price")));
        ui->buildingPriceLabel->setText(ClientManager::strCurrency(price).c_str());
        ui->destructionCostTitle->setText("Destruction cost:");
        price = clientManager->getDifficulty(stoi(selectmessage.get("destructioncost")));
        ui->destructionCostLabel->setText(ClientManager::strCurrency(price).c_str());
        ui->noBuidlingLabel->setText("");
    }
}

InGame::~InGame(){
    delete ui;
    delete view;
    delete buildDialog;
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
        view->selectField(lastLocation);
    }
}

void InGame::on_buildButton_clicked(){;
    clientManager->setRequest("build");
    clientManager->addInfo("row", std::to_string(lastLocation.getRow()));
    clientManager->addInfo("col", std::to_string(lastLocation.getCol()));
    buildDialog->exec();
    if(clientManager->getInfo("showmessagebox") == "true"){
        openMessageBox("Build");
        view->selectField(lastLocation);
    }
}

void InGame::on_upgradeButton_clicked(){
    clientManager->setRequest("upgrade");
    clientManager->addInfo("row", std::to_string(lastLocation.getRow()));
    clientManager->addInfo("col", std::to_string(lastLocation.getCol()));
    clientManager->sendRequestAndRecv();
    openMessageBox("Upgrade");
    if(!clientManager->requestFailed()){
        view->selectField(lastLocation);
    }

}

void InGame::on_sellButton_clicked()
{
    cout<<"row"<< std::to_string(lastLocation.getRow())<<endl;
    cout<<"col"<< std::to_string(lastLocation.getCol())<<endl;
    sellDialog->exec();
    if(clientManager->getInfo("showmessagebox") == "true"){
        openMessageBox("Build");
        view->selectField(lastLocation);
    }
}



void InGame::on_destroyButton_clicked()
{
    clientManager->setRequest("destroy");
    clientManager->addInfo("row", std::to_string(lastLocation.getRow()));
    clientManager->addInfo("col", std::to_string(lastLocation.getCol()));
    clientManager->sendRequestAndRecv();
    openMessageBox("Destroy");
    if(!clientManager->requestFailed()){
        view->selectField(lastLocation);
    }
}

void InGame::on_ownerFieldButton_clicked(){
    view->showCurrentPlayerFieldColor();
}
void InGame::on_allFieldButton_clicked(){
    view->showAllFieldColor();
}

void InGame::on_defaultFieldButton_clicked(){
    view->unshowAllFieldColor();
}

void InGame::on_centerButton_clicked(){
    view->centerMap();
}

void InGame::on_exitButton_clicked(){
    clientManager->setRequest("leavecity");
    clientManager->sendRequestAndRecv();
    clientManager->setCurrentWidget(ClientManagerGUI::MAINMENU);
    clientManager->setCurrentPlayerID(-1);
    clientManager->destroyTimer();
}

void InGame::disableAllButtons(){
    ui->buyButton->setEnabled(false);
    ui->buildButton->setEnabled(false);
    ui->upgradeButton->setEnabled(false);
    ui->sellButton->setEnabled(false);
    ui->destroyButton->setEnabled(false);
}

void InGame::updateButtons(bool buyable, bool buildable, bool upgradable, bool destroyable, bool sell){
    ui->buyButton->setEnabled(buyable);
    ui->buildButton->setEnabled(buildable);
    ui->upgradeButton->setEnabled(upgradable);
    ui->destroyButton->setEnabled(destroyable);
    ui->sellButton->setEnabled(sell);
}

void InGame::on_catalogButton_clicked()
{
    catalog->refresh();
    catalog->exec();
}

void InGame::on_sabotageButton_clicked()
{
    if(isSabotageActive()){
        sabotageMode = false;
        ui->sabotageButton->setStyleSheet("background-color: blue");
    }
    else{
        sabotageMode = true;
        ui->sabotageButton->setStyleSheet("background-color: red");
    }
}

bool InGame::isSabotageActive(){return sabotageMode;}
