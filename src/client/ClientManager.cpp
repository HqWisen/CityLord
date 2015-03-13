#include "ClientManager.hpp"
#include <iostream>


ClientManager::ClientManager(char* hostname, int port) :
    map(nullptr), socket(hostname, port),  updateSocket(hostname, port+1), message(), updater(nullptr){

    SocketMessage updateMessage;
    socket.connectHost();
    updateMessage = SocketMessage::parse(socket.read());
    if(updateMessage.getTopic() == "update"){
        updateSocket.connectHost();
    }else{
        throw std::invalid_argument("Cannot connect the user updater.");
    }
    updater = new ClientUpdater(this, updateSocket);
}

ClientManager::~ClientManager(){
    if(map != nullptr){
        delete map;
    }
    delete updater;
}

void ClientManager::buildMap(std::string filename){
    map = new Map<ClientField>(filename);
    setRequest("mapfullupdate");
    /*** Bloqué tant que la map n'est pas totalement construite ***/
    sendRequestAndRecv();

}

void ClientManager::displayMap(){
    map->display();
}

Map<ClientField>* ClientManager::getMap(){
    return map;
}

void ClientManager::setRequest(std::string request){
    cleanMessage();
    message.setTopic(request);
}

void ClientManager::addInfo(std::string key, std::string value){
    message.set(key, value);
}
std::string ClientManager::getInfo(std::string key){
    return message.get(key);
}

SocketMessage ClientManager::getMessage(){
    return message;
}

bool ClientManager::topicEquals(std::string other){
    return message.getTopic() == other;
}

std::string ClientManager::getAnswerInfos(){
    return message.getTopic() + " - " + message.get("reason");
}

void ClientManager::cleanMessage(){
    message = SocketMessage();
}

void ClientManager::sendRequestAndRecv(){
    sendRequest();
    recvAnswer();
}

void ClientManager::sendRequest(){
    socket.write(message.toString());
}

void ClientManager::recvAnswer(){
    message = SocketMessage::parse(socket.read());
}

bool ClientManager::requestFailed(){
    return message.getTopic() == "failure";
}

std::string ClientManager::getFailureReason(){
    return message.get("reason");
}

void ClientManager::quit(){
    setRequest("quit");
    sendRequest();
}

void ClientManager::repaint(){

}
