#ifndef CLIENTMANAGERGUI_H
#define CLIENTMANAGERGUI_H

#include <QStackedWidget>
#include <QVBoxLayout>
#include <map>
#include <string>
#include "../ClientManager.hpp"
#include "signaler.h"

typedef int key_type;

class DefaultWidget;

class ClientManagerGUI : public ClientManager{

public:
    static const key_type LOGIN, CREATEACCOUNT, MAINMENU, INGAME, CREATEGAME, JOINGAME, BUILD;
    static const int SQUAREMAPSIZE;
public:
    ClientManagerGUI(char*, int);
    ~ClientManagerGUI();
    void set(key_type, DefaultWidget*);
    DefaultWidget* get(key_type);
    bool alreadySet(key_type);
    void setCurrentWidget(key_type);
    QVBoxLayout* getLayout();
    void buildMap(std::string) override;
    void repaint() override;
    Signaler* getSignaler();
private:
    QStackedWidget* stackedWidget;
    QVBoxLayout* layout;
    std::map<key_type, DefaultWidget*> pages;
    Signaler* signaler;

};

#endif // CLIENTMANAGERGUI_H
