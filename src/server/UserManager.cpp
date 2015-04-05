#include "UserManager.hpp"

const std::map<std::string, request_ptr> UserManager::requestmap = {
	{"login", RequestSystem::login},
	{"createaccount", RequestSystem::createaccount},
	{"choicemap", RequestSystem::choicemap},
	{"createcity", RequestSystem::createcity},
    {"numberofcity", RequestSystem::numberofcity},
    {"cityinfo", RequestSystem::cityinfo},
	{"joincity", RequestSystem::joincity},
	{"selectfield", RequestSystem::selectfield},
	{"showinfo", RequestSystem::showinfo},
	{"showcatalog", RequestSystem::showcatalog},
	{"buy", RequestSystem::buy},
	{"build", RequestSystem::build},
	{"upgrade", RequestSystem::upgrade},
    {"destroy", RequestSystem::destroy},
    {"mapfullupdate", RequestSystem::mapfullupdate},
    {"leavecity", RequestSystem::leavecity},
    {"playerinfo", RequestSystem::playerinfo},
    {"offer", RequestSystem::offer},
    {"offercancel", RequestSystem::cancelOffer},
    {"inittimer", RequestSystem::inittimer},
    {"offercancel", RequestSystem::cancelOffer}
};

UserManager::UserManager(CityLordServer* cserver, ClientSocket socket, ServerSocket updateClientSocket) : server(cserver), clientSocket(socket), \
    updateSocket(nullptr), updatemutex(PTHREAD_MUTEX_INITIALIZER){
    SocketMessage answer;
    answer.setTopic("update");
    sendAnswer(answer);
    updateSocket = updateClientSocket.acceptClient();
    this->start();
}

void UserManager::run(){
    SocketMessage request, answer;
    recvRequest(request);
	while(request.getTopic() != "quit" and !request.getTopic().empty()){
        answer = UserManager::requestmap.at(request.getTopic())(server, this, request);
		sendAnswer(answer);
		recvRequest(request);
    }
    disconnectUser();
}

void UserManager::disconnectUser(){    
    sendQuitUpdate();
    pthread_mutex_lock(&updatemutex);
    if(user != nullptr && cityManager != nullptr &&  user->getPlayer(cityManager) != nullptr){
        user->getPlayer(cityManager)->setUserManager(nullptr);
    }
    leaveCity();
    sendAnswer(SocketMessage("close"));
    updateSocket->closeSocket();
    clientSocket.closeSocket();
    server->LOG("User '"+getUserName()+"' with IP "+clientSocket.getClientIP()+" is now disconnected.");
    pthread_mutex_unlock(&updatemutex);
}

void UserManager::setUser(User* user_){
    user = user_;
}

User* UserManager::getUser(){
    return user;
}

void UserManager::setActiveCity(CityManager* cm){
	cityManager = cm;
}

void UserManager::leaveCity(){
    if(cityManager != nullptr){
      user->getPlayer(cityManager)->setConnected(false);
      setActiveCity(nullptr);
    }
}

void UserManager::initActivePlayer(int playerid){
    user->initPlayer(cityManager, playerid);
    user->getPlayer(cityManager)->setConnected(true);
    user->getPlayer(cityManager)->setUserManager(this);
}

Player* UserManager::getActivePlayer(){
	return user->getPlayer(cityManager);
}

CityManager* UserManager::getActiveCity(){
	return cityManager;
}

std::string UserManager::getIP(){
	return clientSocket.getClientIP();
}

std::string UserManager::getUserName(){
    if(user != nullptr){
        return user->getUserName();
    }else{
        return "Unknown username";
    }
}

void UserManager::recvRequest(SocketMessage& request){
    request = SocketMessage::parse(clientSocket.read());
}

void UserManager::sendAnswer(SocketMessage answer){
    clientSocket.write(answer.toString());
}

void UserManager::sendQuitUpdate(){
    pthread_mutex_lock(&updatemutex);
    updateSocket->write(SocketMessage("quit").toString());
    pthread_mutex_unlock(&updatemutex);
}

void UserManager::sendUpdate(SocketMessage update){
    if(cityManager != nullptr){ // The user is playing
        pthread_mutex_lock(&updatemutex);
        updateSocket->write(update.toString());
        updateSocket->read(); // wait for finish signal
        pthread_mutex_unlock(&updatemutex);
    }
}



