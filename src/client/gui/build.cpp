#include "build.h"
#include "ui_build.h"

build::build(QWidget* parent, ClientManagerGUI* cm) :
    QDialog(parent), ui(new Ui::build), clientManager(cm), tableItemArray(nullptr), headerLabels(), choice(-1){
    ui->setupUi(this);
    for (int c = 0; c < ui->tableWidget->horizontalHeader()->count(); ++c)
    {
        /*ui->tableWidget->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);*/
    }
    headerLabels << "Building type";
    ui->tableWidget->setColumnCount(headerLabels.size());
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    refresh();
}

build::~build(){
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

QPushButton* build::getCancelButton(){
    return ui->cancelButton;
}

void build::on_buildDialogButton_clicked(){
    QItemSelectionModel* selectionModel = ui->tableWidget->selectionModel();
    QModelIndexList selected = selectionModel->selectedRows();
    if(selected.count() == 0){
        ui->errorLabel->setText("Please select a type.");
    }else{
        for(int i= 0; i< selected.count();i++){
            QModelIndex index = selected.at(i);
            choice = index.row();
        }
        /* Request and location are set in ingame buildButton method */
        std::cout<<"TOPIC = "<<clientManager->getTopicMessage()<<std::endl;
        clientManager->addInfo("typeindex", std::to_string(choice));
        clientManager->sendRequestAndRecv();
        QMessageBox::warning(this, "Build", clientManager->getAnswerInfos().c_str());
        close();
    }

}

void build::on_cancelButton_clicked(){
    close();
}


