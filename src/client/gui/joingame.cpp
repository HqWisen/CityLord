#include "joingame.h"
#include "ui_joingame.h"

JoinGame::JoinGame(QWidget* parent, ClientManager* cm) :
    DefaultWidget(parent, cm), ui(new Ui::JoinGame){

    displayDefaultBackground();
    ui->setupUi(this);
    for (int c = 0; c < ui->tableWidget->horizontalHeader()->count(); ++c)
    {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
    QStringList headerLabels;
    headerLabels << "Map name" << "Creator" << "Players";
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
    QTableWidgetItem *item0 = new QTableWidgetItem("Map1.txt");
    QTableWidgetItem *item1 = new QTableWidgetItem("Map2.txt");
    QTableWidgetItem *item0b = new QTableWidgetItem("Fish");
    QTableWidgetItem *item1b = new QTableWidgetItem("Hakim");
    QTableWidgetItem *item0c = new QTableWidgetItem("0/8");
    QTableWidgetItem *item1c = new QTableWidgetItem("0/6");

    //items not Editable
    item0->setFlags(item0->flags() & ~Qt::ItemIsEditable);
    item1->setFlags(item1->flags() & ~Qt::ItemIsEditable);
    item0b->setFlags(item0b->flags() & ~Qt::ItemIsEditable);
    item1b->setFlags(item1b->flags() & ~Qt::ItemIsEditable);
    item0c->setFlags(item0c->flags() & ~Qt::ItemIsEditable);
    item1c->setFlags(item1c->flags() & ~Qt::ItemIsEditable);

    ui->tableWidget->setItem(0, 0, item0);
    ui->tableWidget->setItem(1, 0, item1);
    ui->tableWidget->setItem(0, 1, item0b);
    ui->tableWidget->setItem(1, 1, item1b);
    ui->tableWidget->setItem(0, 2, item0c);
    ui->tableWidget->setItem(1, 2, item1c);
    ui->tableWidget->item(0,2)->setTextAlignment(Qt::AlignRight);
    ui->tableWidget->item(1,2)->setTextAlignment(Qt::AlignRight);
}

JoinGame::~JoinGame()
{
    delete ui;
}


void JoinGame::refresh(){

}

void JoinGame::on_cancelButton_clicked(){
    clientManager->setCurrentWidget(ClientManager::MAINMENU);

}
