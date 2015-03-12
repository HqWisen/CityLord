#ifndef JOINGAME_H
#define JOINGAME_H

#include <QWidget>
#include <QTableWidgetItem>
#include "defaultwidget.h"

namespace Ui {
class JoinGame;
}

class JoinGame : public DefaultWidget{
    Q_OBJECT

public:
    JoinGame(QWidget*, ClientManager*);
    ~JoinGame();
    void refresh() override;

private slots:
    void on_joinButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::JoinGame *ui;
    QTableWidgetItem*** tableItemArray;
    QStringList headerLabels;
    int choice;
};


#endif // JOINGAME_H
