#ifndef SELL_H
#define SELL_H

#include <QWidget>
#include <QDialog>
#include <QTableWidgetItem>
#include <QMessageBox>
#include "clientmanagerGUI.h"

namespace Ui {
class Sell;
}

class Sell : public QDialog
{
    Q_OBJECT

public:
    explicit Sell(QWidget*, ClientManagerGUI*);
    ~Sell();
    QPushButton* getCancelButton();
private slots:
    void on_putOnDialogButton_clicked();

    void on_takeOffDialogButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::Sell *ui;
    ClientManagerGUI* clientManager;
    QTableWidgetItem*** tableItemArray;
    QStringList headerLabels;
    int choice;
};

#endif // SELL_H
