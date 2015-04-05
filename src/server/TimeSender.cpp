#include "TimeSender.hpp"
#include "CityUpdater.hpp"

#include <thread>
#include <chrono>
#include <iostream>

const unsigned TimeSender::MAXDAY = 15;

TimeSender::TimeSender(CityUpdater* up) : updater(up), dayRemaining(MAXDAY), \
    advanceVisitor(false), updateCity(false), pay(false), over(false){}

void TimeSender::run(){
    unsigned timer = spawnTimer;
    unsigned timer2 = moveTimer;
    SocketMessage update("updatetime");
    t.start();
    while(dayRemaining!=0){
        if(t.elapsedTime() < timer2){
        }
        else{
            timer2 += moveTimer;
            advanceVisitor = true;
           //makeVisitorsAdvance();
        }
        if(t.elapsedTime() < timer) {
        }
        else{
            timer += spawnTimer;
            updateCity = true;
            //updateCity();
            if(t.elapsedTime() < dayTimer){
            }
            else{   //nouveau jour
                pay = true;
                //makeOwnersPay();
                t.start();
                timer = spawnTimer;
                timer2 = moveTimer;
                dayRemaining -= 1;
                //std::cout<<"Day : "<<dayRemaining<<std::endl;
            }
        }
    }
    over = true;
    /*while(true){
        update.set("time", updater->getTime());
        std::cout<<"sendUpdatTime = "<<update.get("time")<<std::endl;
        updater->sendUpdateToPlayers(update);
        std::this_thread::sleep_for (std::chrono::seconds(1));
    }*/
}

std::string TimeSender::getTime(){
    /*int x = MAXDAY-dayRemaining+1;
    std::string day = to_string(x);
    int y = t.elapsedTime();
    int res = dayTimer + y;
    int hour = (res*5)/60;
    int min = (res*5)%60;
    std::stringstream str_time;
    str_time << setfill('0') << setw(2) << hour;
    str_time << ":";
    str_time << setfill('0') << setw(2) << min;
    std::string result = "Day " + day + " - " + str_time.str();
    return  result;*/

    int x = MAXDAY-dayRemaining+1;
    std::string day = to_string(x);
    int y = t.elapsedTime();
    //int res = dayTimer - y;
    int hour = (y*5)/60;
    int min = (y*5)%60;

    std::stringstream str_time;
    str_time << setfill('0') << setw(2) << hour;
    str_time << ":";
    str_time << setfill('0') << setw(2) << min;

    std::string concat = "Day " + day;
    std::string concat1 = concat + " - ";
    std::string concat2= concat1 + str_time.str();

    return  concat2;
}

bool TimeSender::isOver(){
    return over;
}

bool TimeSender::makeAdvanceVisitor(){
    return advanceVisitor;
}

bool TimeSender::makeUpdateCity(){
    return updateCity;
}

bool TimeSender::makePay(){
    return pay;
}

void TimeSender::setAdvanceVisitor(bool value){
   advanceVisitor = value;
}

void TimeSender::setUpdateCity(bool value){
    updateCity = value;
}

void TimeSender::setPay(bool value){
    pay = value;
}

