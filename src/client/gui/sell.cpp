#include "sell.h"
#include "ui_sell.h"

sell::sell(QWidget *parent, ClientManagerGUI *cm) :
    QDialog(parent),
    ui(new Ui::sell),
    clientManager(cm)
{
    cout<<"heeeeeeeeeeeere"<<endl;
    ui->setupUi(this);
    //ui->priceSpinBox->setValue(10000);
    //ui->priceSpinBox->setRange(10000,1000000); //min 10 000 -> max 1 000 000
    //setWindowTitle("Sell");
}

sell::~sell()
{
    delete ui;
}

void sell::on_putOnDialogButton_clicked()
{
    cout<<ui->priceSpinBox->value()<<endl;
    close();
}

void sell::on_takeOffDialogButton_clicked()
{
    close();
}

void sell::on_cancelButton_clicked()
{

}

QPushButton* sell::getCancelButton(){
    return ui->cancelButton;
}
