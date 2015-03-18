#ifndef LOCATION_HPP_
#define LOCATION_HPP_

#include <string>
#include <iostream>

class Location{
    int row, col;

	public:
        Location() = default;
        Location(int,int);
        Location(const Location&) = default;
        Location& operator=(const Location&) = default;
        ~Location() = default;
        int getRow();
        int getCol();
        void setRow(int);
        void setCol(int);
		std::string toString();
        static Location parse(std::string);
        bool isEqual(Location);

};

#endif // LOCATION_HPP_

