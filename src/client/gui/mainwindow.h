#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "inplay.h"
#include "login.h"
#include "mainmenu.h"
#include "widgetmanager.h"
#include <QMainWindow>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QComboBox>

#include <iostream>

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
    WidgetManager* widgetManager;
    QStackedWidget* stackedWidget;
};

#endif // MAINWINDOW_H
