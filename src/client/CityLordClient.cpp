#include "CityLordClient.hpp"

#include <stdexcept>

CityLordClient::CityLordClient(char* hostname, int port) : connectionSocket(hostname, port), updateSocket(hostname, port+1), map(nullptr), updater(nullptr){}

void CityLordClient::run(){
    SocketMessage updateMessage, quitRequest("quit");
	connectionSocket.connectHost();
    recvAnswer(updateMessage);
    if(updateMessage.getTopic() == "update"){
        updateSocket.connectHost();
    }else{
        throw std::invalid_argument("Cannot connect the user updater.");
    }
    updater = new Updater(this, updateSocket);
    LOG("Welcome in CityLord !");
	beginConnection();
	chooseCity();
	bool disconnected = false;
	while(! disconnected){
		std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
		LOG("Choose an action");
		std::cout<<"1 - Show map"<<std::endl;
		std::cout<<"2 - Select field"<<std::endl;
		std::cout<<"3 - Show catalog"<<std::endl;
		std::cout<<"4 - Show information"<<std::endl;
		//std::cout<<"5 - Show others players's information"<<std::endl;
		std::cout<<"5 - Disconnection"<<std::endl;

		int choice = makeChoice(1, 6);
		if(choice == 1){
			showMap();
		}else if(choice == 2){
			selectField();
		}
		else if(choice == 3){
			showCatalog();
		}
		else if(choice == 4){
			showInfo();
		}
		//else if(choice == 5){
			//showInfoOthersPlayers();
		//}
		else if(choice == 5){
			disconnected= true;
		}
	}
	sendRequest(quitRequest);
}

CityLordClient::~CityLordClient(){
    delete map;
    delete updater;
}

void CityLordClient::beginConnection(){
	std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
	LOG("Connect you to the server");
	std::cout<<"1 - Create an account"<<std::endl;
	std::cout<<"2 - Login"<<std::endl;
	int choice = makeChoice(1, 2);
	if(choice == 1){
		createAccount();
	}else if(choice == 2){
		login();
	}
	// TODO print username
}

void CityLordClient::login(){
	bool fail = true;
    std::string username, password;
	SocketMessage request("login"), answer;
	std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
	LOG("Enter your account nickname to log in.");
	while(fail){
        std::cout<<"Username : ";
        std::cin>>username;
        request.set("username", username);
        std::cout<<"Password : ";
        std::cin>>password;
        request.set("password", password);
        sendRequest(request);
		recvAnswer(answer);
		fail = (answer.getTopic() == "failure");
		if(fail){
			LOG(answer.get("reason"));
		}
	}
}

void CityLordClient::createAccount(){
	// TODO restriction du pseudo (nb max de char etc...)
	bool fail = true;
    std::string username, password;
	SocketMessage request("createaccount"), answer;
	std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
	LOG("To create an account enter your username.");
	while(fail){
        std::cout<<"Username : ";
        std::cin>>username;
        request.set("username", username);
        std::cout<<"Password : ";
        std::cin>>password;
        request.set("password", password);
		sendRequest(request);
		recvAnswer(answer);
		fail = (answer.getTopic() == "failure");
		if (fail){
			LOG(answer.get("reason"));
		}
	}
	LOG("Please save it to keep your account !");
}
void CityLordClient::chooseCity(){
	std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
	LOG("Choose your city");
	std::cout<<"1 - Create a city"<<std::endl;
	std::cout<<"2 - Join a city"<<std::endl;
	int choice = makeChoice(1, 2);
	if(choice == 1){
		createCity();
	}else if(choice == 2){
		joinCity();
	}
}

