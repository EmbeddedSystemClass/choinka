#include <stdlib.h>
#include "procfamily.h"
#include "io.h"
#include "timers.h"
#include "muldiv.h"
#include "adc.h"
#include "gradation.h"

typedef struct{
	const uint32_t UID31_0;/*!< UID(31:0): x and y coordinates on the wafer expressed in BCD format, address offset: 0x00 */
	const uint32_t UID63_32;/*!< UID(63:32): [63:40] lot number (ASCII encoded), [39:32] wafer number (8-bit unsigned number), address offset: 0x04 */
	const uint32_t UID95_64;/*!< UID(95:64): number (ASCII encoded), Address offset: 0x08 */
}SIGNATURE_TypeDef;

#define SIGNATURE_BASE (0x1FFFF7AC)
#define SIGNATURE      ((SIGNATURE_TypeDef *) SIGNATURE_BASE)

#define PULSEDIRUP 0
#define PULSEDIRDOWN 1

volatile uint16_t counter;
volatile uint16_t pulse[9];
//volatile uint16_t pulsemax[9];
volatile uint16_t pulsedir[9];
volatile uint32_t DominantCounter;
volatile uint16_t pulsemaxidx[9];
volatile uint16_t pulseidx[9];
volatile uint16_t retardmax[9];
volatile uint16_t retard[9];

void DominantColor(void){
	int i;
	//uint16_t max;
	//do{
		pulsemaxidx[0] = rand() % (GRADATIONTABLE);
	//}while(pulsemaxidx[0] < GRADATIONTABLE/3);
	//do{
		pulsemaxidx[1] = rand() % (GRADATIONTABLE);
	//}while (pulsemaxidx[1] == pulsemaxidx[0] || pulsemaxidx[1] < GRADATIONTABLE/3);
	//do {
		pulsemaxidx[2] = rand() % (GRADATIONTABLE);
	//}while (pulsemaxidx[2] == pulsemaxidx[0] || pulsemaxidx[2] == pulsemaxidx[1] || pulsemaxidx[2] < GRADATIONTABLE/3);
/*	max = 0;
	d = 0;
	for (i = 0 ; i<3 ; i++){
		if (pulsemaxidx[i]> max){
			max = pulsemaxidx[i];
			d = i;
		}
	}
	switch(d){
	case 0:
		//dominuje kolor 0, potem 1, potem 2
		pulsemaxidx[1] = UIMulDiv(pulsemaxidx[0],1,4);
		pulsemaxidx[2] = UIMulDiv(pulsemaxidx[1],1,2);
		break;
	case 1:
		//dominuje kolor 1, potem 2, potem 0
		pulsemaxidx[2] = UIMulDiv(pulsemaxidx[1],1,4);
		pulsemaxidx[0] = UIMulDiv(pulsemaxidx[2],1,2);
		break;
	case 2:
		//dominuje kolor 2, potem 0, potem 1
		pulsemaxidx[0] = UIMulDiv(pulsemaxidx[2],1,4);
		pulsemaxidx[1] = UIMulDiv(pulsemaxidx[0],1,2);
		//pulsemaxidx[2] /= 2;
		break;
	}*/
	//do{
		pulsemaxidx[3] = rand() % (GRADATIONTABLE);
	//}while(pulsemaxidx[3] < GRADATIONTABLE/3);
	//do{
		pulsemaxidx[4] = rand() % (GRADATIONTABLE);
	//}while (pulsemaxidx[4] == pulsemaxidx[3] || pulsemaxidx[4] < GRADATIONTABLE/3);
	//do {
		pulsemaxidx[5] = rand() % (GRADATIONTABLE);
	//}while (pulsemaxidx[5] == pulsemaxidx[3] || pulsemaxidx[5] == pulsemaxidx[4] || pulsemaxidx[5] < GRADATIONTABLE/3);
/*	max = 0;
	d = 0;
	for (i = 3 ; i<6 ; i++){
		if (pulsemax[i]> max){
			max = pulsemax[i];
			d = i;
		}
	}
	switch(d){
	case 3:
		//dominuje kolor 0, potem 1, potem 2
		pulsemax[4] = pulsemax[3] / 8;
		pulsemax[5] = pulsemax[4] / 2;
		break;
	case 4:
		//dominuje kolor 1, potem 2, potem 0
		pulsemax[5] = pulsemax[4] / 8;
		pulsemax[3] = pulsemax[5] / 2;
		break;
	case 5:
		//dominuje kolor 2, potem 0, potem 1
		pulsemax[3] = pulsemax[5] / 8;
		pulsemax[4] = pulsemax[3] / 2;
		pulsemax[3] /= 2;
		break;
	}*/
//	do{
		pulsemaxidx[6] = rand() % (GRADATIONTABLE);
	//}while(pulsemaxidx[6] < GRADATIONTABLE/3);
	//do{
		pulsemaxidx[7] = rand() % (GRADATIONTABLE);
	//}while (pulsemaxidx[7] == pulsemaxidx[6] || pulsemaxidx[7] < GRADATIONTABLE/3);
	//do {
		pulsemaxidx[8] = rand() % (GRADATIONTABLE);
	//}while (pulsemaxidx[8] == pulsemaxidx[6] || pulsemaxidx[8] == pulsemaxidx[7] || pulsemaxidx[8] < GRADATIONTABLE/3);
/*	max = 0;
	d = 0;
	for (i = 6 ; i<9 ; i++){
		if (pulsemax[i]> max){
			max = pulsemax[i];
			d = i;
		}
	}
	switch(d){
	case 6:
		//dominuje kolor 0, potem 1, potem 2
		pulsemax[7] = pulsemax[6] / 8;
		pulsemax[8] = pulsemax[7] / 2;
		break;
	case 7:
		//dominuje kolor 1, potem 2, potem 0
		pulsemax[8] = pulsemax[7] / 8;
		pulsemax[6] = pulsemax[8] / 2;
		break;
	case 8:
		//dominuje kolor 2, potem 0, potem 1
		pulsemax[6] = pulsemax[8] / 8;
		pulsemax[7] = pulsemax[6] / 2;
		pulsemax[8] /= 2;
		break;
	}*/
	do{
		DominantCounter = (uint32_t)(rand() % 0xffff);
	}while (DominantCounter < 128);
	for (i = 0 ; i < 9; i++){
		retardmax[i] = 0 + rand() % 32;
	}
}

