#ifndef GENERATOR_HPP_
#define GENERATOR_HPP_


#include "../common/thread/Thread.hpp"
#include "Timer.hpp"
#include <iostream>



class Generator : public Thread{

	public:
		Generator();
		void run() override;
        void generateVisitor();

};

#endif // GENERATOR_HPP_

