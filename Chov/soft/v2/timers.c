/**
  ******************************************************************************
  * @file    timers.c
  * @author  Miroslaw Lach
  * @version V3.4.0
  * @date    18.08.2011
  * @brief   Obsluga timerow.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, AUTHOR SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 Miroslaw Lach</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include "procfamily.h"
#include "io.h"
#include "timers.h"


volatile uint32_t Timers1ms[TIMERS1MS_LOT];
volatile uint8_t Keys[3];
volatile uint8_t ClearLastDataTimerRqst;
volatile double LastDataTimer;
volatile uint8_t LastDataTimerSmph;
volatile uint8_t pwm[9];
volatile uint8_t velpwm[9]={
		1,1,1,1,1,1,1,1,1
};
volatile uint8_t maxpwm[9]={
		255,
		255,
		255,
		255,
		255,
		255,
		255,
		255,
		255,
};

volatile int Newpwm[9];

void RefreshTimers1ms(void){
	volatile uint16_t i;
	//static uint32_t Ticks100ms;
	for (i=0 ; i<TIMERS1MS_LOT ; i++){
		if (Timers1ms[i]>0){
			Timers1ms[i]--;
		}
	}
}

