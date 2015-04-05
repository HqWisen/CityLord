/*
#ifndef TIMESENDER_HPP_
#define TIMESENDER_HPP_



#include "../common/thread/Thread.hpp"
#include "Timer.hpp"
#include <string>

class CityUpdater;

class TimeSender : public Thread{
    static const unsigned MAXDAY;
    CityUpdater* updater;
    Timer t;
    unsigned dayRemaining;
    unsigned dayTimer = 288;
    unsigned moveTimer = 1;
    unsigned spawnTimer = 1;
    bool advanceVisitor, updateCity, pay, over;
    public:
        TimeSender(CityUpdater*);
        virtual void run() override;
        std::string getTime();
        bool makeAdvanceVisitor();
        bool makeUpdateCity();
        bool makePay();
        bool isOver();
        void setAdvanceVisitor(bool);
        void setUpdateCity(bool);
        void setPay(bool);
        };

#endif
*/

