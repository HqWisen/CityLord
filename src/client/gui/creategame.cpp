#include "creategame.h"
#include "ui_creategame.h"

CreateGame::CreateGame(QWidget* parent, WidgetManager* wm) :
    DefaultWidget(parent, wm), ui(new Ui::CreateGame){

    displayDefaultBackground();
    ui->setupUi(this);
    for (int c = 0; c < ui->tableWidget->horizontalHeader()->count(); ++c)
    {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
    QStringList headerLabels;
    headerLabels << "Map name";
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
    QTableWidgetItem *item0 = new QTableWidgetItem("Map1.txt");
    QTableWidgetItem *item1 = new QTableWidgetItem("Map2.txt");
    ui->tableWidget->setItem(0, 0, item0);
    ui->tableWidget->setItem(1, 0, item1);

}

CreateGame::~CreateGame(){
    delete ui;
}

void CreateGame::refresh(){

}

void CreateGame::on_cancelButton_clicked(){
    widgetManager->setCurrentWidget(WidgetManager::MAINMENU);

}
