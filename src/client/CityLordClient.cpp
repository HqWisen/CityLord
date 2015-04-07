#include "CityLordClient.hpp"

#include <stdexcept>

CityLordClient::CityLordClient(char* hostname, int port) : clientManager(new ClientManager(hostname, port)){

}

void CityLordClient::runClient(){
    LOG("Welcome in CityLord !");
	beginConnection();
	chooseCity();
	bool disconnected = false;
	while(! disconnected){
        LOG("Choose an action");
		std::cout<<"1 - Show map"<<std::endl;
		std::cout<<"2 - Select field"<<std::endl;
        std::cout<<"3 - Set-up roadblock"<<std::endl;
		std::cout<<"4 - Show catalog"<<std::endl;
		std::cout<<"5 - Show information"<<std::endl;
		//std::cout<<"5 - Show others players's information"<<std::endl;
		std::cout<<"6 - Disconnect"<<std::endl;

		int choice = makeChoice(1, 6);
		if(choice == 1){
			showMap();
		}else if(choice == 2){
			selectField();
		}
        else if(choice == 3){
            setupRoadblock();
        }
		else if(choice == 4){
			showCatalog();
		}
		else if(choice == 5){
			showInfo();
		}
		//else if(choice == 5){
			//showInfoOthersPlayers();
		//}
		else if(choice == 6){
			disconnected= true;
		}
	}
    clientManager->quit();
}

CityLordClient::~CityLordClient(){
    clientManager->quit();
    delete clientManager;
}

void CityLordClient::beginConnection(){
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
    LOG("Enter your account nickname to log in.");
	while(fail){
        clientManager->setRequest("login");
        std::cout<<"Username : ";
        std::cin>>username;
        clientManager->addInfo("username", username);
        std::cout<<"Password : ";
        std::cin>>password;
        clientManager->addInfo("password", password);
        clientManager->sendRequestAndRecv();
        fail = clientManager->requestFailed();
		if(fail){
            LOG(clientManager->getReason());
		}
	}
}

void CityLordClient::createAccount(){
	// TODO restriction du pseudo (nb max de char etc...)
	bool fail = true;
    std::string username, password;
    clientManager->setRequest("createaccount");
    LOG("To create an account enter your username.");
	while(fail){
        clientManager->setRequest("createaccount");
        std::cout<<"Username : ";
        std::cin>>username;
        clientManager->addInfo("username", username);
        std::cout<<"Password : ";
        std::cin>>password;
        clientManager->addInfo("password", password);
        clientManager->sendRequestAndRecv();
        fail = clientManager->requestFailed();
        if(fail){
            LOG(clientManager->getReason());
        }
    }
	LOG("Please save it to keep your account !");
}
void CityLordClient::chooseCity(){
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
    clientManager->setRequest("choicemap");
    clientManager->sendRequestAndRecv();
    std::map<std::string, std::string> map = clientManager->getMessage().getMap();
	int i = 0;
    LOG("Choose a map for the city");
	for(std::map<std::string, std::string>::iterator iterator = map.begin(); iterator != map.end(); iterator++) {
		i++;
		std::cout<<iterator->first<<" - "<<iterator->second<<std::endl;
	}
	int choiceCity = makeChoice(1, i);
    clientManager->setRequest("choicemode");
    clientManager->sendRequestAndRecv();
    std::map<std::string, std::string> mode = clientManager->getMessage().getMap();
    i = 0;
    LOG("Choose a difficulty mode");
    for(std::map<std::string, std::string>::iterator iterator = mode.begin(); iterator != mode.end(); iterator++) {
        i++;
        std::cout<<iterator->first<<" - "<<iterator->second<<std::endl;
    }
    int choiceMode = makeChoice(1, i);
    clientManager->setRequest("createcity");
    clientManager->addInfo("mapnumber", std::to_string(choiceCity));
    clientManager->addInfo("modenumber", std::to_string(choiceMode));
    clientManager->sendRequestAndRecv();
    if(!clientManager->requestFailed()){
		LOG("The server created a new city with the map "+map[std::to_string(choiceCity)]+" in "+mode[std::to_string(choiceMode)]);
	}else{
		// TODO handle creation failure
	}
	joinCity();
}

