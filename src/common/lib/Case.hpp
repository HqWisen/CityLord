#ifndef CASE_HPP_
#define CASE_HPP_

#include "Location.hpp"
#include <string>

class Case{
	protected:
        Location location;
	public:
        Case(int, int);
        Case(Location);
        Location getLocation();
        void setLocation(Location);
        virtual ~Case() = default;
        virtual std::string print() = 0;
        virtual std::string getImageName() = 0;
};

#endif // CASE_HPP_
