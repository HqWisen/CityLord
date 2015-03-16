#include "build.h"
#include "ui_build.h"
#include <QMessageBox>
/*
build::build(QWidget* parent, ClientManagerGUI* cm) :
    DefaultWidget(parent, cm), ui(new Ui::build), tableItemArray(nullptr), headerLabels(), choice(-1){
    ui->setupUi(this);
    for (int c = 0; c < ui->tableWidget->horizontalHeader()->count(); ++c)
    {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
    headerLabels << "Building type";
    ui->tableWidget->setColumnCount(headerLabels.size());
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
    //setWindowOpacity(0);
}

build::~build()
{
    delete ui;
}


void build::refresh(){
    if(tableItemArray != nullptr){
        delete[] tableItemArray;
    }

    ui->tableWidget->setRowCount(BuildingType::typesLength);
    tableItemArray = new QTableWidgetItem*[BuildingType::typesLength];
    for (int i=0; i<BuildingType::typesLength; i++) {
        tableItemArray[i] = new QTableWidgetItem(BuildingType::types[i].buildingName.c_str());
        tableItemArray[i]->setFlags(tableItemArray[i]->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(i, 0, tableItemArray[i]);
    }

    ui->errorLabel->setText("");
    //clientManager->setRequest("build");
    //int buildChoice = makeChoice(1, BuildingType::typesLength);
    //clientManager->addInfo("typeindex", std::to_string(buildChoice-1));
    //clientManager->sendRequestAndRecv();
    //LOG(clientManager->getAnswerInfos());

}

void build::on_buildButton_clicked(){
    QItemSelectionModel* selectionModel = ui->tableWidget->selectionModel();
    QModelIndexList selected = selectionModel->selectedRows();
    if(selected.count() == 0){
        ui->errorLabel->setText("Please select a type.");
    }else{
        for(int i= 0; i< selected.count();i++){
            QModelIndex index = selected.at(i);
            choice = index.row();
        }
        clientManager->addInfo("typeindex", std::to_string(choice));
        clientManager->sendRequestAndRecv();
        clientManager->setCurrentWidget(ClientManagerGUI::INGAME);
        QMessageBox::warning(this, "Build", clientManager->getAnswerInfos().c_str());

    }

}

void build::on_cancelButton_clicked(){
    clientManager->setCurrentWidget(ClientManagerGUI::INGAME);

}*/



