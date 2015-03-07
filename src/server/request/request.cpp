#include "request.hpp"

namespace request{
	
	SocketMessage login(CityLordServer* server, UserManager* userManager, SocketMessage message){
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
		return answer;
	}

	SocketMessage createaccount(CityLordServer* server, UserManager* userManager, SocketMessage message){
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
		return answer;		
	}

	SocketMessage choicemap(CityLordServer* server, UserManager* userManager, SocketMessage message){
		SocketMessage answer;
		int i = 0;
		for (std::vector<std::string>::const_iterator it = CityLordServer::getMapNameVector().begin(); it != CityLordServer::getMapNameVector().end(); it++){
			answer.set(std::to_string(i+1), *it);
			i++;
		}
		return answer;		
	}

	SocketMessage createcity(CityLordServer* server, UserManager* userManager, SocketMessage message){
		SocketMessage answer;
		answer.setTopic("success");
		int numberOfMap = std::stoi(message.get("number")) - 1;
        CityManager* cityManager = server->createCity(numberOfMap, userManager->getUser());
		server->LOG("User "+ userManager->getUserName() + " created a city with map " + cityManager->getMapName() + ", city number is " + std::to_string(cityManager->getID()));
		// TODO send failure if creation failed*/
		return answer;		
	}
	
    SocketMessage cityinfo(CityLordServer* server, UserManager* userManager, SocketMessage message){
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
		return answer;		
	}

	SocketMessage joincity(CityLordServer* server, UserManager* userManager, SocketMessage message){
		SocketMessage answer;
        int cityid = std::stoi(message.get("cityid"));
        CityManager* cityManager = server->getCity(cityid);
        userManager->setActiveCity(cityManager);
        if(cityManager->canJoin(userManager->getActivePlayer())){
            userManager->initActivePlayer(cityManager->getNextID());
            cityManager->addPlayer(userManager->getActivePlayer());
            server->LOG("User " + userManager->getUserName() + " joined the city "+cityManager->getName());
            answer.setTopic("success");
        }else{
            answer.setTopic("failure");
            answer.set("reason", "The city "+cityManager->getName()+" is full.");
        }
		return answer;
	}

	SocketMessage showmap(CityLordServer* server, UserManager* userManager, SocketMessage message){
		SocketMessage answer;

        CityManager* cityManager = userManager->getActiveCity();
        cityManager->getMap()->display();
        return answer;
	}

	SocketMessage mapsize(CityLordServer* server, UserManager* userManager, SocketMessage message){
		SocketMessage answer;
		Map* map = userManager->getActiveCity()->getMap();
        answer.set("x", std::to_string(map->getNumberOfCols()));
        answer.set("y", std::to_string(map->getNumberOfRows()));
		return answer;
	}

	SocketMessage selectfield(CityLordServer* server, UserManager* userManager, SocketMessage message){
		SocketMessage answer;
		Map* map = userManager->getActiveCity()->getMap();
		int x = std::stoi(message.get("x"));
		int y = std::stoi(message.get("y"));
        Field* field;
        if((field = dynamic_cast<Field*>(map->getCase(Location(x, y))))){
            if(field->getOwner() == userManager->getActivePlayer()){
				answer.setTopic("owner");
			}else if(field->getOwner() == nullptr){
				answer.setTopic("purchasable");
			}else{
				answer.setTopic("other");
			}
			answer.set("info", field->toString());
		}else{
			answer.setTopic("notfield");
		}
		return answer;
	}

	SocketMessage showinfo(CityLordServer* server, UserManager* userManager, SocketMessage message){
		SocketMessage answer;
		Player* player = userManager->getActivePlayer();
		answer.set("money", std::to_string(player->getMoney()));	
		answer.set("nickname", player->getNickName());	
		answer.set("nbuilding", std::to_string(player->getNBuilding()));	
		answer.set("nemptyfield", std::to_string(player->getNEmptyField()));
		//answer.set("color", player->getColor());	
		return answer;
	}

	SocketMessage showcatalog(CityLordServer* server, UserManager* userManager, SocketMessage message){
		SocketMessage answer;
		std::vector<Field*> fieldVector = userManager->getActiveCity()->getPurchasableFields();
		int i = 0;
		for (std::vector<Field*>::iterator it = fieldVector.begin(); it != fieldVector.end(); it++){
            answer.set((*it)->getLocation().toString(), (*it)->toString());
			i++;
		}
		return answer;
	}

	SocketMessage buy(CityLordServer* server, UserManager* userManager, SocketMessage message){
		SocketMessage answer;
		int x = std::stoi(message.get("x"));
		int y = std::stoi(message.get("y"));
		CityManager* cityManager = userManager->getActiveCity();
		Player* player = userManager->getActivePlayer();
		answer = cityManager->makePurchase(player, Location(x, y));
		return answer;
	}
	
	SocketMessage build(CityLordServer* server, UserManager* userManager, SocketMessage message){
		SocketMessage answer;
		int x = std::stoi(message.get("x"));
		int y = std::stoi(message.get("y"));
		std::string type = message.get("type");
		BuildingType buildingType;
		if(type == "bar"){
			buildingType = BuildingType::BAR;
		}else if(type == "shop"){
			buildingType = BuildingType::SHOP;
		}
		CityManager* cityManager = userManager->getActiveCity();
		Player* player = userManager->getActivePlayer();
		answer = cityManager->buildBuilding(player, Location(x, y), buildingType);
		return answer;
	}
	
	SocketMessage upgrade(CityLordServer* server, UserManager* userManager, SocketMessage message){
		SocketMessage answer;
		int x = std::stoi(message.get("x"));
		int y = std::stoi(message.get("y"));
		CityManager* cityManager = userManager->getActiveCity();
		Player* player = userManager->getActivePlayer();
		answer = cityManager->upgradeBuilding(player, Location(x, y));
		
		return answer;
	}
	
	SocketMessage destroy(CityLordServer* server, UserManager* userManager, SocketMessage message){
		SocketMessage answer;
		int x = std::stoi(message.get("x"));
		int y = std::stoi(message.get("y"));
		CityManager* cityManager = userManager->getActiveCity();
		Player* player = userManager->getActivePlayer();
		answer = cityManager->destroyBuilding(player, Location(x, y));
		return answer;
	}

}

