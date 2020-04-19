#ifndef _TIMERS_H_
#define _TIMERS_H_

#include <stdint.h>
#define SECONDS(s) (s*1000)
enum Timers_e{
	MAINPTIMER,
	TIMERS1MS_LOT,
};
#define MainPTimer Timers1ms[MAINPTIMER]
#define LEDRTimer Timers1ms[LEDRTIMER]
#define LEDGTimer Timers1ms[LEDGTIMER]
#define SensorTimer Timers1ms[SENSORTIMER]
#define SamplesTimer Timers1ms[SAMPLESTIMER]
#define ADCTimer Timers1ms[ADCTIMER]
#define Key1Timer Timers1ms[KEY1TIMER]
#define REDETimer Timers1ms[REDETIMER]



void RefreshTimers1ms(void);
void TIM2_Configuration(void);

extern volatile uint32_t Timers1ms[TIMERS1MS_LOT];
extern volatile uint8_t Keys[3];
extern volatile uint8_t ClearLastDataTimerRqst;
extern volatile double LastDataTimer;
extern volatile uint8_t LastDataTimerSmph;
extern volatile uint8_t pwm[9];
extern volatile uint8_t velpwm[9];
extern volatile uint8_t maxpwm[9];
extern volatile int Newpwm[9];





#endif
