#include "Location.hpp"

Location::Location(int r,int c) : row(r), col(c){
}

int Location::getRow(){
    return row;
}

int Location::getCol(){
    return col;
}

void Location::setRow(int r){
    row=r;
}

void Location::setCol(int c){
    col=c;
}

std::string Location::toString(){
	std::string result;
	result +="(";
    result += std::to_string(row)+",";
    result += std::to_string(col)+")";
	return result;
}

Location Location::parse(std::string source){
    int row, col;
    int index;
    index = source.find(",");
    row = std::stoi(source.substr(1, index-1));
    source.erase(0, index+1);
    source.erase(source.size()-1, source.size());
    col = std::stoi(source);
    return Location(row, col);
}

bool Location::isEqual(Location &other){
    bool res = false;
    if(this->row==other.getRow() and this->col==other.getCol()){
        res = true;
    }
    return res;
}