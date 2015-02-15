#include <iostream>
#include <string>
#include <map>

int main(){
	/* main de test */
	std::cout<<">>> Beginning test <<<"<<std::endl;
	std::map<std::string, int> m;
	m["hakim"] = 18;
	std::cout<<"Result = "<<m["hakim"]<<std::endl;
	std::cout<<"Result = "<<m["haAim"]<<std::endl;
	auto search = m.find("hakkim");
	if(search != m.end()){
		std::cout<<search->first<<std::endl;
		std::cout<<search->second<<std::endl;
	}else{
		std::cout<<"Not Fund"<<std::endl;
	}
	return 0;

}
