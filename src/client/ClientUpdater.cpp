#include "ClientUpdater.hpp"

const std::map<std::string, update_ptr> ClientUpdater::updatemap = {
    {"changeowner", UpdateMethods::changeowner},
    //{"changeownerwithbuilding", UpdateMethods::changeownerwithbuilding},
    {"build", UpdateMethods::build},
    {"destroy", UpdateMethods::destroy},
    {"visitorMove", UpdateMethods::visitormove}

};


ClientUpdater::ClientUpdater(ClientManager* cm, Socket socket) : clientManager(cm), updateSocket(socket){
    this->start();
}

void ClientUpdater::run(){

    SocketMessage update, answer("success");
    recvUpdate(update);
    while(update.getTopic() != "quit" && !update.getTopic().empty()){       
        ClientUpdater::updatemap.at(update.getTopic())(clientManager, update);
        sendAnswer(answer); // finish signal
        recvUpdate(update);
    }
}

void ClientUpdater::recvUpdate(SocketMessage& update){
    update = SocketMessage::parse(updateSocket.read());
}
void ClientUpdater::sendAnswer(SocketMessage answer){
    updateSocket.write(answer.toString());
}
