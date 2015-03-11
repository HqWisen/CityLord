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
#include <vector>

#include "Case.hpp"
#include "Road.hpp"
#include "Field.hpp"
#include "Obstacle.hpp"

#include "Visitor.hpp"

#include "Spawn.hpp"
#include "BorderSpawn.hpp"
#include "BuildingSpawn.hpp"

using namespace std;

template <typename FieldType>
class Map{
    int visitorMax = 50;
    Visitor** visitorList;
    vector<Spawn*> spawnList;
    int numberOfRows;
    int numberOfCols;
    Case*** caseMatrix;
    //Neighborhood neighborhoods[];
    public:
        Map() = default;
        Map(std::string);
        Map(const Map&) = default;
        ~Map();
        int getNumberOfRows();
        int getNumberOfCols();
        void display();
        Location findSpawnPoint(Location);
        vector<Spawn*> getSpawnList();
        Case* getCase(Location);
        void addVisitor(Visitor*);
        void deleteVisitor(int);
        Visitor* getVisitor(int);
        int getMaxVisitors();
		void deleteVisitor(int);
        bool isFull();


/*      string getMapString();
        static void parseMap(string, string);*/
};

template <typename FieldType>
Map<FieldType>::Map(string fileName){
    string tmpString;
    ifstream file(fileName);
    getline(file, tmpString);
    numberOfCols = atoi(tmpString.c_str());
    getline(file, tmpString);
    numberOfRows = atoi(tmpString.c_str());
    //----------------------------------------------- Matrice  --------------------------------
    caseMatrix = new Case**[numberOfRows];
    for (int i=0; i<numberOfRows; i++) {
        caseMatrix[i] = new Case*[numberOfCols];
        for (int j=0; j<numberOfCols; j++) {
            caseMatrix[i][j] = nullptr;
        }
    }
    //----------------------------------------- Liste des visiteurs  --------------------------
    visitorList = new Visitor*[visitorMax];
    for(int k=0; k<visitorMax; k++){
        visitorList[k] = nullptr;
    }
    //----------------------------------------------- Parseur  --------------------------------
    Road* road;
    BorderSpawn* spawn;
    ClientField* field;
    for (int row=0; row<((numberOfRows*2)+1); row++) { //par ligne
        getline(file, tmpString);
        char tmpChar;
        // ---------------------------------------- Premiere Ligne ----------------------------
        if (row == 0) {
            for (int col=0; col<numberOfCols; col++) { //par colonne
                tmpChar = tmpString.at((col*4)+1);
                if (tmpChar == ' ') {
                    road = new BorderSpawn(Location(0, col));
                    caseMatrix[0][col] = road;
                    road->open(Road::NORTH);
                    spawnList.push_back(dynamic_cast<BorderSpawn*>(caseMatrix[0][col]));
                }
            }
        // ---------------------------------------- Derniere Ligne ----------------------------
        } else if (row == (numberOfRows*2)) {
            for (int col=0; col<numberOfCols; col++){
                tmpChar = tmpString.at((col*4)+1);
                if (tmpChar == ' ') {
                    road = dynamic_cast<Road*>(caseMatrix[numberOfRows-1][col]);
                    road->open(Road::SOUTH);
                }
            }
        // ------------------- Lignes Intermediaires (partie au-dessus des cases) -------------
        }else if ((row % 2) == 0) {
            for (int col=0; col<numberOfCols; col++) {
                tmpChar = tmpString.at((col*4)+1);
                if (tmpChar == ' ') {
                    if (caseMatrix[row/2][col] == nullptr) {
                        caseMatrix[row/2][col] = new Road(Location(row/2, col));
                    }
                    dynamic_cast<Road*>(caseMatrix[row/2][col])->open(Road::NORTH);
                    dynamic_cast<Road*>(caseMatrix[(row/2)-1][col])->open(Road::SOUTH);
                }
            }
        // ------------------------ Lignes Intermediaires (milieu des cases) -------------------
        } else {
            // ---------------------------- Premiere case --------------------------------------
            tmpChar = tmpString.at(0);
            if (tmpChar == ' ') {
                if (caseMatrix[row/2][0] == nullptr) {
                    caseMatrix[row/2][0] = new BorderSpawn(Location(row/2, 0));
                    spawnList.push_back(dynamic_cast<BorderSpawn*>(caseMatrix[row/2][0]));
                }else if (!(spawn = dynamic_cast<BorderSpawn*>(caseMatrix[row/2][0]))) {
                    caseMatrix[row/2][0] = new BorderSpawn(Location(row/2, 0), dynamic_cast<Road*>(caseMatrix[row/2][0]));
                    spawnList.push_back(dynamic_cast<BorderSpawn*>(caseMatrix[row/2][0]));
                }
                dynamic_cast<Road*>(caseMatrix[row/2][0])->open(Road::WEST);
            }
            tmpChar = tmpString.at(2);
            if (tmpChar == 'B') {
                tmpChar = tmpString.at(1);
                int player = tmpChar;
                tmpChar = tmpString.at(3);
                int building = (int) tmpChar;
                BuildingType type = BuildingType::getTypeByIndex((building/10)-2);
                int level = (building%10);
                if (level == 0){
                    level = 10;
                }
                if (player > 47){
                    caseMatrix[row/2][0] = new FieldType(Location(row/2,0));
                    if ((field = dynamic_cast<ClientField*>(caseMatrix[row/2][0]))) {
                        field->setOwnerID(player-8);
                    }
                    dynamic_cast<FieldType*>(caseMatrix[row/2][0])->buildBuilding(type, level);
                }else {
                    caseMatrix[row/2][0] = new FieldType(Location(row/2,0));
                    dynamic_cast<FieldType*>(caseMatrix[row/2][0])->buildBuilding(type, level);
                }
            }else if (tmpChar == 'O') {
                caseMatrix[row/2][0] = new Obstacle(Location(row/2, 0));
            }else if (tmpChar == 'S') {
                caseMatrix[row/2][0] = new BuildingSpawn(Location(row/2, 0), findSpawnPoint(Location(row/2, 0)));
                spawnList.push_back(dynamic_cast<BuildingSpawn*>(caseMatrix[row/2][0]));
            }else if (tmpChar == 'F'){
                tmpChar = tmpString.at(1);
                int player = tmpChar;
                if (player > 47){
                    caseMatrix[row/2][0] = new FieldType(Location(row/2,0));
                    if ((field = dynamic_cast<ClientField*>(caseMatrix[row/2][0]))) {
                        field->setOwnerID(player-8);
                    }
                }else {
                    caseMatrix[row/2][0] = new FieldType(Location(row/2,0));
                }
            }else if(tmpChar == 'R'){
                if (caseMatrix[row/2][0] == nullptr) {
                    caseMatrix[row/2][0] = new Road(Location(row/2, 0));
                }
            }
            // -------------------------- Cases suivantes --------------------------------------
            for (int col=1; col<numberOfCols; col++) {
                tmpChar = tmpString.at((col*4));
                if (tmpChar == ' ') {

                    if (caseMatrix[row/2][col-1] == nullptr) {
                        caseMatrix[row/2][col-1] = new Road(Location(row/2, col-1));
                    }
                    dynamic_cast<Road*>(caseMatrix[row/2][col-1])->open(Road::EAST);

                    if (caseMatrix[row/2][col] == nullptr) {
                        caseMatrix[row/2][col] = new Road(Location(row/2, col));
                    }
                    dynamic_cast<Road*>(caseMatrix[row/2][col])->open(Road::WEST);

                }
                tmpChar = tmpString.at((col*4)+2);
                if (tmpChar == 'B') {
                    tmpChar = tmpString.at((col*4)+1);
                    int player = tmpChar;
                    tmpChar = tmpString.at((col*4)+3);
                    int building = (int) tmpChar;
                    BuildingType type = BuildingType::getTypeByIndex((building/10)-2);
                    int level = (building%10);
                    if (level == 0){
                        level = 10;
                    }
                    if (player > 47){
                        caseMatrix[row/2][col] = new FieldType(Location(row/2,col));
                        if ((field = dynamic_cast<ClientField*>(caseMatrix[row/2][col]))) {
                            field->setOwnerID(player-8);
                        }
                        dynamic_cast<FieldType*>(caseMatrix[row/2][col])->buildBuilding(type, level);
                    }else {
                        caseMatrix[row/2][col] = new FieldType(Location(row/2,col));
                        dynamic_cast<FieldType*>(caseMatrix[row/2][col])->buildBuilding(type, level);
                    }
                }else if (tmpChar == 'O') {
                    caseMatrix[row/2][col] = new Obstacle(Location(row/2, col));
                }else if (tmpChar == 'S') {
                    caseMatrix[row/2][col] = new BuildingSpawn(Location(row/2, col), findSpawnPoint(Location(row/2, col)));
                    spawnList.push_back(dynamic_cast<BuildingSpawn*>(caseMatrix[row/2][col]));
                }else if (tmpChar == 'F'){
                    tmpChar = tmpString.at(1);
                    int player = tmpChar;
                    if (player > 47){
                        caseMatrix[row/2][col] = new FieldType(Location(row/2,col));
                        if ((field = dynamic_cast<ClientField*>(caseMatrix[row/2][col]))) {
                            field->setOwnerID(player-8);
                        }
                    }else {
                        caseMatrix[row/2][col] = new FieldType(Location(row/2,col));
                    }
                }else if(tmpChar == 'R') {
                    if (caseMatrix[row/2][col] == nullptr){
                        caseMatrix[row/2][col] = new Road(Location(row/2, col));
                    }
                }
            }
            // ---------------------------- Dernier 'mur' --------------------------------------
            tmpChar = tmpString.at(numberOfCols*4);
            if (tmpChar == ' ') {
                dynamic_cast<Road*>(caseMatrix[row/2][numberOfCols-1])->open(Road::EAST);
                caseMatrix[row/2][numberOfCols-1] = new BorderSpawn(Location(row/2, numberOfCols-1), dynamic_cast<Road*>(caseMatrix[row/2][numberOfCols-1]));
                spawnList.push_back(dynamic_cast<BorderSpawn*>(caseMatrix[row/2][numberOfCols-1]));
            }
        }
    }
    file.close();
}

