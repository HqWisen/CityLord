#include "build.h"
#include "ui_build.h"

build::build(QWidget* parent, ClientManagerGUI* cm) :
    QDialog(parent), ui(new Ui::build), clientManager(cm), tableItemArray(nullptr), headerLabels(), choice(-1){
    ui->setupUi(this);
    for (int c = 0; c < ui->tableWidget->horizontalHeader()->count(); ++c)
    {
        ui->tableWidget->horizontalHeader()->setResizeMode(
            c, QHeaderView::Stretch);
    }
    headerLabels << "Type" << "Price" << "Constr. cost" << "Up. cost" << "Destr. cost"\
                    << "Daily cost" << "Capacity" << "Open time" << "Close time" << "Stay time" << "Income";
    ui->tableWidget->setColumnCount(headerLabels.size());
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
    setWindowTitle("Build");
    refresh();
}

build::~build(){
    delete ui;
}


void build::refresh(){
    if(tableItemArray != nullptr){
        delete[] tableItemArray;
    }
    /*int constructionCost;
    int destructionCost;
    int maxCapacity;
    int dailyCost;
    int attractiveness;
    int stayTime;
    int openTime;
    int closeTime;
    int income;
    int price;
    int upgradeCost;*/

    ui->tableWidget->setRowCount(BuildingType::typesLength);
    tableItemArray = new QTableWidgetItem**[BuildingType::typesLength];
    for (int i=0; i<BuildingType::typesLength; i++) {
        tableItemArray[i] = new  QTableWidgetItem*[headerLabels.size()];
        tableItemArray[i][0] = new QTableWidgetItem(BuildingType::types[i].NAME.c_str());
        tableItemArray[i][0]->setFlags(tableItemArray[i][0]->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(i, 0, tableItemArray[i][0]);
        tableItemArray[i][1] = new QTableWidgetItem(ClientManager::strCurrency(BuildingType::types[i].PRICE).c_str());
        tableItemArray[i][1]->setFlags(tableItemArray[i][1]->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(i, 1, tableItemArray[i][1]);
        tableItemArray[i][2] = new QTableWidgetItem(ClientManager::strCurrency(BuildingType::types[i].CONSTRUCTIONCOST).c_str());
        tableItemArray[i][2]->setFlags(tableItemArray[i][2]->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(i, 2, tableItemArray[i][2]);
        tableItemArray[i][3] = new QTableWidgetItem(ClientManager::strCurrency(BuildingType::types[i].UPGRADECOST).c_str());
        tableItemArray[i][3]->setFlags(tableItemArray[i][3]->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(i, 3, tableItemArray[i][3]);
        tableItemArray[i][4] = new QTableWidgetItem(ClientManager::strCurrency(BuildingType::types[i].DESTRUCTIONCOST).c_str());
        tableItemArray[i][4]->setFlags(tableItemArray[i][4]->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(i, 4, tableItemArray[i][4]);
        tableItemArray[i][5] = new QTableWidgetItem(ClientManager::strCurrency(BuildingType::types[i].DAILYCOST).c_str());
        tableItemArray[i][5]->setFlags(tableItemArray[i][5]->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(i, 5, tableItemArray[i][5]);
        tableItemArray[i][6] = new QTableWidgetItem(std::to_string(BuildingType::types[i].CAPACITY).c_str());
        tableItemArray[i][6]->setFlags(tableItemArray[i][6]->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(i, 6, tableItemArray[i][6]);
        tableItemArray[i][7] = new QTableWidgetItem(std::to_string(BuildingType::types[i].OPENTIME).c_str());
        tableItemArray[i][7]->setFlags(tableItemArray[i][7]->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(i, 7, tableItemArray[i][7]);
        tableItemArray[i][8] = new QTableWidgetItem(std::to_string(BuildingType::types[i].CLOSETIME).c_str());
        tableItemArray[i][8]->setFlags(tableItemArray[i][8]->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(i, 8, tableItemArray[i][8]);
        tableItemArray[i][9] = new QTableWidgetItem(std::to_string(BuildingType::types[i].STAYTIME).c_str());
        tableItemArray[i][9]->setFlags(tableItemArray[i][9]->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(i, 9, tableItemArray[i][9]);
        tableItemArray[i][10] = new QTableWidgetItem(ClientManager::strCurrency(BuildingType::types[i].INCOME).c_str());
        tableItemArray[i][10]->setFlags(tableItemArray[i][10]->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(i, 10, tableItemArray[i][10]);


    }

    ui->errorLabel->setText("");
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
        clientManager->addInfo("typeindex", std::to_string(choice));
        clientManager->sendRequestAndRecv();
        clientManager->addInfo("showmessagebox", "true");
        close();
    }

}

void build::on_cancelButton_clicked(){
    close();
}


