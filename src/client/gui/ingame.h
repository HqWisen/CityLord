#ifndef INGAME_H
#define INGAME_H

#include <QWidget>
#include <QMessageBox>

#include <sstream>
#include <string>
#include <iostream>
#include "citylordview.h"
#include "defaultwidget.h"
#include "build.h"
#include "sell.h"
#include "cataloggui.h"

namespace Ui {
class InGame;
}

class InGame: public DefaultWidget{
    Q_OBJECT

public:
    InGame(QWidget*, ClientManagerGUI*);
    ~InGame();
    void refresh() override;
private:
    void openMessageBox(std::string);
    void activeButton(std::string);
public slots:
    void repaintView();
    void buildViewMap();
    void selectField(SocketMessage, Location);
    void updateMoney(int);
    void updateTime(QString);
    void createVisitor(int, QString);
    void moveVisitor(int, QString);
    void removeVisitor(int);
    void updateScene(QGraphicsPixmapItem*, QPointF);
private slots:
    void on_buyButton_clicked();
    void on_buildButton_clicked();
    void on_upgradeButton_clicked();
    void on_destroyButton_clicked();
    void on_ownerFieldButton_clicked();
    void on_allFieldButton_clicked();
    void on_defaultFieldButton_clicked();
    void on_centerButton_clicked();
    void disableAllButtons();
    void updateButtons(bool,bool,bool,bool,bool);
    void on_exitButton_clicked();
    void on_sellButton_clicked();
    void on_catalogButton_clicked();

private:
    Ui::InGame* ui;
    CityLordView* view;
    build* buildDialog;
    sell* sellDialog;
    Location lastLocation;
    CatalogGui* catalog;
};

#endif // WIDGET_H
