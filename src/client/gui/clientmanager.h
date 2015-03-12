#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QStackedWidget>
#include <QVBoxLayout>
#include <map>
#include <string>
#include "../../common/socket/ConnectionSocket.hpp"
#include "../../common/socket/SocketMessage.hpp"

typedef int key_type;

class DefaultWidget;

class ClientManager{
public:
    static const key_type LOGIN, CREATEACCOUNT, MAINMENU, INGAME, CREATEGAME, JOINGAME;
public:
    ClientManager(char*, int);
    ~ClientManager();
    void set(key_type, DefaultWidget*);
    DefaultWidget* get(key_type);
    bool alreadySet(key_type);
    void setCurrentWidget(key_type);
    QVBoxLayout* getLayout();
    void setRequest(std::string);
    void addInfo(std::string, std::string);
    std::string getInfo(std::string);
    void cleanMessage();
    void sendRequestAndRecv();
    void sendRequest();
    void recvAnswer();
    bool requestFailed();
    std::string getFailureReason();
    void quit();

private:
    QStackedWidget* stackedWidget;
    QVBoxLayout* layout;
    std::map<key_type, DefaultWidget*> pages;
    ConnectionSocket socket;
    ConnectionSocket updateSocket;
    SocketMessage message;

};

#endif // CLIENTMANAGER_H
