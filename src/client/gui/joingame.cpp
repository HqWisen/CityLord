#include "joingame.h"
#include "ui_joingame.h"


JoinGame::JoinGame(QWidget* parent, ClientManager* cm) :
    DefaultWidget(parent, cm), ui(new Ui::JoinGame), tableItemArray(nullptr), headerLabels(), choice(-1){
    displayDefaultBackground();
    ui->setupUi(this);
    for (int c = 0; c < ui->tableWidget->horizontalHeader()->count(); ++c)
    {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
    headerLabels << "City" << "Map" << "Creator"<<"Players";
    ui->tableWidget->setColumnCount(headerLabels.size());
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
}

JoinGame::~JoinGame()
{
    delete ui;
}


void JoinGame::refresh(){
    if(tableItemArray != nullptr){
        delete[] tableItemArray;
    }
    ui->errorLabel->setText("");
    int numberOfCity;
    clientManager->setRequest("numberofcity");
    clientManager->sendRequestAndRecv();
    numberOfCity = std::stoi(clientManager->getInfo("numberofcity"));
    ui->tableWidget->setRowCount(numberOfCity);
    tableItemArray = new QTableWidgetItem**[numberOfCity];
    for (int i=0; i<numberOfCity; i++) {
        tableItemArray[i] = new QTableWidgetItem*[headerLabels.size()];
        for (int j=0; j<headerLabels.size(); j++) {
            tableItemArray[i][j] = new QTableWidgetItem;
        }
    }
    int cityid = 0;
    clientManager->setRequest("cityinfo");
    clientManager->addInfo("cityid", std::to_string(cityid));
    clientManager->sendRequestAndRecv();
    std::string players;
    while(!clientManager->requestFailed()){
        tableItemArray[cityid][0] = new QTableWidgetItem(clientManager->getInfo("name").c_str());
        tableItemArray[cityid][1] = new QTableWidgetItem(clientManager->getInfo("mapname").c_str());
        tableItemArray[cityid][2] = new QTableWidgetItem(clientManager->getInfo("creator").c_str());
        players = clientManager->getInfo("nplayer") +"/"+clientManager->getInfo("maxplayer");
        tableItemArray[cityid][3] = new QTableWidgetItem(players.c_str());
        cityid++;
        clientManager->setRequest("cityinfo");
        clientManager->addInfo("cityid", std::to_string(cityid));
        clientManager->sendRequestAndRecv();
    }



    for(int i=0;i<numberOfCity;i++){
        for(int j=0;j<headerLabels.size();j++){
            tableItemArray[i][j]->setFlags(tableItemArray[i][j]->flags() & ~Qt::ItemIsEditable);
            ui->tableWidget->setItem(i, j, tableItemArray[i][j]);
        }
    }
}

void JoinGame::on_joinButton_clicked(){
    QItemSelectionModel* selectionModel = ui->tableWidget->selectionModel();
    QModelIndexList selected = selectionModel->selectedRows();
    if(selected.count() == 0){
        ui->errorLabel->setText("Please select a city.");
    }else{
        for(int i= 0; i< selected.count();i++){
            QModelIndex index = selected.at(i);
            choice = index.row();
        }
        clientManager->setRequest("joincity");
        clientManager->addInfo("cityid", std::to_string(choice));
        clientManager->sendRequestAndRecv();
        if(clientManager->requestFailed()){
            ui->errorLabel->setText(clientManager->getFailureReason().c_str());
        }else{
            clientManager->setCurrentWidget(ClientManager::INGAME);
            clientManager->buildMap(clientManager->getInfo("filename"));
        }
    }

}

void JoinGame::on_cancelButton_clicked(){
    clientManager->setCurrentWidget(ClientManager::MAINMENU);

}
