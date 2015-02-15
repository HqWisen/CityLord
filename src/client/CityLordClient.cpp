#include "CityLordClient.hpp"


CityLordClient::CityLordClient(char* hostname, int port) : connectionSocket(hostname, port){}

void CityLordClient::run(){
	connectionSocket.connectHost();
	LOG("You are now connected to the server.");
	beginConnection();

}

void CityLordClient::beginConnection(){
	std::cout<<M_LOGIN<<" - Login"<<std::endl;
	std::cout<<M_ACCOUNT<<" - Create an account"<<std::endl;
	int choice = makeChoice(1, 2);
	if(choice == M_LOGIN){
		connectionSocket.writeInt(M_LOGIN);
		nickname = login();
	}else if(choice == M_ACCOUNT){
		connectionSocket.writeInt(M_ACCOUNT);
		nickname = createAccount();
	}
	LOG("Your are now connected to the server with nickname : "+nickname);
}

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

std::string CityLordClient::createAccount(){
	// TODO restriction du pseudo (nb max de char etc...)
	int fail = 1;
	std::string nickname;
	LOG("To create an account enter your nickname.");
	while(fail == 1){
		std::cout<<"Nickname : ";
		std::cin>>nickname;
		connectionSocket.write(nickname);
		fail = connectionSocket.readInt();
		if(fail == 1){
			LOG("Creation failed : this nickname is already used.");
			LOG("Please enter another one.");
		}
	}
	LOG("Please save it to keep your account !");
	return nickname;
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