void CityLordClient::createCity(){
	SocketMessage request, answer;
	request.setTopic("choicemap");
	sendRequest(request);
	recvAnswer(answer);
	std::map<std::string, std::string> map = answer.getMap();
	int i = 0;
	std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
	LOG("Choose a map for the city");
	for(std::map<std::string, std::string>::iterator iterator = map.begin(); iterator != map.end(); iterator++) {
		i++;
		std::cout<<iterator->first<<" - "<<iterator->second<<std::endl;
	}
	int choice = makeChoice(1, i);
	request.setTopic("createcity");
	request.set("number", std::to_string(choice));
	sendRequest(request);
	recvAnswer(answer);
	if(answer.getTopic() == "success"){
		LOG("The server created a new city with the map "+map[std::to_string(choice)]);
	}else{
		// TODO handle creation failure
	}
	joinCity();
}

void CityLordClient::joinCity(){
	SocketMessage request, answer;
    std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
    LOG("Choose a city to play");
    bool fail = true;
    while(fail){
        int cityid = 0;
        request.setTopic("cityinfo");
        request.set("cityid", std::to_string(cityid));
        sendRequest(request);
        recvAnswer(answer);
        while(answer.getTopic() != "failure"){
            std::cout<<cityid+1<<" - "<<answer.get("name")<<" | "<<answer.get("mapname")<<" | " \
            <<answer.get("creator")<<" | "<<answer.get("nplayer")<<"/"<<answer.get("maxplayer")<<std::endl;
            cityid++;
            request.set("cityid", std::to_string(cityid));
            sendRequest(request);
            recvAnswer(answer);
        }
        int choice = makeChoice(1, cityid);
        request.setTopic("joincity");
        request.set("cityid", std::to_string(choice-1));
        sendRequest(request);
        recvAnswer(answer);
        if(answer.getTopic() == "failure"){
            LOG(answer.get("reason"));
        }else{
            fail = false;
            //map = new Map<ClientField>(answer.get("filename"));
            std::cout<<answer.get("mapstring")<<std::endl;
            std::string path = "src/resources/tmp/out.txt";
            Map<ClientField>::parseMap(path, answer.get("mapstring"));
            map = new Map<ClientField>(path);
            map->display();

        }
    }
}

void CityLordClient::showMap(){
    map->display();
}

void CityLordClient::selectField(){
	SocketMessage request;
    SocketMessage answer;
    LOG("Choose the row :");
    int crow = makeChoice(1, map->getNumberOfRows());
    LOG("Choose the column :");
    int ccol = makeChoice(1, map->getNumberOfCols());
	request.setTopic("selectfield");
    request.set("row", std::to_string(crow-1));
    request.set("col", std::to_string(ccol-1));
    sendRequest(request);
	recvAnswer(answer);
	if(answer.getTopic() == "owner"){ 
        std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
		std::cout<<"It's your field, what would you want to do ?"<<std::endl;
        /*std::cout<<"1 - Build"<<std::endl;
		//std::cout<<"2 - Sell"<<std::endl;
		std::cout<<"2 - Show information"<<std::endl;
		std::cout<<"3 - Upgrade"<<std::endl;
		std::cout<<"4 - Destroy"<<std::endl;
		std::cout<<"5 - Quit"<<std::endl;

		int choice = makeChoice(1, 6);
		if(choice == 1){
			request.setTopic("build");
			std::cout<<"1 - BAR"<<std::endl;
			std::cout<<"2 - SHOP"<<std::endl;
			int buildChoice = makeChoice(1, 2);
			if(buildChoice == 1){
				request.set("type", "bar");
			}else if(buildChoice == 2){
				request.set("type", "shop");
			}
			sendRequest(request);
			recvAnswer(answer);
			LOG(answer.getTopic() + " - " + answer.get("reason"));
		}
		else if(choice == 2){
			std::cout<<answer.get("info")<<std::endl;
		}
		else if(choice == 3){
			request.setTopic("upgrade");
			sendRequest(request);
			recvAnswer(answer);
			LOG(answer.getTopic() + " - " + answer.get("reason"));
		
		}
		else if(choice == 4){
			request.setTopic("destroy");
			sendRequest(request);
			recvAnswer(answer);
			LOG(answer.getTopic() + " - " + answer.get("reason"));
        }*/
	}
	else if(answer.getTopic() == "other"){ 
        /*std::cout<<"--------------------------------------------------------------------------------"<<std::endl;

        std::cout<<"It's another player field"<<std::endl;
		std::cout<<"1 - Show information"<<std::endl;
		std::cout<<"2 - Quit"<<std::endl;
		int choice = makeChoice(1, 2);
		if(choice == 1){
			std::cout<<answer.get("info")<<std::endl;
        }*/
	}
	else if(answer.getTopic() == "purchasable"){ 
		std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
        LOG("This field is free for sale");
		std::cout<<"1 - Show information"<<std::endl;
		std::cout<<"2 - Buy"<<std::endl;
		std::cout<<"3 - Quit"<<std::endl;
		int choice = makeChoice(1, 3);
		if(choice == 1){
			std::cout<<answer.get("info")<<std::endl;
		}else if(choice == 2){
			request.setTopic("buy");
			sendRequest(request);
			recvAnswer(answer);
			LOG(answer.getTopic() + " - " + answer.get("reason"));
		}
	}
	else{
		std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
		std::cout<<"The field selected is not selectable ! (Tree, road, ...)"<<std::endl;
    }
}

