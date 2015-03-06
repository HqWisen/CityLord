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
    result += "row="+std::to_string(row)+", ";
    result += "col="+std::to_string(col)+")";
	return result;
}
