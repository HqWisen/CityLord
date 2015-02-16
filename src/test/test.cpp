#include <iostream>
#include <string>
#include <map>

#include "../common/template/SocketMessage.hpp"

int main(){
	/* main de test */
	std::cout<<">>> Beginning test <<<"<<std::endl;
	SocketMessage message("login");
	message.set("username", "hakim");
	message.set("nickname", "skills");
	message.set("mail", "hakimblhya@gmail.com");
	std::cout<<message.toString()<<std::endl;
	SocketMessage parsed = SocketMessage::parse(message.toString());
	std::cout<<"parsed one = "<<parsed.toString()<<std::endl;
	std::cout<<"message one = "<<message.toString()<<std::endl;
	/*std::map<std::string, int> m;
	m["hakim"] = 18;
	std::cout<<"Result = "<<m["hakim"]<<std::endl;
	std::cout<<"Result = "<<m["haAim"]<<std::endl;
	auto search = m.find("hakkim");
	if(search != m.end()){
		std::cout<<search->first<<std::endl;
		std::cout<<search->second<<std::endl;
	}else{
		std::cout<<"Not Fund"<<std::endl;
	}*/
	return 0;

}
