#include "sell.h"
#include "ui_sell.h"

sell::sell(QWidget *parent, ClientManagerGUI *cm, Location* location) :
    QDialog(parent),
    ui(new Ui::sell),
    clientManager(cm),
    lastLocation(location)
{
    ui->setupUi(this);
    ui->priceSpinBox->setValue(10000);
    ui->priceSpinBox->setRange(10000,1000000); //min 10 000 -> max 1 000 000
    setWindowTitle("Sell");
}

sell::~sell()
{
    delete ui;
}

void sell::on_putOnDialogButton_clicked()
{
    clientManager->setRequest("offer");
    clientManager->addInfo("row", std::to_string(lastLocation->getRow()));
    clientManager->addInfo("col", std::to_string(lastLocation->getCol()));
    int offeredPrice = getPrice();
    clientManager->addInfo("offerprice", std::to_string(offeredPrice));
    clientManager->sendRequestAndRecv();
    clientManager->addInfo("showmessagebox", "true");
    close();
}

void sell::on_takeOffDialogButton_clicked()
{
    cout<<"row--"<< std::to_string(lastLocation->getRow())<<endl;
    cout<<"col--"<< std::to_string(lastLocation->getCol())<<endl;
    clientManager->setRequest("offercancel");
    clientManager->addInfo("row", std::to_string(lastLocation->getRow()));
    clientManager->addInfo("col", std::to_string(lastLocation->getCol()));
    clientManager->sendRequestAndRecv();
    clientManager->addInfo("showmessagebox", "true");
    close();
}


void sell::on_hypothecateButton_clicked()
{
    clientManager->setRequest("hypotheque");
    clientManager->addInfo("row", std::to_string(lastLocation->getRow()));
    clientManager->addInfo("col", std::to_string(lastLocation->getCol()));
    clientManager->sendRequestAndRecv();
    clientManager->addInfo("showmessagebox", "true");
    close();
}

void sell::on_buyBackButton_clicked()
{
    clientManager->setRequest("buyback");
    clientManager->addInfo("row", std::to_string(lastLocation->getRow()));
    clientManager->addInfo("col", std::to_string(lastLocation->getCol()));
    clientManager->sendRequestAndRecv();
    clientManager->addInfo("showmessagebox", "true");
    close();
}


void sell::on_cancelButton_clicked()
{
    close();
}

QPushButton* sell::getCancelButton(){
    return ui->cancelButton;
}

int sell::getPrice(){
    return ui->priceSpinBox->value();
}
