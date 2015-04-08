#include "cataloggui.h"
#include "ui_cataloggui.h"

CatalogGui::CatalogGui(QWidget* parent, ClientManagerGUI* cm):
    QDialog(parent), ui(new Ui::CatalogGui), clientManager(cm), tableItemArray(nullptr), headerLabels(), choice(-1)
{
    ui->setupUi(this);
    for (int c = 0; c < ui->tableWidget->horizontalHeader()->count(); ++c)
    {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
    headerLabels << "Location" << "Building" << "Level" << "Owner" << "Price";
    ui->tableWidget->setColumnCount(headerLabels.size());
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
    setWindowTitle("Catalog");
    refresh();

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
    /*
    clientManager->setRequest("showcatalog");
    clientManager->sendRequestAndRecv();
    std::map<std::string, std::string> map = clientManager->getMessage().getMap();
    for(std::map<std::string, std::string>::iterator iterator = map.begin(); iterator != map.end(); iterator++) {
        std::cout<<iterator->first<<" - "<<iterator->second<<std::endl;
    }
    */
}