void CityLordClient::joinCity(){
    LOG("Choose a city to play");
    bool fail = true;
    while(fail){
        int cityid = 0;
        clientManager->setRequest("cityinfo");
        clientManager->addInfo("cityid", std::to_string(cityid));
        clientManager->sendRequestAndRecv();
        while(!clientManager->requestFailed()){
            std::cout<<cityid+1<<" - "<<clientManager->getInfo("name")<<" | "<<clientManager->getInfo("mapname")<<" | " \
            <<clientManager->getInfo("creator")<<" | "<<clientManager->getInfo("nplayer")<<"/"<<clientManager->getInfo("maxplayer")<<std::endl;
            cityid++;
            clientManager->setRequest("cityinfo");
            clientManager->addInfo("cityid", std::to_string(cityid));
            clientManager->sendRequestAndRecv();
        }
        int choice = makeChoice(1, cityid);
        clientManager->setRequest("joincity");
        clientManager->addInfo("cityid", std::to_string(choice-1));
        clientManager->sendRequestAndRecv();
        if(clientManager->requestFailed()){
            LOG(clientManager->getReason());
        }else{
            fail = false;
            clientManager->buildMap(clientManager->getInfo("filename"));
        }
    }
}

void CityLordClient::showMap(){
    clientManager->displayMap();
}

void CityLordClient::selectField(){
    LOG("Choose the row :");
    int crow = makeChoice(1, clientManager->getMap()->getNumberOfRows());
    LOG("Choose the column :");
    int ccol = makeChoice(1, clientManager->getMap()->getNumberOfCols());
    clientManager->setRequest("selectfield");
    clientManager->addInfo("row", std::to_string(crow-1));
    clientManager->addInfo("col", std::to_string(ccol-1));
    clientManager->sendRequestAndRecv();
    if(clientManager->topicEquals("owner")){
        LOG("You own this field.");
        std::cout<<"1 - Build"<<std::endl;
		//std::cout<<"2 - Sell"<<std::endl;
		std::cout<<"2 - Show information"<<std::endl;
		std::cout<<"3 - Upgrade"<<std::endl;
		std::cout<<"4 - Destroy"<<std::endl;
		std::cout<<"5 - Offer"<<std::endl;
		std::cout<<"6 - Hypotheque"<<std::endl;
		std::cout<<"7 - Buy back"<<std::endl;
		std::cout<<"8 - Quit"<<std::endl;

		int choice = makeChoice(1, 8);
		if(choice == 1){
            clientManager->setRequest("build");
            clientManager->addInfo("row", std::to_string(crow-1));
            clientManager->addInfo("col", std::to_string(ccol-1));
            for(int i=0;i<BuildingType::typesLength;i++){
                std::cout<<i+1<<" - "<<BuildingType::types[i].NAME<<std::endl;
            }
            int buildChoice = makeChoice(1, BuildingType::typesLength);
            clientManager->addInfo("typeindex", std::to_string(buildChoice-1));
            clientManager->sendRequestAndRecv();
            LOG(clientManager->getAnswerInfos());
        }
        else if(choice == 2){
            std::cout<<clientManager->getInfo("info")<<std::endl;
		}
        else if(choice == 3){
            clientManager->setRequest("upgrade");
            clientManager->addInfo("row", std::to_string(crow-1));
            clientManager->addInfo("col", std::to_string(ccol-1));
            clientManager->sendRequestAndRecv();
            LOG(clientManager->getAnswerInfos());

		}
        else if(choice == 4){
            clientManager->setRequest("destroy");
            clientManager->addInfo("row", std::to_string(crow-1));
            clientManager->addInfo("col", std::to_string(ccol-1));
            clientManager->sendRequestAndRecv();
            LOG(clientManager->getAnswerInfos());
        }
        else if(choice == 5){
			clientManager->setRequest("offer");
			clientManager->addInfo("row", std::to_string(crow-1));
			clientManager->addInfo("col", std::to_string(ccol-1));
			std::cout<<"Price (from 1 to 1000000000): "<<endl;
			int offeredPrice = makeChoice(1, 1000000000);
			clientManager->addInfo("offerprice", std::to_string(offeredPrice));
			clientManager->sendRequestAndRecv();
			LOG(clientManager->getAnswerInfos());
		}
		else if(choice == 6){
			clientManager->setRequest("hypotheque");
            clientManager->addInfo("row", std::to_string(crow-1));
            clientManager->addInfo("col", std::to_string(ccol-1));
            clientManager->sendRequestAndRecv();
            LOG(clientManager->getAnswerInfos());
		}
		else if(choice == 7){
 			clientManager->setRequest("buyback");
            clientManager->addInfo("row", std::to_string(crow-1));
            clientManager->addInfo("col", std::to_string(ccol-1));
            clientManager->sendRequestAndRecv();
            LOG(clientManager->getAnswerInfos());
		}
	}
	else if(clientManager->topicEquals("owner-offered")){
		LOG("You own this field, but you have offered it");
		std::cout<<"1 - Cancel offer"<<std::endl;
		std::cout<<"2 - Show information"<<std::endl;
		std::cout<<"3 - Quit"<<std::endl;
		
		int choice = makeChoice(1,3);
		if(choice == 1){
			clientManager->setRequest("offercancel");
			clientManager->addInfo("row", std::to_string(crow-1));
			clientManager->addInfo("col", std::to_string(ccol-1));
			clientManager->sendRequestAndRecv();
			LOG(clientManager->getAnswerInfos());
		}
		else if(choice == 2){
            std::cout<<clientManager->getInfo("info")<<std::endl;
		}
	}	
    else if(clientManager->topicEquals("other")){
        LOG("It's another player's field");
		std::cout<<"1 - Show information"<<std::endl;
		std::cout<<"2 - Quit"<<std::endl;
		int choice = makeChoice(1, 2);
		if(choice == 1){
            std::cout<<clientManager->getInfo("info")<<std::endl;
        }
	}
    else if(clientManager->topicEquals("purchasable")){
        LOG("This field is free for sale");
		std::cout<<"1 - Show information"<<std::endl;
		std::cout<<"2 - Buy"<<std::endl;
		std::cout<<"3 - Quit"<<std::endl;
		int choice = makeChoice(1, 3);
		if(choice == 1){
            std::cout<<clientManager->getInfo("info")<<std::endl;
		}else if(choice == 2){
            clientManager->setRequest("buy");
            clientManager->addInfo("row", std::to_string(crow-1));
            clientManager->addInfo("col", std::to_string(ccol-1));
            clientManager->sendRequestAndRecv();
            LOG(clientManager->getAnswerInfos());
		}
	}
	else{
        LOG("This case is not a field or building !");
    }
}

