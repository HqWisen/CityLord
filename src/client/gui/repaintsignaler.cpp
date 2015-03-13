#include "repaintsignaler.h"

RepaintSignaler::RepaintSignaler()
{
}
void RepaintSignaler::signalRepainting(){
    emit repaintView();
}
