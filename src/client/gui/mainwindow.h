#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ingame.h"
#include "login.h"
#include "mainmenu.h"
#include "createaccount.h"
#include "creategame.h"
#include "joingame.h"
#include "clientmanager.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit MainWindow(char*, int);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWidget* centralWidget;
    ClientManager* clientManager;
};

#endif // MAINWINDOW_H
