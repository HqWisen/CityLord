#include "Generator.hpp"

Generator::Generator(){
    this->start();
}

void Generator::run(){
	bool stop = false;
	while(not stop){
		unsigned long timer = 10;
		Timer t;
		t.start();
		while(true){
        	if(t.elapsedTime() < timer) {
     
        	}
        	else{
                timer += 10; 
				generateVisitor();
			}
		}
	}
}

void Generator::generateVisitor(){
	std::cout<<"Visitor"<<std::endl;
}


