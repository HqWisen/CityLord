#ifndef USER_HPP_
#define USER_HPP_

#include <string>
#include <map>

#include "Player.hpp"

class CityManager;

class User{
	std::string username;
	std::map<CityManager*, Player> playerMap;
	public:
		User(std::string);
};

#endif // USER_HPP_

