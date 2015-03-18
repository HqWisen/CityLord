#include "request.hpp"

pthread_mutex_t RequestSystem::requestmutex(PTHREAD_MUTEX_INITIALIZER);

SocketMessage RequestSystem::login(CityLordServer* server, UserManager* userManager, SocketMessage message){
    pthread_mutex_lock(&requestmutex);
    SocketMessage answer;
    if(server->accountExist(message.get("username"))){
        if(server->matchPassword(message.get("username"), message.get("password"))){
            server->LOG("Client with IP " + userManager->getIP() + " log in with username " + message.get("username") + ".");
            userManager->setUser(server->getUser(message.get("username")));
            answer.setTopic("success");
        }else{
            answer.setTopic("failure");
            answer.set("reason", "LOGIN FAILURE - The password doesn't match the nickname.");
        }
    }else{
        answer.setTopic("failure");
        answer.set("reason", "LOGIN FAILURE - this username doesn't exist.");

    }
    pthread_mutex_unlock(&requestmutex);
    return answer;
}

SocketMessage RequestSystem::createaccount(CityLordServer* server, UserManager* userManager, SocketMessage message){
    pthread_mutex_lock(&requestmutex);
    SocketMessage answer;
    if(!server->accountExist(message.get("username"))){
        User* user = server->createAccount(message.get("username"), message.get("password"));
        userManager->setUser(user);
        server->LOG("Client with IP " + userManager->getIP() + " has created an account with username " + message.get("username") + ".");
        answer.setTopic("success");
    }else{
        answer.setTopic("failure");
        answer.set("reason", "CREATION FAILURE - This username is already used.");
    }
    pthread_mutex_unlock(&requestmutex);
    return answer;
}

SocketMessage RequestSystem::choicemap(CityLordServer* server, UserManager* userManager, SocketMessage message){
    pthread_mutex_lock(&requestmutex);
    SocketMessage answer;
    int i = 0;
    for (std::vector<std::string>::const_iterator it = CityLordServer::getMapNameVector().begin(); it != CityLordServer::getMapNameVector().end(); it++){
        answer.set(std::to_string(i+1), *it);
        i++;
    }
    pthread_mutex_unlock(&requestmutex);
    return answer;
}

SocketMessage RequestSystem::createcity(CityLordServer* server, UserManager* userManager, SocketMessage message){
    pthread_mutex_lock(&requestmutex);
    SocketMessage answer;
    answer.setTopic("success");
    int numberOfMap = std::stoi(message.get("number")) - 1;
    CityManager* cityManager = server->createCity(numberOfMap, userManager->getUser());
    server->LOG("User "+ userManager->getUserName() + " created a city with map " + cityManager->getMapName() + ", city number is " + std::to_string(cityManager->getID()));
    // TODO send failure if creation failed*/
    answer.set("cityname", cityManager->getName());
    pthread_mutex_unlock(&requestmutex);
    return answer;
}

SocketMessage RequestSystem::numberofcity(CityLordServer* server, UserManager* userManager, SocketMessage message){
    pthread_mutex_lock(&requestmutex);
    SocketMessage answer;
    string numberOfCity = std::to_string(server->getNumberOfCity());
    answer.set("numberofcity", numberOfCity);
    pthread_mutex_unlock(&requestmutex);
    return answer;
}

SocketMessage RequestSystem::cityinfo(CityLordServer* server, UserManager* userManager, SocketMessage message){
    pthread_mutex_lock(&requestmutex);
    SocketMessage answer;
    int cityid = std::stoi(message.get("cityid"));
    if(cityid < server->getNumberOfCity()){
        CityManager* cityManager = server->getCity(cityid);
        answer.set("name", cityManager->getName());
        answer.set("mapname", cityManager->getMapName());
        answer.set("creator", cityManager->getCreator()->getUserName());
        answer.set("nplayer", std::to_string(cityManager->getNPlayer()));
        answer.set("maxplayer", std::to_string(cityManager->getMaxPlayer()));
    }else{
        answer.setTopic("failure");
        answer.set("reason", "The city with ID " + message.get("id") + " doesn't exist.");
    }
    pthread_mutex_unlock(&requestmutex);
    return answer;
}

SocketMessage RequestSystem::joincity(CityLordServer* server, UserManager* userManager, SocketMessage message){
    pthread_mutex_lock(&requestmutex);
    SocketMessage answer;
    int cityid = std::stoi(message.get("cityid"));
    CityManager* cityManager = server->getCity(cityid);
    userManager->setActiveCity(cityManager);
    if(cityManager->canJoin(userManager->getActivePlayer())){
        userManager->initActivePlayer(cityManager->getNextID());
        cityManager->addPlayer(userManager->getActivePlayer());
        server->LOG("User " + userManager->getUserName() + " joined the city "+cityManager->getName());
        answer.setTopic("success");
        answer.set("filename", cityManager->getMapFileName());
    }else{
        answer.setTopic("failure");
        answer.set("reason", "The city "+cityManager->getName()+" is full.");
    }
    pthread_mutex_unlock(&requestmutex);
    return answer;
}

SocketMessage RequestSystem::selectfield(CityLordServer* server, UserManager* userManager, SocketMessage message){
    pthread_mutex_lock(&requestmutex);
    SocketMessage answer;
    Map<Field>* map = userManager->getActiveCity()->getMap();
    int row = std::stoi(message.get("row"));
    int col = std::stoi(message.get("col"));
    Field* field;
    if((field = dynamic_cast<Field*>(map->getCase(Location(row, col))))){
        answer = field->infoHasSocketMessage();
        if(field->getOwner() == userManager->getActivePlayer()){
            answer.setTopic("owner");
        }else if(field->getOwner() == nullptr){
            answer.setTopic("purchasable");
        }else{
            answer.setTopic("other");
        }
        answer.set("info", field->toString()); // for terminal
    }else{
        answer.setTopic("notfield");
    }
    pthread_mutex_unlock(&requestmutex);
    return answer;
}