unsigned int GetSeedValue(void){
	int i;
	unsigned int result = 0;
	uint16_t Value;
	for (i = 0 ; i<32 ; i++){
		/* Test EOC flag */
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
		Value =ADC_GetConversionValue(ADC1);
		result <<= 1;
		if (Value & 0x01){
			result++;
		}
	}
	return result;
}

int main(void)
{
	unsigned int s;
	SystemCoreClockUpdate();
	//SysTick_Config(SystemCoreClock/50000);
	ADC_Config();
	GPIO_Configuration();
	s = GetSeedValue();
	srand(s);
	DominantColor();
    while(1)
    {
    	counter++;
    	if (counter >= MAXCOUNTER){
    		for (s = 0 ; s < 9 ; s++){
    			retard[s]++;
    		}
    		if (retard[0] > retardmax[0]){
    			retard[0] = 0;
        		if (pulsedir[0] == PULSEDIRUP){
        			if (pulseidx[0] >=pulsemaxidx[0]){
        				pulsedir[0] = PULSEDIRDOWN;
        			}else{
        				pulseidx[0]++;
        			}
        		}else{
        			if (pulseidx[0] > 0){
        				pulseidx[0]--;
        			}else{
        				pulsedir[0] = PULSEDIRUP;
        			}
        		}
        		pulse[0] = UIMulDiv(GradationTable[pulseidx[0]],MAXCOUNTER,10000);
    		}
    		if (retard[1] > retardmax[1]){
    			retard[1] = 0;
        		if (pulsedir[1] == PULSEDIRUP){
        			if (pulseidx[1] >=pulsemaxidx[1]){
        				pulsedir[1] = PULSEDIRDOWN;
        			}else{
        				pulseidx[1]++;
        			}
        		}else{
        			if (pulseidx[1] > 0){
        				pulseidx[1]--;
        			}else{
        				pulsedir[1] = PULSEDIRUP;
        			}
        		}
        		pulse[1] = UIMulDiv(GradationTable[pulseidx[1]],MAXCOUNTER,10000);
    		}
    		if (retard[2] > retardmax[2]){
    			retard[2] = 0;
        		if (pulsedir[2] == PULSEDIRUP){
        			if (pulseidx[2] >=pulsemaxidx[2]){
        				pulsedir[2] = PULSEDIRDOWN;
        			}else{
        				pulseidx[2]++;
        			}
        		}else{
        			if (pulseidx[2] > 0){
        				pulseidx[2]--;
        			}else{
        				pulsedir[2] = PULSEDIRUP;
        			}
        		}
        		pulse[2] = UIMulDiv(GradationTable[pulseidx[2]],MAXCOUNTER,10000);
    		}
    		if (retard[3] > retardmax[3]){
    			retard[3] = 0;
        		if (pulsedir[3] == PULSEDIRUP){
        			if (pulseidx[3] >=pulsemaxidx[3]){
        				pulsedir[3] = PULSEDIRDOWN;
        			}else{
        				pulseidx[3]++;
        			}
        		}else{
        			if (pulseidx[3] > 0){
        				pulseidx[3]--;
        			}else{
        				pulsedir[3] = PULSEDIRUP;
        			}
        		}
        		pulse[3] = UIMulDiv(GradationTable[pulseidx[3]],MAXCOUNTER,10000);
    		}
    		if (retard[4] > retardmax[4]){
    			retard[4] = 0;
        		if (pulsedir[4] == PULSEDIRUP){
        			if (pulseidx[4] >=pulsemaxidx[4]){
        				pulsedir[4] = PULSEDIRDOWN;
        			}else{
        				pulseidx[4]++;
        			}
        		}else{
        			if (pulseidx[4] > 0){
        				pulseidx[4]--;
        			}else{
        				pulsedir[4] = PULSEDIRUP;
        			}
        		}
        		pulse[4] = UIMulDiv(GradationTable[pulseidx[4]],MAXCOUNTER,10000);
    		}
    		if (retard[5] > retardmax[5]){
    			retard[5] = 0;
        		if (pulsedir[5] == PULSEDIRUP){
        			if (pulseidx[5] >=pulsemaxidx[5]){
        				pulsedir[5] = PULSEDIRDOWN;
        			}else{
        				pulseidx[5]++;
        			}
        		}else{
        			if (pulseidx[5] > 0){
        				pulseidx[5]--;
        			}else{
        				pulsedir[5] = PULSEDIRUP;
        			}
        		}
        		pulse[5] = UIMulDiv(GradationTable[pulseidx[5]],MAXCOUNTER,10000);
    		}
    		if (retard[6] > retardmax[6]){
    			retard[6] = 0;
        		if (pulsedir[6] == PULSEDIRUP){
        			if (pulseidx[6] >=pulsemaxidx[6]){
        				pulsedir[6] = PULSEDIRDOWN;
        			}else{
        				pulseidx[6]++;
        			}
        		}else{
        			if (pulseidx[6] > 0){
        				pulseidx[6]--;
        			}else{
        				pulsedir[6] = PULSEDIRUP;
        			}
        		}
        		pulse[6] = UIMulDiv(GradationTable[pulseidx[6]],MAXCOUNTER,10000);
    		}
    		if (retard[7] > retardmax[7]){
    			retard[7] = 0;
        		if (pulsedir[7] == PULSEDIRUP){
        			if (pulseidx[7] >=pulsemaxidx[7]){
        				pulsedir[7] = PULSEDIRDOWN;
        			}else{
        				pulseidx[7]++;
        			}
        		}else{
        			if (pulseidx[7] > 0){
        				pulseidx[7]--;
        			}else{
        				pulsedir[7] = PULSEDIRUP;
        			}
        		}
        		pulse[7] = UIMulDiv(GradationTable[pulseidx[7]],MAXCOUNTER,10000);
    		}
    		if (retard[8] > retardmax[8]){
    			retard[8] = 0;
        		if (pulsedir[8] == PULSEDIRUP){
        			if (pulseidx[8] >=pulsemaxidx[8]){
        				pulsedir[8] = PULSEDIRDOWN;
        			}else{
        				pulseidx[8]++;
        			}
        		}else{
        			if (pulseidx[8] > 0){
        				pulseidx[8]--;
        			}else{
        				pulsedir[8] = PULSEDIRUP;
        			}
        		}
        		pulse[8] = UIMulDiv(GradationTable[pulseidx[8]],MAXCOUNTER,10000);
    		}
    		if (DominantCounter>0){
    			DominantCounter-- ;
    		}else{
    			DominantColor();
    		}
    		counter = 0;
    	}
    	if (counter >= pulse[0]){
    		CLED0_GPIO->BRR = CLED0_Pin;//GPIO_ResetBits(CLED0_GPIO,CLED0_Pin);
    	}else{
    		CLED0_GPIO->BSRR = CLED0_Pin;//GPIO_SetBits(CLED0_GPIO,CLED0_Pin);
    	}
    	if (counter >= pulse[1]){
    		CLED1_GPIO->BRR = CLED1_Pin;//GPIO_ResetBits(CLED0_GPIO,CLED0_Pin);
    	}else{
    		CLED1_GPIO->BSRR = CLED1_Pin;//GPIO_SetBits(CLED0_GPIO,CLED0_Pin);
    	}
    	if (counter >= pulse[2]){
    		CLED2_GPIO->BRR = CLED2_Pin;//GPIO_ResetBits(CLED0_GPIO,CLED0_Pin);
    	}else{
    		CLED2_GPIO->BSRR = CLED2_Pin;//GPIO_SetBits(CLED0_GPIO,CLED0_Pin);
    	}
    	if (counter >= pulse[3]){
    		CLED3_GPIO->BRR = CLED3_Pin;//GPIO_ResetBits(CLED0_GPIO,CLED0_Pin);
    	}else{
    		CLED3_GPIO->BSRR = CLED3_Pin;//GPIO_SetBits(CLED0_GPIO,CLED0_Pin);
    	}
    	if (counter >= pulse[4]){
    		CLED4_GPIO->BRR = CLED4_Pin;//GPIO_ResetBits(CLED0_GPIO,CLED0_Pin);
    	}else{
    		CLED4_GPIO->BSRR = CLED4_Pin;//GPIO_SetBits(CLED0_GPIO,CLED0_Pin);
    	}
    	if (counter >= pulse[5]){
    		CLED5_GPIO->BRR = CLED5_Pin;//GPIO_ResetBits(CLED0_GPIO,CLED0_Pin);
    	}else{
    		CLED5_GPIO->BSRR = CLED5_Pin;//GPIO_SetBits(CLED0_GPIO,CLED0_Pin);
    	}
    	if (counter >= pulse[6]){
    		CLED6_GPIO->BRR = CLED6_Pin;//GPIO_ResetBits(CLED0_GPIO,CLED0_Pin);
    	}else{
    		CLED6_GPIO->BSRR = CLED6_Pin;//GPIO_SetBits(CLED0_GPIO,CLED0_Pin);
    	}
    	if (counter >= pulse[7]){
    		CLED7_GPIO->BRR = CLED7_Pin;//GPIO_ResetBits(CLED0_GPIO,CLED0_Pin);
    	}else{
    		CLED7_GPIO->BSRR = CLED7_Pin;//GPIO_SetBits(CLED0_GPIO,CLED0_Pin);
    	}
    	if (counter >= pulse[8]){
    		CLED8_GPIO->BRR = CLED8_Pin;//GPIO_ResetBits(CLED0_GPIO,CLED0_Pin);
    	}else{
    		CLED8_GPIO->BSRR = CLED8_Pin;//GPIO_SetBits(CLED0_GPIO,CLED0_Pin);
    	}
    }
}
