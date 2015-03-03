#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QStackedWidget>
#include <QVBoxLayout>
#include <map>

typedef int key_type;

class DefaultWidget;

class ClientManager{
public:
    static const key_type LOGIN, CREATEACCOUNT, MAINMENU, INPLAY, CREATEGAME, JOINGAME;
public:
    ClientManager();
    ~ClientManager();
    void set(key_type, DefaultWidget*);
    DefaultWidget* get(key_type);
    bool alreadySet(key_type);
    void setCurrentWidget(key_type);
    QVBoxLayout* getLayout();

private:
    QStackedWidget* stackedWidget;
    QVBoxLayout* layout;
    std::map<key_type, DefaultWidget*> pages;


};

#endif // CLIENTMANAGER_H
