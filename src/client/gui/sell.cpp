#include "sell.h"
#include "ui_sell.h"


Sell::Sell(QWidget *parent, ClientManagerGUI *cm):
    QDialog(parent), ui(new Ui::Sell), clientManager(cm){
    ui->setupUi(this);
    //ui->priceSpinBox->setValue(10000);
    //ui->priceSpinBox->setRange(10000,1000000); //min 10 000 -> max 1 000 000
    //setWindowTitle("Sell");
}

Sell::~Sell()
{
    delete ui;
}

void Sell::on_putOnDialogButton_clicked()
{
    cout<<ui->priceSpinBox->value()<<endl;
    close();
}

void Sell::on_takeOffDialogButton_clicked()
{

}

void Sell::on_cancelButton_clicked()
{
    close();
}


QPushButton* Sell::getCancelButton(){
    return ui->cancelButton;
}
