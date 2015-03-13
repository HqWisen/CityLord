#ifndef USER_HPP_
#define USER_HPP_

#include <string>
#include <map>

#include "Player.hpp"
#include "CityManager.hpp"
class CityManager;

class User{
	std::string username;
    std::string password;
	std::map<CityManager*, Player*> playerMap;
	public:
		User() = default;
		User(const User&) = default;
	
        User(std::string, std::string);
		std::string getUserName();
        std::string getPassword();
        void initPlayer(CityManager*, int);
		Player* getPlayer(CityManager* cm){return playerMap.find(cm) != playerMap.end() ? playerMap[cm] : nullptr;};
        // TODO DESTRUCTOR OF PLAYER
};

#endif // USER_HPP_

