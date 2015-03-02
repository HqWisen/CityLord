#ifndef MAINMENU_H
#define MAINMENU_H

#include "widgetmanager.h"
#include <QWidget>
#include <QMessageBox>

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent, WidgetManager*);
    ~MainMenu();

private slots:
    void on_join_pushButton_clicked();

    void on_create_pushButton_clicked();

    void on_disconnect_pushButton_clicked();

    void on_quit_pushButton_clicked();

private:
    Ui::MainMenu *ui;
    WidgetManager* widgetManager;
};

#endif // MAINMENU_H
