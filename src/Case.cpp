

#include<iostream>
#include "Case.hpp"


using namespace std;

Case::Case(Obstacle obs){
	this->obs = &obs;
	this->road = NULL;
	this->field = NULL;
}

Case::Case(Field field){
	this->field = &field;
	this->road = NULL;
	this->obs = NULL;
}

Case::Case(Road road){
	this->road = &road;
	this->obs = NULL;
	this->field = NULL;
}

void Case::display(){
	cout<<endl;
}

int main( int argc, const char* argv[] )
{
	return 0;
}