void CityLordClient::setupRoadblock(){
    LOG("Choose the row :");
    int crow = makeChoice(1, clientManager->getMap()->getNumberOfRows());
    LOG("Choose the column :");
    int ccol = makeChoice(1, clientManager->getMap()->getNumberOfCols());
    clientManager->setRequest("selectroad");
    clientManager->addInfo("row", std::to_string(crow-1));
    clientManager->addInfo("col", std::to_string(ccol-1));
    clientManager->sendRequestAndRecv();
    if(clientManager->topicEquals("road")){
        LOG("This road is not currently being blocked off");
        std::cout<<"Are you sure you want to set-up a roadblock here? Price : "<<clientManager->getInfo("price")<<std::endl;
        std::cout<<"1 - Yes"<<std::endl;
        std::cout<<"2 - No"<<std::endl;
        int choice = makeChoice(1, 2);
        if(choice == 1){
            clientManager->setRequest("roadblock");
            clientManager->addInfo("row", std::to_string(crow-1));
            clientManager->addInfo("col", std::to_string(ccol-1));
            clientManager->sendRequestAndRecv();
            LOG(clientManager->getAnswerInfos());
        }
    }
    else if(clientManager->topicEquals("roadblocked")){
        LOG("This road is already being blocked off");
    }
    else{
        LOG("This case is not a road !");
    }
}

void CityLordClient::showInfo(){
    clientManager->setRequest("showinfo");
    clientManager->sendRequestAndRecv();
    std::string money = clientManager->getInfo("money");
    std::string nickname = clientManager->getInfo("nickname");
    std::string nBuilding = clientManager->getInfo("nbuilding");
    std::string nEmptyField = clientManager->getInfo("nemptyfield");
	//std::string color = answer.get("color");

    std::cout<<"Your nickname : "<< nickname <<std::endl;
	std::cout<<"Your money : "<< money <<std::endl;
	std::cout<<"Number of building : "<< nBuilding <<std::endl;
	std::cout<<"Number of empty field : "<< nEmptyField <<std::endl;
	//std::cout<<"Your color : "<< color <<std::endl;
}

void CityLordClient::showCatalog(){
    clientManager->setRequest("showcatalog");
    clientManager->sendRequestAndRecv();
    std::map<std::string, std::string> map = clientManager->getMessage().getMap();
    for(std::map<std::string, std::string>::iterator iterator = map.begin(); iterator != map.end(); iterator++) {
		std::cout<<iterator->first<<" - "<<iterator->second<<std::endl;
	}
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

void CityLordClient::LOG(std::string info){
    std::cout<<"------------------------------"<<std::endl;
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




