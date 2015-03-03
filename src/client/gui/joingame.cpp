#include "joingame.h"
#include "ui_joingame.h"

JoinGame::JoinGame(QWidget* parent, WidgetManager* wm) :
    DefaultWidget(parent, wm), ui(new Ui::JoinGame){

    displayDefaultBackground();
    ui->setupUi(this);
    for (int c = 0; c < ui->tableWidget->horizontalHeader()->count(); ++c)
    {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
    QStringList headerLabels;
    headerLabels << "Map name";
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
    QTableWidgetItem *item0 = new QTableWidgetItem("Map1.txt");
    QTableWidgetItem *item1 = new QTableWidgetItem("Map2.txt");
    QTableWidgetItem *item0b = new QTableWidgetItem("0/8");
    QTableWidgetItem *item1b = new QTableWidgetItem("0/6");
    ui->tableWidget->setItem(0, 0, item0);
    ui->tableWidget->setItem(1, 0, item1);
    ui->tableWidget->setItem(0, 1, item0b);
    ui->tableWidget->setItem(1, 1, item1b);

}

JoinGame::~JoinGame()
{
    delete ui;
}


void JoinGame::refresh(){

}

void JoinGame::on_cancelButton_clicked(){
    widgetManager->setCurrentWidget(WidgetManager::MAINMENU);

}
