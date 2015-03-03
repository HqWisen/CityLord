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
    MainMenu(QWidget *parent, WidgetManager*);
    ~MainMenu();
    void refresh() override;
private slots:
private:
    Ui::MainMenu *ui;
};

#endif // MAINMENU_H
