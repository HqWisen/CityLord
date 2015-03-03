#include "inplay.h"
#include "ui_inplay.h"

InPlay::InPlay(QWidget *parent, ClientManager* cm) :
    DefaultWidget(parent, cm), ui(new Ui::InPlay)
{
    ui->setupUi(this);
}

InPlay::~InPlay()
{
    delete ui;
}

void InPlay::on_build_pushButton_clicked()
{
    QMessageBox::warning(this, "Build", "Make a Build Function");
}

void InPlay::on_upgrade_pushButton_clicked()
{
    QMessageBox::warning(this, "Upgrade", "Make a Upgrade Function");

}

void InPlay::on_sell_pushButton_clicked()
{
    QMessageBox::warning(this, "Sell", "Make a Sell Function");
}

void InPlay::on_demolish_pushButton_clicked()
{
    QMessageBox::warning(this, "Demolish", "Make a Demolish Function");
}
