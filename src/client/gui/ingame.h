#ifndef INGAME_H
#define INGAME_H

#include <QWidget>
#include <QMessageBox>

#include <sstream>
#include <string>
#include <iostream>
#include "citylordview.h"
#include "defaultwidget.h"


namespace Ui {
class InGame;
}

class InGame: public DefaultWidget{
    Q_OBJECT

public:
    InGame(QWidget*, ClientManagerGUI*);
    ~InGame();
    void refresh() override;
    void updateMoney(int);
    void updateTime(int);
public slots:
    void repaintView();
    void activeButton(std::string, Location);
private slots:
    void on_buyButton_clicked();
    void on_buildButton_clicked();
    void on_upgradeButton_clicked();
    void on_destroyButton_clicked();
    void disableAllButtons();
    void updateButtons(bool,bool,bool,bool,bool);

    void on_exitButton_clicked();

private:
    Ui::InGame* ui;
    CityLordView* view;
    Location lastLocation;

};

#endif // WIDGET_H
