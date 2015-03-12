#include "ingame.h"
#include "ui_ingame.h"


InGame::InGame(QWidget* parent, ClientManager* cm) :
    DefaultWidget(parent, cm), ui(new Ui::InGame), view(new CityLordView(this)){

    int ROWS, COLS;
    ROWS = 50;
    COLS = 50;

    ui->setupUi(this);
    for(int row=0;row<ROWS;row++){
        for(int col=0;col<COLS;col++){
            view->addBaseOn(row, col);
        }
    }
    view->addBar();
}

InGame::~InGame(){
    delete ui;
    delete view;
}

void InGame::refresh(){

}

void InGame::updateMoney(int amount){
    if(amount>0){ui->moneyLabel->setStyleSheet("QLabel { color:rgb(0, 220, 0); }");}
    else{ui->moneyLabel->setStyleSheet("QLabel { color : red; }");};\
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

void InGame::on_demolishButton_clicked()
{
    this->updateTime(945);
}

void InGame::on_buyButton_clicked()
{
    this->updateMoney(15684);
    ui->buyButton->setEnabled(false);
}

void InGame::on_buildButton_clicked()
{
    this->updateMoney(-3682);
    ui->buyButton->setEnabled(true);
}

void InGame::disableAllButtons(){
    ui->buyButton->setEnabled(false);
    ui->buildButton->setEnabled(false);
    ui->upgradeButton->setEnabled(false);
    ui->sellButton->setEnabled(false);
    ui->demolishButton->setEnabled(false);
}
