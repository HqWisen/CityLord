#ifndef CLIENTMANAGERGUI_H
#define CLIENTMANAGERGUI_H

#include <QStackedWidget>
#include <QGraphicsPixmapItem>
#include <QVBoxLayout>
#include <map>
#include <string>
#include "../ClientManager.hpp"
#include "signaler.h"

typedef int key_type;

class DefaultWidget;

class ClientManagerGUI : public ClientManager{

public:
    static const key_type LOGIN, CREATEACCOUNT, MAINMENU, INGAME, CREATEGAME, JOINGAME;
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
    void updateScene(QGraphicsPixmapItem*, QPointF);
    void updateTime() override;
    void repaint() override;
    void updateMoney(int) override;
    void createVisitor(int, Location) override;
    void moveVisitor(int, Location) override;
    void removeVisitor(int) override;
    Signaler* getSignaler();
    int getCurrentPlayerID();
    void setCurrentPlayerID(int);
    void setDifficultyMultiplier(float);
    int getDifficulty(int);
    void setAdvantageMultiplier(float);
    int getAdvantage(int);
    //////////////void updateTime(int) override;
private:
    float difficultyMult = 1.0;
    float advantageMult = 1.0;
    QStackedWidget* stackedWidget;
    QVBoxLayout* layout;
    std::map<key_type, DefaultWidget*> pages;
    Signaler* signaler;
    int currentPlayerID;

};

#endif // CLIENTMANAGERGUI_H
