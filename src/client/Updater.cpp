#include "Updater.hpp"

const std::map<std::string, update_ptr> Updater::updatemap = {
    {"changeowner", update::changeowner},
    {"changeownerwithbuilding", update::changeownerwithbuilding},
    {"build", update::build},
    {"destroy", update::destroy},
    {"visitorMove", update::visitormove}

};

Updater::Updater(CityLordClient* cclient, Socket socket) : client(cclient), updateSocket(socket){
	this->start();
}

void Updater::run(){
    SocketMessage update;
    recvUpdate(update);
    while(update.getTopic() != "quit" && !update.getTopic().empty()){
        Updater::updatemap.at(update.getTopic())(client, update);
        recvUpdate(update);
    }
}

void Updater::recvUpdate(SocketMessage& update){
    update = SocketMessage::parse(updateSocket.read());
}