SocketMessage RequestSystem::showinfo(CityLordServer* server, UserManager* userManager, SocketMessage message){
    pthread_mutex_lock(&requestmutex);
    SocketMessage answer;
    Player* player = userManager->getActivePlayer();
    answer.set("money", std::to_string(player->getMoney()));
    answer.set("nickname", player->getNickName());
    answer.set("nbuilding", std::to_string(player->getNBuilding()));
    answer.set("nemptyfield", std::to_string(player->getNEmptyField()));
    //answer.set("color", player->getColor());
    pthread_mutex_unlock(&requestmutex);
    return answer;
}

SocketMessage RequestSystem::showcatalog(CityLordServer* server, UserManager* userManager, SocketMessage message){
    pthread_mutex_lock(&requestmutex);
    SocketMessage answer;
    std::vector<Field*> fieldVector = userManager->getActiveCity()->getPurchasableFields();
    int i = 0;
    for (std::vector<Field*>::iterator it = fieldVector.begin(); it != fieldVector.end(); it++){
        answer.set((*it)->getLocation().toString(), (*it)->toString());
        i++;
    }
    pthread_mutex_unlock(&requestmutex);
    return answer;
}

SocketMessage RequestSystem::buy(CityLordServer* server, UserManager* userManager, SocketMessage message){
    pthread_mutex_lock(&requestmutex);
    SocketMessage answer;
    int row = std::stoi(message.get("row"));
    int col = std::stoi(message.get("col"));
    CityManager* cityManager = userManager->getActiveCity();
    Player* player = userManager->getActivePlayer();
    answer = cityManager->makePurchase(player, Location(row, col));
    pthread_mutex_unlock(&requestmutex);
    return answer;
}

SocketMessage RequestSystem::build(CityLordServer* server, UserManager* userManager, SocketMessage message){
    pthread_mutex_lock(&requestmutex);
    SocketMessage answer;
    int row = std::stoi(message.get("row"));
    int col = std::stoi(message.get("col"));
    BuildingType buildingType = BuildingType::getTypeByIndex(std::stoi(message.get("typeindex")));
    CityManager* cityManager = userManager->getActiveCity();
    Player* player = userManager->getActivePlayer();
    answer = cityManager->buildBuilding(player, Location(row, col), buildingType);
    pthread_mutex_unlock(&requestmutex);
    return answer;
}

SocketMessage RequestSystem::upgrade(CityLordServer* server, UserManager* userManager, SocketMessage message){
    pthread_mutex_lock(&requestmutex);
    SocketMessage answer;
    int row = std::stoi(message.get("row"));
    int col = std::stoi(message.get("col"));
    CityManager* cityManager = userManager->getActiveCity();
    Player* player = userManager->getActivePlayer();
    answer = cityManager->upgradeBuilding(player, Location(row, col));
    pthread_mutex_unlock(&requestmutex);
    return answer;
}

SocketMessage RequestSystem::destroy(CityLordServer* server, UserManager* userManager, SocketMessage message){
    pthread_mutex_lock(&requestmutex);
    SocketMessage answer;
    int row = std::stoi(message.get("row"));
    int col = std::stoi(message.get("col"));
    CityManager* cityManager = userManager->getActiveCity();
    Player* player = userManager->getActivePlayer();
    answer = cityManager->destroyBuilding(player, Location(row, col));
    pthread_mutex_unlock(&requestmutex);
    return answer;
}

SocketMessage RequestSystem::mapfullupdate(CityLordServer* server, UserManager* userManager, SocketMessage message){
    pthread_mutex_lock(&requestmutex);
    SocketMessage answer, update;
    Map<Field>* map = userManager->getActiveCity()->getMap();
    Field* field;
    for(int row=0;row<map->getNumberOfRows();row++){
        for(int col=0;col<map->getNumberOfCols();col++){
            if((field = dynamic_cast<Field*>(map->getCase(Location(row, col))))){
                if(field->hasOwner()){
                    update.setTopic("changeowner");
                    update.set("ownerid", std::to_string(field->getOwnerID()));
                    update.set("location", field->getLocation().toString());
                    userManager->sendUpdate(update);
                }
                if(field->hasBuilding()){
                    update.setTopic("build");
                    update.set("location", field->getLocation().toString());
                    update.set("typeindex", std::to_string(BuildingType::getIndexByType(field->getBuilding()->getType())));
                    update.set("level", std::to_string(field->getBuilding()->getLevel()));
                    userManager->sendUpdate(update);
                }
            }
        }
    }
    pthread_mutex_unlock(&requestmutex);
    return answer;
}

SocketMessage RequestSystem::leavecity(CityLordServer* server, UserManager* userManager, SocketMessage message){
    pthread_mutex_lock(&requestmutex);
    SocketMessage answer;
    userManager->leaveCity();
    pthread_mutex_unlock(&requestmutex);
    return answer;
}

SocketMessage RequestSystem::playerinfo(CityLordServer* server, UserManager* userManager, SocketMessage message){
    pthread_mutex_lock(&requestmutex);
    SocketMessage answer;
    Player* player = userManager->getActivePlayer();
    answer.set("nickname", player->getNickName());
    answer.set("playerid", std::to_string(player->getPlayerID()));
    answer.set("money", std::to_string(player->getMoney()));
    answer.set("color", Player::COLORNAME[player->getPlayerID()]);
    pthread_mutex_unlock(&requestmutex);
    return answer;
}



