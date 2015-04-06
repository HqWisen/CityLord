#ifndef CLIENTMANAGER_HPP
#define CLIENTMANAGER_HPP

#include <string>

#include "ClientUpdater.hpp"
#include "../common/models/Map.hpp"
#include "../common/socket/ConnectionSocket.hpp"
#include "../common/socket/SocketMessage.hpp"
#include "../common/models/Timer.hpp"


class ClientUpdater;

class ClientManager{
public:
    static const std::string CURRENCY;
public:
    ClientManager() = default;
    ClientManager(char*, int);
    virtual ~ClientManager();
    virtual void buildMap(std::string);
    static void runUpdateTime(void*);
    virtual void updateTime();
    virtual void createVisitor(int, Location);
    std::string getStrTime();
    void destroyTimer();
    void displayMap();
    Map<ClientField>* getMap();
    void setRequest(std::string);
    void addInfo(std::string, std::string);
    std::string getInfo(std::string);
    SocketMessage getMessage();
    bool topicEquals(std::string);
    std::string getAnswerInfos();
    std::string getTopicMessage();
    void cleanMessage();
    void sendRequestAndRecv();
    void sendRequest();
    void recvAnswer();
    bool requestFailed();
    std::string getReason();
    void quit();
    virtual void repaint();
    virtual void updateMoney(int);
    static std::string strCurrency(int);
    static std::string strCurrency(std::string);
protected:
    Map<ClientField>* map;
    ConnectionSocket socket;
    ConnectionSocket updateSocket;
    SocketMessage message;
    ClientUpdater* updater;
    Timer<ClientManager>* timer;

};

#endif // CLIENTMANAGER_HPP
