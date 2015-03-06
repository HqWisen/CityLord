#ifndef MAP_HPP_
#define MAP_HPP_
/*

#include "Case.hpp"
//#include "Neighborhood.hpp"
#include "Field.hpp"
#include "Road.hpp"
#include "Obstacle.hpp"
#include "Building.hpp"
#include "Player.hpp"
#include "Visitor.hpp"
*/

#include <iostream>
#include <fstream>
#include <string>

#include "Case.hpp"
#include "Road.hpp"
#include "Field.hpp"
#include "Obstacle.hpp"

class Map{
    //Visitor* visitorList;
    //Player* playerList[8] = {nullptr};
    int numberOfRows;
    int numberOfCols;
    Case*** caseMatrix;
    //Neighborhood neighborhoods[];
    public:
        Map(std::string);
        int getNumberOfRows();
        int getNumberOfCols();
        void display();
        /*Map();
        ~Map();
		Case* getCase(Location);
		string getMapString();
		int getDimensionX();
		int getDimensionY();
        static void parseMap(string, string);*/
};

#endif // MAP_HPP_

