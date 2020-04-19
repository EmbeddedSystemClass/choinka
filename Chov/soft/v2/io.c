/**
 * @file    io.c
 * @author  Miroslaw Lach
 * @version V1.0
 * @date    16.02.2012
 * @brief   Ustawienia linii portów
 *
 * <h2><center> &copy; COPYRIGHT 2012 Miroslaw Lach</center></h2>
 */

#include "procfamily.h"
#include "io.h"



void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	  /* GPIOC Periph clock enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB , ENABLE);
// output
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
// output low speed
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_Level_1;
// output low speed no-pull
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
// output  PP low speed no-pull
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	//CLED0
	GPIO_InitStructure.GPIO_Pin=CLED0_Pin;
	GPIO_Init(CLED0_GPIO,&GPIO_InitStructure);
	GPIO_WriteBit(CLED0_GPIO,CLED0_Pin,Bit_RESET);
	//CLED1
	GPIO_InitStructure.GPIO_Pin=CLED1_Pin;
	GPIO_Init(CLED1_GPIO,&GPIO_InitStructure);
	GPIO_WriteBit(CLED1_GPIO,CLED1_Pin,Bit_RESET);
	//CLED2
	GPIO_InitStructure.GPIO_Pin=CLED2_Pin;
	GPIO_Init(CLED2_GPIO,&GPIO_InitStructure);
	GPIO_WriteBit(CLED2_GPIO,CLED2_Pin,Bit_RESET);
	//CLED3
	GPIO_InitStructure.GPIO_Pin=CLED3_Pin;
	GPIO_Init(CLED3_GPIO,&GPIO_InitStructure);
	GPIO_WriteBit(CLED3_GPIO,CLED3_Pin,Bit_RESET);
	//CLED4
	GPIO_InitStructure.GPIO_Pin=CLED4_Pin;
	GPIO_Init(CLED4_GPIO,&GPIO_InitStructure);
	GPIO_WriteBit(CLED4_GPIO,CLED4_Pin,Bit_RESET);
	//CLED5
	GPIO_InitStructure.GPIO_Pin=CLED5_Pin;
	GPIO_Init(CLED5_GPIO,&GPIO_InitStructure);
	GPIO_WriteBit(CLED5_GPIO,CLED5_Pin,Bit_RESET);
	//CLED6
	GPIO_InitStructure.GPIO_Pin=CLED6_Pin;
	GPIO_Init(CLED6_GPIO,&GPIO_InitStructure);
	GPIO_WriteBit(CLED6_GPIO,CLED6_Pin,Bit_RESET);
	//CLED7
	GPIO_InitStructure.GPIO_Pin=CLED7_Pin;
	GPIO_Init(CLED7_GPIO,&GPIO_InitStructure);
	GPIO_WriteBit(CLED7_GPIO,CLED7_Pin,Bit_RESET);
	//CLED8
	GPIO_InitStructure.GPIO_Pin=CLED8_Pin;
	GPIO_Init(CLED8_GPIO,&GPIO_InitStructure);
	GPIO_WriteBit(CLED8_GPIO,CLED8_Pin,Bit_RESET);
	// output PP middle speed
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_Level_3;
	//DIAG_TXD
	GPIO_InitStructure.GPIO_Pin=DIAG_TXD_Pin;
	GPIO_Init(DIAG_TXD_GPIO,&GPIO_InitStructure);
}

