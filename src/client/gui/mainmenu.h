#ifndef MAINMENU_H
#define MAINMENU_H

#include "defaultwidget.h"
#include <QMessageBox>

namespace Ui {
class MainMenu;
}

class MainMenu : public DefaultWidget{
    Q_OBJECT
public:
    MainMenu(QWidget *parent, ClientManager*);
    ~MainMenu();
    void refresh() override;
private slots:
    void on_createButton_clicked();
    void on_disconnectButton_clicked();
    void on_quitButton_clicked();

private:
    Ui::MainMenu *ui;
};

#endif // MAINMENU_H
