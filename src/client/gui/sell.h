#ifndef SELL_H
#define SELL_H

#include <QDialog>
#include <QMessageBox>
#include "clientmanagerGUI.h"

namespace Ui {
class sell;
}

class sell : public QDialog
{
    Q_OBJECT

public:
    explicit sell(QWidget *, ClientManagerGUI*);
    ~sell();
    QPushButton* getCancelButton();
    int getPrice();
private slots:
    void on_putOnDialogButton_clicked();

    void on_takeOffDialogButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::sell *ui;
    ClientManagerGUI* clientManager;
};

#endif // SELL1_H
