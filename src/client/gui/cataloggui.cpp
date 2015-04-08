#include "cataloggui.h"
#include "ui_cataloggui.h"

CatalogGui::CatalogGui(QWidget* parent, ClientManagerGUI* cm, CityLordView* cv, Location* location):
    QDialog(parent), ui(new Ui::CatalogGui), clientManager(cm), view(cv), lastLocation(location), tableItemArray(nullptr), headerLabels(), choice(-1)
{
    ui->setupUi(this);
    for (int c = 0; c < ui->tableWidget->horizontalHeader()->count(); ++c)
    {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
    //headerLabels << "Location" << "Building" << "Level" << "Owner" << "Price";
    headerLabels << "Location" << "Owner" << "Price";
    ui->tableWidget->setColumnCount(headerLabels.size());
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
    setWindowTitle("Catalog");

}

CatalogGui::~CatalogGui()
{
    delete ui;
}

void CatalogGui::on_buyCatButton_clicked()
{

}

void CatalogGui::on_cancelButton_clicked()
{
    close();
}

void CatalogGui::refresh()
{
    if(tableItemArray != nullptr){
        delete[] tableItemArray;
    }
    clientManager->setRequest("showcatalog");
    clientManager->sendRequestAndRecv();
    std::map<std::string, std::string> map = clientManager->getMessage().getMap();
    ui->tableWidget->setRowCount(map.size());
    tableItemArray = new QTableWidgetItem**[map.size()];

    int i = 0;
    for(std::map<std::string, std::string>::iterator iterator = map.begin(); iterator != map.end(); iterator++) {
        std::string location = iterator->first;
        location=location.substr(1, location.size()-2);

        std::string priceAndOwner = iterator->second;
        priceAndOwner=priceAndOwner.substr(8, priceAndOwner.size()); // delete "Price : "
        int j = 0;
        while((priceAndOwner[j]!='-') && (j<priceAndOwner.size())){j++;}
        std::string price=priceAndOwner.substr(1, j-2);
        std::string owner=priceAndOwner.substr(j+10, priceAndOwner.size());

        tableItemArray[i] = new  QTableWidgetItem*[headerLabels.size()];
        tableItemArray[i][0] = new QTableWidgetItem(QString::fromStdString(location));
        tableItemArray[i][0]->setFlags(tableItemArray[i][0]->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(i, 0, tableItemArray[i][0]);
        tableItemArray[i][1] = new QTableWidgetItem(QString::fromStdString(owner));
        tableItemArray[i][1]->setFlags(tableItemArray[i][1]->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(i, 1, tableItemArray[i][1]);
        tableItemArray[i][2] = new QTableWidgetItem(QString::fromStdString(price));
        tableItemArray[i][2]->setFlags(tableItemArray[i][2]->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(i, 2, tableItemArray[i][2]);
        i++;
    }
}
/*
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
*/
