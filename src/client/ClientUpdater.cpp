#include "ClientUpdater.hpp"

const std::map<std::string, update_ptr> ClientUpdater::updatemap = {
    {"changeowner", update::changeowner},
    {"changeownerwithbuilding", update::changeownerwithbuilding},
    {"build", update::build},
    {"destroy", update::destroy},
    {"visitorMove", update::visitormove}

};

ClientUpdater::ClientUpdater(CityLordClient* cclient, Socket socket) : client(cclient), updateSocket(socket){
	this->start();
}

void ClientUpdater::run(){
    SocketMessage update;
    recvUpdate(update);
    while(update.getTopic() != "quit" && !update.getTopic().empty()){
        ClientUpdater::updatemap.at(update.getTopic())(client, update);
        recvUpdate(update);
    }
}

void ClientUpdater::recvUpdate(SocketMessage& update){
    update = SocketMessage::parse(updateSocket.read());
}

