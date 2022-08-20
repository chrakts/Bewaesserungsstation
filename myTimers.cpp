#include "myTimers.h"


// 1:  9.9  ms
// 2:  19.8 ms
// 5:  49.4 ms
//10:  99.0 ms
//101: 1000 ms

volatile TIMER MyTimers[MYTIMER_NUM]= {	{TM_START,RESTART_YES,60,0,nextCapaMeasure},
                                        {TM_START,RESTART_YES,100,0,nextCapaSend},
                                        {TM_STOP,RESTART_NO,5000,0,stopRelais},
                                        {TM_START,RESTART_NO,5000,0,startupTimer},
                                        {TM_START,RESTART_YES,200,0,nextTempMeasure},
                                        {TM_START,RESTART_YES,600,0,nextTempSend}
};


void nextTempMeasure(uint8_t test)
{
  NEXTTempMeasure = true;
}

void nextCapaMeasure(uint8_t test)
{
  NEXTCapaMeasure = true;
}

void nextCapaSend(uint8_t test)
{
  NEXTCapaSend = true;
}

void nextTempSend(uint8_t test)
{
  NEXTTempSend = true;
}

void stopRelais(uint8_t test)
{

}

void startupTimer(uint8_t test)
{
  MyTimers[TIMER_CAPASEND].value = 6000;
  MyTimers[TIMER_TEMPSEND].value = 6000;
}
