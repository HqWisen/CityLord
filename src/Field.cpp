

#include<iostream>
#include "Field.hpp"


using namespace std;

void Field::display(){
	if(building){
		building->display();
	}
	else{
		cout<<" ";
	}
}

void Field::buildBuilding(Building build){
	this->building = &build;
}

/*
int main( int argc, const char* argv[] )
{
	return 0;
}
*/
