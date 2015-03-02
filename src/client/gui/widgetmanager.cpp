#include "widgetmanager.h"

void WidgetManager::setMainMenuPage(QWidget* mainmenu){
    menuPage = mainmenu;
}


void WidgetManager::setLoginPage(QWidget* login){
    loginPage = login;
}

void WidgetManager::setInPlayPage(QWidget* inplay){
    inplayPage = inplay;
}

QWidget* WidgetManager::getMainMenuPage(){
    return menuPage;
}

QWidget* WidgetManager::getLoginPage(){
    return loginPage;
}

QWidget* WidgetManager::getInPlayPage(){
    return inplayPage;
}
