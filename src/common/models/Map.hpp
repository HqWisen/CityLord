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
#include <stdexcept>

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
        int addVisitor(Visitor*);
        void addVisitor(int, Location);
        void deleteVisitor(int);
        Visitor* getVisitor(int);
        int getMaxVisitors();
        bool isFull();
};

template <typename FieldType>
Map<FieldType>::Map(string fileName){
    string tmpStringTop, tmpStringBottom;
    char tmpChar;
    ifstream file(fileName);
    getline(file, tmpStringTop);
    numberOfCols = atoi(tmpStringTop.c_str());
    getline(file, tmpStringTop);
    numberOfRows = atoi(tmpStringTop.c_str());
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
    for(int row=0;row<numberOfRows;row++){
        getline(file, tmpStringTop);
        getline(file, tmpStringBottom);
        /* Construction des objets selon la lettre + ouverture des route EAST - WEST */
        for(int col=0;col<numberOfCols;col++){
            tmpChar = tmpStringBottom.at(2+(col*4));
            if (tmpChar == 'O') {
                caseMatrix[row][col] = new Obstacle(Location(row, col));
            }else if (tmpChar == 'S') {
                caseMatrix[row][col] = new BuildingSpawn(Location(row, col));
                spawnList.push_back(dynamic_cast<BuildingSpawn*>(caseMatrix[row][col]));
            }else if (tmpChar == 'F'){
                caseMatrix[row][col] = new FieldType(Location(row,col));
            }else if(tmpChar == 'R') {
                if(row == 0 || row == numberOfRows-1 || col == 0 || col == numberOfCols-1){
                    caseMatrix[row][col] = new BorderSpawn(Location(row, col));
                    spawnList.push_back(dynamic_cast<BorderSpawn*>(caseMatrix[row][col]));
                }else{
                    caseMatrix[row][col] = new Road(Location(row, col));
                }
                tmpChar = tmpStringBottom.at(col*4);
                if(tmpChar == ' '){
                    dynamic_cast<Road*>(caseMatrix[row][col])->open(Road::WEST);
                    if(col != 0){
                        if(dynamic_cast<Road*>(caseMatrix[row][col-1]) != nullptr){
                            dynamic_cast<Road*>(caseMatrix[row][col-1])->open(Road::EAST);
                        }else{
                            throw std::invalid_argument("The map try to open a case who is not a road.");
                        }
                    }
                }
            }
        }
        /* Mur extreme EAST de la ligne*/
        tmpChar = tmpStringBottom.at(numberOfCols*4);
        if(tmpChar == ' '){
            if(dynamic_cast<Road*>(caseMatrix[row][numberOfCols-1]) != nullptr){
                dynamic_cast<Road*>(caseMatrix[row][numberOfCols-1])->open(Road::EAST);
            }else{
                throw std::invalid_argument("The map try to open a case who is not a road.");
            }
        }
        /* Ouverture des routes (NORD) */
        for(int col=0;col<numberOfCols;col++){
            tmpChar = tmpStringTop.at(2+(col*4));
            if(tmpChar == ' '){
                if(dynamic_cast<Road*>(caseMatrix[row][col]) != nullptr){
                    dynamic_cast<Road*>(caseMatrix[row][col])->open(Road::NORTH);
                }else{
                    throw std::invalid_argument("The map try to open a case who is not a road.");
                }
                if(row != 0){
                    if(dynamic_cast<Road*>(caseMatrix[row-1][col]) != nullptr){
                        dynamic_cast<Road*>(caseMatrix[row-1][col])->open(Road::SOUTH);
                    }else{
                        throw std::invalid_argument("The map try to open a case who is not a road.");
                    }
                }
            }
        }
    }

    /*Ouverture des routes de la derniere lignes (SOUTH)*/
    getline(file, tmpStringTop);
    for(int col=0;col<numberOfCols;col++){
        tmpChar = tmpStringTop.at(2+(col*4));
        if(tmpChar == ' '){
            if(dynamic_cast<Road*>(caseMatrix[numberOfRows-1][col]) != nullptr){
                dynamic_cast<Road*>(caseMatrix[numberOfRows-1][col])->open(Road::SOUTH);
            }else{
                throw std::invalid_argument("The map try to open a case who is not a road.");
            }
       }
    }
    BuildingSpawn* buildingSpawn;
    for (int i=0; i<spawnList.size(); i++) {
        if ((buildingSpawn = dynamic_cast<BuildingSpawn*>(spawnList[i]))) {
            buildingSpawn->setSpawnPoint(findSpawnPoint(Location(buildingSpawn->getLocation().getRow(), buildingSpawn->getLocation().getCol())));
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
    cout<<"    ";
    for (int col=1; col<=numberOfCols; col++) {
        printf( " %3s", (to_string(col)).c_str());
    }
    cout<<"\n";
    for(int row=0;row<numberOfRows;row++){
        cout<<"    ";
        /* Mur du haut */
        for(int col=0;col<numberOfCols;col++){
            if((road = dynamic_cast<Road*>(caseMatrix[row][col])) && road->isOpen(Road::NORTH)){
                cout<<"+ ║ ";
            }else{
                cout<<"+---";
            }
        }
        cout<<"+"<<endl;
        /* Ligne des cases */
        printf( "%3s ", (to_string((row+1)).c_str()));
        for(int col=0;col<numberOfCols;col++){
            if(((road = dynamic_cast<Road*>(caseMatrix[row][col]))) && road->isOpen(Road::WEST)){
                cout<<"═";
                cout<<(caseMatrix[row][col]->print());
            }else {
                cout<<"|";
                if((field = dynamic_cast<FieldType*>(caseMatrix[row][col]))){
                    if(field->hasOwner()){
                        color = field->getOwnerColor();
                    }else{
                        color="\033[0m";
                    }
                    string item = caseMatrix[row][col]->print();
                    cout<<color<<(((item.replace(0,1," ")).replace(2,1," ")) + "\033[0m");
                }else {
                    cout<<(caseMatrix[row][col]->print());
                }
            }
        }
        /* Mur d'extreme droite */
        if(((road = dynamic_cast<Road*>(caseMatrix[row][numberOfCols-1]))) && road->isOpen(Road::EAST)){
            cout<<"═"<<endl;
        }else{
            cout<<"|"<<endl;
        }
    }
    /* Mur tout en bas */
    cout<<"    ";
    for(int col = 0;col<numberOfCols;col++){
        if((road = dynamic_cast<Road*>(caseMatrix[numberOfRows-1][col])) && road->isOpen(Road::SOUTH)){
            cout<<"+ ║ ";
        }else{
            cout<<"+---";
        }
    }
    cout<<"+"<<endl;
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
    }else if ((location.getRow()-1) >= 0) {
        if ((road = dynamic_cast<Road*>(caseMatrix[location.getRow()-1][location.getCol()]))) {
            return road->getLocation();
        }
    }else if ((location.getCol()-1) >= 0) {
        if ((road = dynamic_cast<Road*>(caseMatrix[location.getRow()][location.getCol()-1]))) {
            return road->getLocation();
        }
    }else if (((location.getRow()+1) < numberOfRows) && ((location.getCol()+1) < numberOfCols)) {
        if ((road = dynamic_cast<Road*>(caseMatrix[location.getRow()+1][location.getCol()+1]))) {
            return road->getLocation();
        }
    }else if (((location.getRow()-1) >= 0) && ((location.getCol()+1) < numberOfCols)) {
        if ((road = dynamic_cast<Road*>(caseMatrix[location.getRow()-1][location.getCol()+1]))) {
            return road->getLocation();
        }
    }else if (((location.getRow()-1) >= 0) && ((location.getCol()-1) >= 0)) {
        if ((road = dynamic_cast<Road*>(caseMatrix[location.getRow()-1][location.getCol()-1]))) {
            return road->getLocation();
        }
    }else if (((location.getRow()+1) < numberOfRows) && ((location.getCol()-1) >= 0)) {
        if ((road = dynamic_cast<Road*>(caseMatrix[location.getRow()+1][location.getCol()-1]))) {
            return road->getLocation();
        }
    }
    cout<<"WARNING BAD SPAWN"<<endl;
    return location;
}

//=========================================== Visitor ==========================================

template <typename FieldType>
int Map<FieldType>::addVisitor(Visitor* newVisitor){
    int i = -1;
    bool spaceFound = false;
    while(i<=visitorMax && !spaceFound){
        i++;
        if(visitorList[i] == nullptr){
            spaceFound = true;
            visitorList[i] = newVisitor;
        }
    }
    return i;
}

template <typename FieldType>
void Map<FieldType>::addVisitor(int visitorID, Location spawnLocation){
    visitorList[visitorID] = new Visitor(spawnLocation);
}

template <typename FieldType>
void Map<FieldType>::deleteVisitor(int index){
	delete this->visitorList[index];
	this->visitorList[index] = nullptr;
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
bool Map<FieldType>::isFull(){
    for(int i=0; i<visitorMax; i++){
        if(visitorList[i] == nullptr){
            return false;
        }
    }
    return true;
}

#endif // MAP_HPP_

