#include "sell.h"
#include "ui_sell.h"

sell::sell(QWidget *parent, ClientManagerGUI *cm) :
    QDialog(parent),
    ui(new Ui::sell),
    clientManager(cm)
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
    /* Request and location are set in ingame buildButton method */
    int offeredPrice = getPrice();
    clientManager->addInfo("offerprice", std::to_string(offeredPrice));
    clientManager->sendRequestAndRecv();
    clientManager->addInfo("showmessagebox", "true");
    close();
}

void sell::on_takeOffDialogButton_clicked()
{

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
