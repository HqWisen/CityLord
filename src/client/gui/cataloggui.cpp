#include "cataloggui.h"
#include "ui_cataloggui.h"

CatalogGui::CatalogGui(QWidget* parent, ClientManagerGUI* cm, CityLordView* cv, Location* location):
    QDialog(parent), ui(new Ui::CatalogGui), clientManager(cm), view(cv), lastLocation(location), tableItemArray(nullptr), headerLabels(), choice(-1)
{
    ui->setupUi(this);
    for (int c = 0; c < ui->tableWidget->horizontalHeader()->count(); ++c)
    /*{
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }*/
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
    QItemSelectionModel* selectionModel = ui->tableWidget->selectionModel();
    QModelIndexList selected = selectionModel->selectedRows();
    if(selected.count() == 0){
        ui->errorlabel->setText("Please select a type.");
    }else{
        for(int i= 0; i< selected.count();i++){
            QModelIndex index = selected.at(i);
            choice = index.row();
        }
        std::string theLocation = tableItemArray[choice][0]->text().toStdString();
        std::string delimiter = ",";
        std::string row = theLocation.substr(0, theLocation.find(delimiter));
        std::string col = theLocation.substr(theLocation.find(delimiter)+1, theLocation.size());
        clientManager->setRequest("buy");
        clientManager->addInfo("row", row);
        clientManager->addInfo("col", col);
        clientManager->sendRequestAndRecv();
        openMessageBox("Buy");
        if(!clientManager->requestFailed()){
            lastLocation = new Location(std::stoi(row),std::stoi(col));
            view->selectField(*lastLocation);
        }
        refresh();
    }
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
    ui->errorlabel->setText("");
}

void CatalogGui::openMessageBox(std::string title){
    if(clientManager->requestFailed()){
        QMessageBox::critical(this, title.c_str(), clientManager->getReason().c_str());
    }else{
        QMessageBox::information(this, title.c_str(), clientManager->getReason().c_str());
    }
}