template <typename FieldType>
Map<FieldType>::~Map(){
    delete[] caseMatrix;
    spawnList.clear();
}

template <typename FieldType>
int Map<FieldType>::getNumberOfRows(){
    return numberOfRows;
}

template <typename FieldType>
int Map<FieldType>::getNumberOfCols(){
    return numberOfCols;
}

template <typename FieldType>
vector<Spawn*> Map<FieldType>::getSpawnList(){
    return spawnList;
}

template <typename FieldType>
void Map<FieldType>::display(){
    string color;
    Road* road;
    FieldType* field;

    for (int row=0; row<((numberOfRows*2)+1); row++) {
        if (row == (numberOfRows*2)) {
            for (int col=0; col<numberOfCols; col++) {
                if((road = dynamic_cast<Road*>(caseMatrix[numberOfRows-1][col])) && road->isOpen(Road::SOUTH)){
                    cout<<"+ ║ ";
                }else{
                    cout<<"+---";
                }
            }
            cout<<"+"<<endl;
        }else if ((row % 2) == 0) {
            for (int col=0; col<numberOfCols; col++) {
                if((road = dynamic_cast<Road*>(caseMatrix[row/2][col])) && road->isOpen(Road::NORTH)){
                    cout<<"+ ║ ";
                }else {
                    cout<<"+---";
                }
            }
            cout<<"+"<<endl;
        }else{
            for (int col=0; col<numberOfCols; col++) {
                if(((road = dynamic_cast<Road*>(caseMatrix[row/2][col]))) && road->isOpen(Road::WEST)){
                    cout<<"═";
                    cout<<(caseMatrix[row/2][col]->print());
                }else {
                    cout<<"|";
                    if((field = dynamic_cast<FieldType*>(caseMatrix[row/2][col]))){
                        if(field->hasOwner()){
                            color = field->getOwnerColor();
                        }else{
                            color="\033[0m";
                        }
                        string item = caseMatrix[row/2][col]->print();
                        cout<<color<<(((item.replace(0,1," ")).replace(2,1," ")) + "\033[0m");
                    }else {
                        cout<<(caseMatrix[row/2][col]->print());
                    }
                }
            }
            if((road = dynamic_cast<Road*>(caseMatrix[row/2][numberOfCols-1])) && road->isOpen(Road::EAST)){
                cout<<" "<<endl;
            }else{
                cout<<"|"<<endl;
            }
        }
    }
}

