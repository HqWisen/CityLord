#ifndef CATALOGGUI_H
#define CATALOGGUI_H

#include <QDialog>
#include <QTableWidgetItem>
#include "clientmanagerGUI.h"
#include "citylordview.h"

namespace Ui {
class CatalogGui;
}

class CatalogGui : public QDialog
{
    Q_OBJECT

public:
    explicit CatalogGui(QWidget *,ClientManagerGUI*, CityLordView*, Location*);
    ~CatalogGui();
    void refresh();

private slots:

    void on_cancelButton_clicked();

    void on_buyCatButton_clicked();

private:
    Ui::CatalogGui *ui;
    ClientManagerGUI* clientManager;
    QTableWidgetItem*** tableItemArray;
    QStringList headerLabels;
    int choice;
    CityLordView* view;
    Location* lastLocation;
};

#endif // CATALOGGUI_H
