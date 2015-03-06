#ifndef LOCATION_HPP_
#define LOCATION_HPP_

#include <string>

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

};

#endif // LOCATION_HPP_

