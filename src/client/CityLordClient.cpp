#include "CityLordClient.hpp"


CityLordClient::CityLordClient(char* hostname, int port) : connectionSocket(hostname, port){}

void CityLordClient::run(){
	SocketMessage quitRequest("quit");
	connectionSocket.connectHost();
	LOG("You are now connected to the server.");
	beginConnection();
	sendRequest(quitRequest);
	

}

void CityLordClient::beginConnection(){
	std::cout<<"1 - Login"<<std::endl;
	std::cout<<"2 - Create an account"<<std::endl;
	int choice = makeChoice(1, 2);
	if(choice == 1){
		login();
	}else if(choice == 2){
		createAccount();
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
