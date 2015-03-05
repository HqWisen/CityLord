#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "inplay.h"
#include "login.h"
#include "mainmenu.h"
#include "createaccount.h"
#include "creategame.h"
#include "clientmanager.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWidget *centralWidget;
    ClientManager* clientManager;
};

#endif // MAINWINDOW_H
