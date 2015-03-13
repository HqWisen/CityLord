#ifndef CLIENTMANAGER_HPP
#define CLIENTMANAGER_HPP

#include "ClientUpdater.hpp"
#include "../common/models/Map.hpp"
#include "../common/socket/ConnectionSocket.hpp"
#include "../common/socket/SocketMessage.hpp"

class ClientUpdater;

class ClientManager{
public:
    ClientManager() = default;
    ClientManager(char*, int);
    virtual ~ClientManager();
    virtual void buildMap(std::string);
    void displayMap();
    Map<ClientField>* getMap();
    void setRequest(std::string);
    void addInfo(std::string, std::string);
    std::string getInfo(std::string);
    SocketMessage getMessage();
    bool topicEquals(std::string);
    std::string getAnswerInfos();
    void cleanMessage();
    void sendRequestAndRecv();
    void sendRequest();
    void recvAnswer();
    bool requestFailed();
    std::string getFailureReason();
    void quit();
    virtual void repaint();
protected:
    Map<ClientField>* map;
    ConnectionSocket socket;
    ConnectionSocket updateSocket;
    SocketMessage message;
    ClientUpdater* updater;

};

#endif // CLIENTMANAGER_HPP
