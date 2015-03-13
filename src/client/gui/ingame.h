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
    InGame(QWidget*, ClientManager*);
    ~InGame();
    void refresh() override;
    void updateMoney(int);
    void updateTime(int);
private slots:
    void on_demolishButton_clicked();
    void on_buyButton_clicked();
    void on_buildButton_clicked();
    void disableAllButtons();

    void on_exitButton_clicked();

private:
    Ui::InGame* ui;
    CityLordView* view;

};

#endif // WIDGET_H
