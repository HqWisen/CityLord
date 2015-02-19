#include "request.hpp"

namespace request{
	
	SocketMessage login(CityLordServer* server, UserManager* userManager, SocketMessage message){
		SocketMessage answer;
		if(server->accountExist(message.get("username"))){
			server->LOG("Client with IP " + userManager->getIP() + " log in with username " + message.get("username") + ".");
			userManager->setUser(server->getUser(message.get("username")));
			answer.setTopic("success");
		}else{
			answer.setTopic("failure");
			answer.set("reason", "Login failed : this username doesn't exist.");
			
		}
		return answer;
	}

	SocketMessage createaccount(CityLordServer* server, UserManager* userManager, SocketMessage message){
		SocketMessage answer;
		if(!server->accountExist(message.get("username"))){
			User* user = server->createAccount(message.get("username"));
			userManager->setUser(user);
			server->LOG("Client with IP " + userManager->getIP() + " has created an account with username " + message.get("username") + ".");
			answer.setTopic("success");
		}else{
			answer.setTopic("failure");
			answer.set("reason", "Creation failure : This username is already used.");
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
		int number = std::stoi(message.get("number")) - 1;
		CityManager* cityManager = server->createCity(number);
		server->LOG("User "+ userManager->getUserName() + " created a city with map " + cityManager->getMapName() + ", city number is " + std::to_string(cityManager->getNumber()));
		userManager->setActiveCity(cityManager);
		server->LOG("User " + userManager->getUserName() + " joined the city n° " + std::to_string(cityManager->getNumber()));
		answer.setTopic("success");
		answer.set("citynumber", std::to_string(cityManager->getNumber()));
		// TODO send failure if creation failed
		return answer;		
	}
	
	SocketMessage choicecity(CityLordServer* server, UserManager* userManager, SocketMessage message){
		SocketMessage answer;
		int numberOfCity = server->getNumberOfCity();
		for (int i = 0; i < numberOfCity; i++){
			answer.set(std::to_string(i+1), "City n°"+std::to_string(i+1));
		}
		return answer;		
	}

	SocketMessage joincity(CityLordServer* server, UserManager* userManager, SocketMessage message){
		SocketMessage answer;
		int number = std::stoi(message.get("number")) - 1;
		CityManager* cityManager = server->getCity(number);
		userManager->setActiveCity(cityManager);
		server->LOG("User " + userManager->getUserName() + " joined the city n° " + std::to_string(cityManager->getNumber()));
		answer.setTopic("success");
		answer.set("citynumber", std::to_string(cityManager->getNumber()));
		// TODO send failure if cannot join the city
		return answer;
	}

	SocketMessage showmap(CityLordServer* server, UserManager* userManager, SocketMessage message){
		SocketMessage answer;
		CityManager* cityManager = userManager->getActiveCity();
		//answer.set("map", cityManager->getMap().getMapString());
		answer.set("map", "NOT IMPLEMENTED");
		return answer;
	}

	SocketMessage selectfield(CityLordServer* server, UserManager* userManager, SocketMessage message){
		SocketMessage answer;
		//int x = std::stoi(message.get("x"));
		//int y = std::stoi(message.get("y"));
		return answer;
	}

	SocketMessage build1(CityLordServer* server, UserManager* userManager, SocketMessage message){
		SocketMessage answer;
		return answer;
	}

	SocketMessage build2(CityLordServer* server, UserManager* userManager, SocketMessage message){
		SocketMessage answer;
		return answer;
	}

	SocketMessage viewcatalog(CityLordServer* server, UserManager* userManager, SocketMessage message){
		SocketMessage answer;
		return answer;
	}

	SocketMessage showinfo(CityLordServer* server, UserManager* userManager, SocketMessage message){
		SocketMessage answer;
		return answer;
	}

	SocketMessage showinfoothersplayers(CityLordServer* server, UserManager* userManager, SocketMessage message){
		SocketMessage answer;
		return answer;
	}



}