template <typename FieldType>
Case* Map<FieldType>::getCase(Location location){
    return caseMatrix[location.getRow()][location.getCol()];
}

template <typename FieldType>
Location Map<FieldType>::findSpawnPoint(Location location){
    Road* road;
    if ((location.getRow()+1) < numberOfRows) {
        if ((road = dynamic_cast<Road*>(caseMatrix[location.getRow()+1][location.getCol()]))) {
            return road->getLocation();
        }
    }else if ((location.getCol()+1) < numberOfCols) {
        if ((road = dynamic_cast<Road*>(caseMatrix[location.getRow()][location.getCol()+1]))) {
            return road->getLocation();
        }
    }else if ((location.getRow()-1) > 0) {
        if ((road = dynamic_cast<Road*>(caseMatrix[location.getRow()-1][location.getCol()]))) {
            return road->getLocation();
        }
    }else if ((location.getCol()-1) > 0) {
        if ((road = dynamic_cast<Road*>(caseMatrix[location.getRow()][location.getCol()-1]))) {
            return road->getLocation();
        }
    }else if (((location.getRow()+1) < numberOfRows) && ((location.getCol()+1) < numberOfCols)) {
        if ((road = dynamic_cast<Road*>(caseMatrix[location.getRow()+1][location.getCol()+1]))) {
            return road->getLocation();
        }
    }else if (((location.getRow()-1) > 0) && ((location.getCol()+1) < numberOfCols)) {
        if ((road = dynamic_cast<Road*>(caseMatrix[location.getRow()-1][location.getCol()+1]))) {
            return road->getLocation();
        }
    }else if (((location.getRow()-1) > 0) && ((location.getCol()-1) > 0)) {
        if ((road = dynamic_cast<Road*>(caseMatrix[location.getRow()-1][location.getCol()-1]))) {
            return road->getLocation();
        }
    }else if (((location.getRow()+1) < numberOfRows) && ((location.getCol()-1) > 0)) {
        if ((road = dynamic_cast<Road*>(caseMatrix[location.getRow()+1][location.getCol()-1]))) {
            return road->getLocation();
        }
    }
    return location;
}

