#ifndef TIMER_H_
#define TIMER_H_

#include "CommonFunction.h"

class Timer{

    public:
        Timer();
        ~Timer(){;};
    void start() ;
    double getTick() ;

    private:
        double startTick ;
        double pauseTick ;

        bool isPaused ;
        bool isStarted ;


};

#endif // TIMER_H_
