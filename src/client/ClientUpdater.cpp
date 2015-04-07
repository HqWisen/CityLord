#include "ClientUpdater.hpp"

const std::map<std::string, update_ptr> ClientUpdater::updatemap = {
    {"changeowner", UpdateSystem::changeowner},
    {"build", UpdateSystem::build},
    {"refresh", UpdateSystem::refresh},
    {"destroy", UpdateSystem::destroy},
    {"updatemoney", UpdateSystem::updatemoney},
    {"visitorcreate", UpdateSystem::createvisitor},
    {"visitormove", UpdateSystem::movevisitor},
    {"visitorremove", UpdateSystem::removevisitor},
	{"offer", UpdateSystem::offer},
	{"offercancel", UpdateSystem::offercancel}
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
