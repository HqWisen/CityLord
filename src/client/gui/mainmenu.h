#ifndef MAINMENU_H
#define MAINMENU_H

#include "defaultwidget.h"
#include <QMessageBox>
#include <QTextBrowser>
#include <QFile>

namespace Ui {
class MainMenu;
}

class MainMenu : public DefaultWidget{
    Q_OBJECT
public:
    MainMenu(QWidget *parent, ClientManagerGUI*);
    ~MainMenu();
    void refresh() override;
private slots:
    void on_joinButton_clicked();
    void on_createButton_clicked();
    void on_disconnectButton_clicked();
    void on_quitButton_clicked();
    void on_helpButton_clicked();

private:
    Ui::MainMenu *ui;
};

#endif // MAINMENU_H
