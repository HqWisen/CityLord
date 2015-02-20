#include "CityLordClient.hpp"

CityLordClient::CityLordClient(char* hostname, int port) : connectionSocket(hostname, port){}

void CityLordClient::run(){
	SocketMessage quitRequest("quit");
	connectionSocket.connectHost();
	LOG("Welcome in CityLord !");
	beginConnection();
	chooseCity();
	bool disconnected = false;
	while(! disconnected){
		std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
		LOG("Choose an action");
		std::cout<<"1 - Show map"<<std::endl;
		std::cout<<"2 - Select field"<<std::endl;
		std::cout<<"3 - Build"<<std::endl;
		std::cout<<"4 - Show catalog"<<std::endl;
		std::cout<<"5 - Show information"<<std::endl;
		std::cout<<"6 - Show others players's information"<<std::endl;
		std::cout<<"7 - Disconnection"<<std::endl;

		int choice = makeChoice(1, 7);
		if(choice == 1){
			showMap();
		}else if(choice == 2){
			selectField();
		}
		else if(choice == 3){
			//build();           !!! parcelle non selectionne
		}
		else if(choice == 4){
			//showCatalog();
		}
		else if(choice == 5){
			showInfo();
		}
		else if(choice == 6){
			//showInfoOthersPlayers();
		}
		else if(choice == 7){
			disconnected= true;
		}
	}
	sendRequest(quitRequest);
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
		LOG("You've joined the City n°"+answer.get("citynumber"));
	}else{
		// TODO handle creation failure
	}
}

void CityLordClient::joinCity(){
	SocketMessage request, answer;
	request.setTopic("choicecity");
	sendRequest(request);
	recvAnswer(answer);
	std::map<std::string, std::string> map = answer.getMap();
	std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
	LOG("Choose a city to play");
	int i = 0;
	for(std::map<std::string, std::string>::iterator iterator = map.begin(); iterator != map.end(); iterator++) {
		i++;
		std::cout<<iterator->first<<" - "<<iterator->second<<std::endl;
	}
	int choice = makeChoice(1, i);
	request.setTopic("joincity");
	request.set("number", std::to_string(choice));
	sendRequest(request);
	recvAnswer(answer);
	if(answer.getTopic() == "success"){
		LOG("You've joined the City n°"+answer.get("citynumber"));
	}else{
		// TODO handle join failed
	}
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
	std::string username;
	SocketMessage request("login"), answer;
	std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
	LOG("Enter your account nickname to log in.");
	while(fail){
		std::cout<<"Username : ";
		std::cin>>username;
		request.set("username", username);
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
	std::string username;
	SocketMessage request("createaccount"), answer;
	std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
	LOG("To create an account enter your username.");
	while(fail){
		std::cout<<"Username : ";
		std::cin>>username;
		request.set("username", username);
		sendRequest(request);
		recvAnswer(answer);
		fail = (answer.getTopic() == "failure");
		if (fail){
			LOG(answer.get("reason"));
		}
	}
	LOG("Please save it to keep your account !");
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

void CityLordClient::sendRequest(SocketMessage message){
	connectionSocket.write(message.toString());
}
void CityLordClient::recvAnswer(SocketMessage& answer){
	answer = SocketMessage::parse(connectionSocket.read());
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
void CityLordClient::showMap(){
	SocketMessage request("showmap");
	SocketMessage answer;
	sendRequest(request);
	recvAnswer(answer);
	std::string mapString = answer.get("map");
	Map::parseMap("resources/tmp/out.txt", mapString);
	Map map("resources/tmp/out.txt");
	map.display();
}

void CityLordClient::selectField(){
	SocketMessage request;
	SocketMessage answer; //la réponse doit etre l'appartenance de la parcelle
	request.setTopic("mapsize");
	sendRequest(request);
	recvAnswer(answer);
	int rows = std::stoi(answer.get("rows"));
	int cols = std::stoi(answer.get("cols"));
	LOG("Choose the row");
	int row = makeChoice(1, rows);
	LOG("Choose the col");
	int col = makeChoice(1, cols);
	request.setTopic("selectfield");
	request.set("row", std::to_string(row));
	request.set("col", std::to_string(col));
	sendRequest(request);
	recvAnswer(answer);
	if(answer.getTopic() == "owner"){ 
		std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
		std::cout<<"It's your field, what would you want to do ?"<<std::endl;
		std::cout<<"1 - Build"<<std::endl;
		std::cout<<"2 - Sell"<<std::endl;
		std::cout<<"3 - Show information"<<std::endl;
		std::cout<<"4 - Upgrade"<<std::endl;
		std::cout<<"5 - Destroy"<<std::endl;
		std::cout<<"6 - Quit"<<std::endl;

		int choice = makeChoice(1, 6);
		if(choice == 1){
			//build2();             !!!!!!!!!!! build2 = parcelle déjà selectionne
		}else if(choice == 2){
			//sell();
		}
		else if(choice == 3){
			//showinfo()field;
		}
		else if(choice == 4){
			//upgrade();
		}
		else if(choice == 5){
			//destroy();
		}
		else if(choice == 6){
			//quitte automatiquement
		}
	}
	else if(answer.getTopic() == "other"){ 
		std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
		std::cout<<"It's not your field, what would you want to do ?"<<std::endl;
		std::cout<<"1 - Show information"<<std::endl;
		std::cout<<"2 - Quit"<<std::endl;

		int choice = makeChoice(1, 2);
		if(choice == 1){
			//showinfofield();
		}
		else if(choice == 2){
			//quit();
		}
	}
	else{
		std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
		std::cout<<"The field selected is not selectable ! (Tree, road, ...)"<<std::endl;
		//quit()
	}
}

void CityLordClient::build1(){  // La parcelle n'est pas encore selectionnée
	SocketMessage request("build1");
	SocketMessage answer;
	sendRequest(request);
	recvAnswer(answer);

	
}

void CityLordClient::build2(){ // La parcelle est déjà selectionnée
	SocketMessage request("build2");
	SocketMessage answer; 
}

void CityLordClient::showInfo(){
	SocketMessage request("showinfo");
	SocketMessage answer; // les différentes informations
	sendRequest(request);
	recvAnswer(answer);

	std::string name = answer.get("name");
	std::string color =answer.get("color");
	std::string money = answer.get("money");	
	std::string nBuilding = answer.get("nbuilding");
	std::string nEmptyField = answer.get("nEmptyField");

	std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
	std::cout<<"Your name : "<< name <<std::endl;
	std::cout<<"Your color : "<< color <<std::endl;
	std::cout<<"Your money : "<< money <<std::endl;
	std::cout<<"Building's number : "<< nBuilding <<std::endl;
	std::cout<<"Empty field's number : "<< nEmptyField <<std::endl;
}

void CityLordClient::showCatalog(){
	SocketMessage request("showcatalog");
	SocketMessage answer; // les parcelles vendables avec leurs infos
	sendRequest(request);
	recvAnswer(answer);


}
