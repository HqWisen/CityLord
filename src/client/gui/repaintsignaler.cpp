#include "repaintsignaler.h"

RepaintSignaler::RepaintSignaler()
{
}
void RepaintSignaler::signalRepainting(){
    emit repaintView();
}
void RepaintSignaler::signalActiving(std::string info, Location location){
    emit activeButton(info, location);
}