void CityLordClient::build(){ // La parcelle est déjà selectionnée
	SocketMessage request("build");
	SocketMessage answer; 
}

void CityLordClient::showInfo(){
	SocketMessage request("showinfo");
	SocketMessage answer; // les différentes informations
	sendRequest(request);
	recvAnswer(answer);
	std::string money = answer.get("money");	
	std::string nickname = answer.get("nickname");
	std::string nBuilding = answer.get("nbuilding");
	std::string nEmptyField = answer.get("nemptyfield");
	//std::string color = answer.get("color");

	std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
	std::cout<<"Your nickname : "<< nickname <<std::endl;
	std::cout<<"Your money : "<< money <<std::endl;
	std::cout<<"Number of building : "<< nBuilding <<std::endl;
	std::cout<<"Number of empty field : "<< nEmptyField <<std::endl;
	//std::cout<<"Your color : "<< color <<std::endl;
}

void CityLordClient::showCatalog(){
	SocketMessage request("showcatalog");
	SocketMessage answer; // les parcelles vendables avec leurs infos
	sendRequest(request);
	recvAnswer(answer);
	std::map<std::string, std::string> map = answer.getMap();
	std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
	for(std::map<std::string, std::string>::iterator iterator = map.begin(); iterator != map.end(); iterator++) {
		std::cout<<iterator->first<<" - "<<iterator->second<<std::endl;
	}
}

void CityLordClient::sendRequest(SocketMessage message){
	connectionSocket.write(message.toString());
}
void CityLordClient::recvAnswer(SocketMessage& answer){
	answer = SocketMessage::parse(connectionSocket.read());
}

int CityLordClient::makeChoice(int min, int max){
	int choice = 0;
	while(choice < min or choice > max){
		choice = 0;
		std::cout<<CINITEM;
		std::cin>>choice;
		std::cin.clear();
		std::cin.ignore();
	}
	return choice;
} 

Map<ClientField>* CityLordClient::getMap(){
    return map;
}

void CityLordClient::LOG(std::string info){
	time_t now = time(0);
	struct tm tstruct;
	char timestr[80];
	tstruct = *localtime(&now);
  //strftime(timestr, sizeof(timestr), "%d-%m-%Y, %X", &tstruct); // with date
  strftime(timestr, sizeof(timestr), "%X", &tstruct);
	std::cout<<"["<<CLIENTNAME<<"]";
	std::cout<<"["<<timestr<<"]";
	std::cout<<" ";
	std::cout<<info;
	std::cout<<std::endl;
}




