#include "User.hpp"

User::User(std::string name) : username(name){}

std::string User::getUserName(){
	return username;
}

