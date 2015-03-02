#ifndef WIDGETMANAGER_H
#define WIDGETMANAGER_H

#include <QWidget>

class Login;
class MainMenu;
class InPlay;

class WidgetManager
{

public:
    WidgetManager() = default;
    void setMainMenuPage(QWidget*);
    void setLoginPage(QWidget*);
    void setInPlayPage(QWidget*);
    QWidget* getMainMenuPage();
    QWidget* getLoginPage();
    QWidget* getInPlayPage();
private:
    QWidget* menuPage;
    QWidget* loginPage;
    QWidget* inplayPage;

};

#endif // WIDGETMANAGER_H
