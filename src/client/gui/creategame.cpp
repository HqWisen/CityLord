#include "creategame.h"
#include "ui_creategame.h"

CreateGame::CreateGame(QWidget* parent, ClientManager* cm) :
    DefaultWidget(parent, cm), ui(new Ui::CreateGame){

    displayDefaultBackground();
    ui->setupUi(this);
    /*for (int c = 0; c < ui->tableWidget->horizontalHeader()->count(); ++c)
    {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
    QStringList headerLabels;
    headerLabels << "Map name" << "Players";
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
    QTableWidgetItem *item0 = new QTableWidgetItem("Map1.txt");
    QTableWidgetItem *item1 = new QTableWidgetItem("Map2.txt");
    QTableWidgetItem *item0b = new QTableWidgetItem("-/8");
    QTableWidgetItem *item1b = new QTableWidgetItem("-/6");

    //items not Editable
    item0->setFlags(item0->flags() & ~Qt::ItemIsEditable);
    item1->setFlags(item1->flags() & ~Qt::ItemIsEditable);
    item0b->setFlags(item0b->flags() & ~Qt::ItemIsEditable);
    item1b->setFlags(item1b->flags() & ~Qt::ItemIsEditable);

    ui->tableWidget->setItem(0, 0, item0);
    ui->tableWidget->setItem(1, 0, item1);

    ui->tableWidget->setItem(0, 1, item0b);
    ui->tableWidget->setItem(1, 1, item1b);
    ui->tableWidget->item(0,1)->setTextAlignment(Qt::AlignRight);
    ui->tableWidget->item(1,1)->setTextAlignment(Qt::AlignRight);*/


}

CreateGame::~CreateGame(){
    delete ui;
}

void CreateGame::refresh(){

}

void CreateGame::on_cancelButton_clicked(){
    clientManager->setCurrentWidget(ClientManager::MAINMENU);

}
