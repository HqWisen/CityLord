#ifndef INGAME_H
#define INGAME_H

#include <QWidget>

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
private slots:
    void on_demolishButton_clicked();
    void on_buyButton_clicked();
    void on_buildButton_clicked();
    void disableAllButtons();

private:
    Ui::InGame* ui;
    CityLordView* view;

};

#endif // WIDGET_H
