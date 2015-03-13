#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ingame.h"
#include "build.h"
#include "login.h"
#include "mainmenu.h"
#include "createaccount.h"
#include "creategame.h"
#include "joingame.h"
#include "clientmanagerGUI.h"
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
    ClientManagerGUI* clientManager;
};

#endif // MAINWINDOW_H
