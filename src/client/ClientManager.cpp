#include "ClientManager.hpp"
#include <iostream>

const std::string ClientManager::CURRENCY = "€";

std::string ClientManager::strCurrency(int i){
    std::string result = std::to_string(i);
    result += CURRENCY;
    return result;
}

std::string ClientManager::strCurrency(std::string str){
    std::string result = str + CURRENCY;
    return result;
}


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
    if(map != nullptr){
        delete map;
    }
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
    return getTopicMessage() + " - " + getReason();
}

std::string ClientManager::getTopicMessage(){
    return message.getTopic();
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

std::string ClientManager::getReason(){
    return getInfo("reason");
}

void ClientManager::quit(){
    setRequest("quit");
    sendRequest();
}

void ClientManager::repaint(){

}

void ClientManager::updateMoney(int newMoney){

}


/*
void ClientManager::updateTime(int newTime){

}
*/