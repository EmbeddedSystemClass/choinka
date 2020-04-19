/*
 * io.h
 *
 *  Created on: Sep 7, 2011
 *      Author: mirek
 */

#ifndef IO_H_
#define IO_H_

#define CLED0_Pin GPIO_Pin_6
#define CLED0_GPIO GPIOA

#define CLED1_Pin GPIO_Pin_7
#define CLED1_GPIO GPIOA

#define CLED2_Pin GPIO_Pin_5
#define CLED2_GPIO GPIOA

#define CLED3_Pin GPIO_Pin_9
#define CLED3_GPIO GPIOA

#define CLED4_Pin GPIO_Pin_1
#define CLED4_GPIO GPIOB

#define CLED5_Pin GPIO_Pin_10
#define CLED5_GPIO GPIOA

#define CLED6_Pin GPIO_Pin_0
#define CLED6_GPIO GPIOA

#define CLED7_Pin GPIO_Pin_4
#define CLED7_GPIO GPIOA

#define CLED8_Pin GPIO_Pin_1
#define CLED8_GPIO GPIOA

#define LEDB0_Pin CLED2_Pin
#define LEDB0_GPIO CLED2_GPIO

#define LEDB1_Pin CLED5_Pin
#define LEDB1_GPIO CLED5_GPIO

#define LEDB2_Pin CLED8_Pin
#define LEDB2_GPIO CLED8_GPIO

#define LEDG0_Pin CLED1_Pin
#define LEDG0_GPIO CLED1_GPIO

#define LEDG1_Pin CLED4_Pin
#define LEDG1_GPIO CLED4_GPIO

#define LEDG2_Pin CLED7_Pin
#define LEDG2_GPIO CLED7_GPIO

#define LEDR0_Pin CLED0_Pin
#define LEDR0_GPIO CLED0_GPIO

#define LEDR1_Pin CLED3_Pin
#define LEDR1_GPIO CLED3_GPIO

#define LEDR2_Pin CLED6_Pin
#define LEDR2_GPIO CLED6_GPIO

#define DIAG_RXD_Pin GPIO_Pin_3
#define DIAG_RXD_PinSource GPIO_PinSource3
#define DIAG_RXD_GPIO GPIOA
#define DIAG_RXD_GPIO_AF GPIO_AF_1

#define DIAG_TXD_Pin GPIO_Pin_2
#define DIAG_TXD_PinSource GPIO_PinSource2
#define DIAG_TXD_GPIO GPIOA
#define DIAG_TXD_GPIO_AF GPIO_AF_1

#define SWDIO_Pin GPIO_Pin_13
#define SWDIO_GPIO GPIOA

#define SWCLK_Pin GPIO_Pin_14
#define SWCLK_GPIO GPIOA






void GPIO_Configuration(void);

#endif /* IO_H_ */
