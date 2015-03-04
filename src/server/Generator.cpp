#include "Generator.hpp"

Generator::Generator(){
    this->start();
}

void Generator::run(){
	bool stop = false;
	while(not stop){
		unsigned long timer = 5;
		Timer t;
		t.start();
		while(true){
        	if(t.elapsedTime() < timer) {

        	}
        	else{
                t = Timer(); //reset the timer
				generateVisitor();
			}
		}
	}
}

void Generator::generateVisitor(){
	cout<<"Visitor creat"<<endl;
}


