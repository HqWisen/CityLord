#include "CityLordClient.hpp"

CityLordClient::CityLordClient(char* hostname, int port) : connectionSocket(hostname, port){}

void CityLordClient::run(){
	SocketMessage quitRequest("quit");
	connectionSocket.connectHost();
	LOG("Welcome in CityLord !");
	beginConnection();
	chooseCity();
	sendRequest(quitRequest);
	

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
	SocketMessage request, answer;
	request.setTopic("choicemap");
	sendRequest(request);
	recvAnswer(answer);
	std::map<std::string, std::string> map = answer.getMap();
	int i = 0;
	LOG("Choose a map for the city");
	for(std::map<std::string, std::string>::iterator iterator = map.begin(); iterator != map.end(); iterator++) {
		i++;
		std::cout<<i<<" - "<<iterator->second<<std::endl;
	}
	int choice = makeChoice(1, i);
	request.setTopic("createcity");
	request.set("number", std::to_string(choice));
	sendRequest(request);
	recvAnswer(answer);
	if(answer.getTopic() == "success"){
		LOG("The server created a new city with the map "+map[std::to_string(choice)]);
		LOG("You've joined the city n°"+answer.get("citynumber"));
	}else{
		// TODO handle creation failure
	}
}

void CityLordClient::joinCity(){
	std::cout<<"NOT IMPLEMENTED YET"<<std::endl;
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
	std::string username;
	SocketMessage request("login"), answer;
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
