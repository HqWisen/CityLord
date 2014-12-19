#ifndef CITYLORD_HPP_
#define CITYLORD_HPP_

class CityLord{
	std::list<City> cityList;
	std::list<User> userList;
	public:
		CityLord() = default;
		void run();
		void login();
		void logout();
		void connect(City&, Player&);

};

#endif // CITYLORD_HPP_

