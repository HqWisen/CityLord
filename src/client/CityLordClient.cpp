#include "CityLordClient.hpp"


CityLordClient::CityLordClient(char* hostname, int port) : connectionSocket(hostname, port){}

void CityLordClient::run(){
	connectionSocket.connectHost();
	LOG("You are now connected to the server.");
	beginConnection();

}

void CityLordClient::beginConnection(){
	std::cout<<"1 - Login"<<std::endl;
	std::cout<<"2 - Create an account"<<std::endl;
	int choice = makeChoice(1, 2);
	if(choice == 1){
		//login();
	}else if(choice == 2){
		createAccount();
	}
	// TODO print username
	LOG("Your are now connected to the server with username: ");
}
/*
std::string CityLordClient::login(){
	std::string nickname;
	int fail = 1;
	LOG("Enter your account nickname to log in.");
	while(fail == 1){
		std::cout<<"Nickname : ";
		std::cin>>nickname;
		connectionSocket.write(nickname);
		fail = connectionSocket.readInt();
		if(fail == 1){
			LOG("Login failed : this nickname doesn't exist.");
			LOG("Please enter another one.");
		}
	}
	return nickname;	
}
*/

void CityLordClient::createAccount(){
	// TODO restriction du pseudo (nb max de char etc...)
	int fail = 1;
	std::string username;
	SocketMessage request(ACCOUNT_REQUEST);
	SocketMessage answer;
	LOG("To create an account enter your username.");
	while(fail == 1){
		std::cout<<"Username : ";
		std::cin>>username;
		request.set("username", username);
		sendRequest(request);
		/*recvAnswer(answer);
		if(answer.getTopic() == FAILURE_TOPIC){
			LOG(answer.get("reason"));
		}*/
		fail = 0;
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
