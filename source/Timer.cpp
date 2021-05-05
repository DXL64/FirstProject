#include "Timer.h"

Timer::Timer()
{
    startTick = 0 ;
    pauseTick = 0 ;
    isPaused  = false ;
    isStarted = false ;
}
void Timer::start()
{
    isStarted = true ;
    isPaused = false ;
    startTick = SDL_GetTicks() ;
}
double Timer::getTick()
{
    if(isPaused)
        return pauseTick ;
    else
        return SDL_GetTicks() - startTick ;
}