template <typename FieldType>
void Map<FieldType>::addVisitor(Visitor* newVisitor){
    int i = 0;
    bool spaceFound = false;
    while(i<visitorMax && !spaceFound){
        if(visitorList[i] == nullptr){
            spaceFound = true;
            visitorList[i] = newVisitor;
        }
        i++;
    }
}

template <typename FieldType>
void Map<FieldType>::deleteVisitor(int index){
    if(index<visitorMax && index>=0){
        if(visitorList[index] != nullptr){
            delete visitorList[index];
            visitorList[index] == nullptr;
        }
    }
}

template <typename FieldType>
Visitor* Map<FieldType>::getVisitor(int index){
    return visitorList[index];
}

template <typename FieldType>
int Map<FieldType>::getMaxVisitors(){
    return visitorMax;
}

template <typename FieldType>
void Map<FieldType>::deleteVisitor(int index){
	delete map.visitorList[i];
	map.visitorList[i] = nullptr;
}


/*template <typename FieldType>
bool Map<FieldType>::isFull(){
    int numberOfVisitors = 0;
    for(int i=0; i<visitorMax; i++){
        if(visitorList[i] != nullptr){
            numberOfVisitors++;
        }
    }
    if(numberOfVisitors==visitorMax){
        return true;
    return false;
    return true;
}*/

#endif // MAP_HPP_

