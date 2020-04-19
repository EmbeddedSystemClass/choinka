/**
  ******************************************************************************
  * @file    SysTick/SysTick_Example/stm32f0xx_it.c 
  * @author  MCD Application Team
  * @version V1.3.0
  * @date    16-January-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "stm32f0xx.h"
#include "timers.h"
#include "usart_diag.h"
#include "io.h"
#include "interrupt.h"

void NVIC_Configuration(void){
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the UARTdiag global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USARTdiag_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/** @addtogroup STM32F0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup SysTick_Example
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
/*void HardFault_Handler(void)
{*/
  /* Go to infinite loop when Hard Fault exception occurs */
  /*while (1)
  {
  }
}*/

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

const GPIO_TypeDef * LED_GPIOTable[9]={
		CLED0_GPIO,
		CLED1_GPIO,
		CLED2_GPIO,
		CLED3_GPIO,
		CLED4_GPIO,
		CLED5_GPIO,
		CLED6_GPIO,
		CLED7_GPIO,
		CLED8_GPIO,
};
const uint32_t LED_PinTable[9]={
		CLED0_Pin,
		CLED1_Pin,
		CLED2_Pin,
		CLED3_Pin,
		CLED4_Pin,
		CLED5_Pin,
		CLED6_Pin,
		CLED7_Pin,
		CLED8_Pin,
};
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
/*void SysTick_Handler(void)
{
	static uint8_t PWMcnt[9];
	static volatile uint8_t counter;
	//static volatile uint8_t maxone[9];
	uint8_t i;
	GPIO_WriteBit(DIAG_TXD_GPIO,DIAG_TXD_Pin,Bit_SET);
	counter++;
	if (counter==0){
		memset(PWMcnt,0,sizeof(PWMcnt));
	}else{
		for (i=0 ; i<9 ; i++){
			PWMcnt[i]++;
			if (PWMcnt[i]<pwm[i]){
				GPIO_WriteBit((GPIO_TypeDef *)LED_GPIOTable[i],LED_PinTable[i],Bit_SET);
			}else{
				GPIO_WriteBit((GPIO_TypeDef *)LED_GPIOTable[i],LED_PinTable[i],Bit_RESET);
			}
		}
	}
	for (i=0 ; i<TIMERS1MS_LOT ; i++){
		if (Timers1ms[i]>0){
			Timers1ms[i]--;
		}
	}
	GPIO_WriteBit(DIAG_TXD_GPIO,DIAG_TXD_Pin,Bit_RESET);
}*/

/*void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USARTdiag,USART_IT_TXE) != RESET){
		if (sUDiagTBuf.Count>0){
			USART_SendData(USARTdiag,FromFIFOBuf(&sUDiagTBuf));
		}else{
			USART_ITConfig(USARTdiag,USART_IT_TXE,DISABLE);
		}
	}
	if (USART_GetITStatus(USARTdiag,USART_IT_RXNE) != RESET){
		ToFIFOBuf(&sUDiagRBuf,USART_ReceiveData(USARTdiag),0);
	}
}*/

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
