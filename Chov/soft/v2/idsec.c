/*
 * @file idsec.c
 * @author  Miros³aw Lach
 * @version V.1.0
 * @date 14-12-15 19:37:35UTC
 * @brief Plik identyfikuj¹cy program. Generowany przez skrypt ChDate.exe
 * @copyright
 * <h2><center>&copy; COPYRIGHT 2014 Miroslaw Lach</center></h2>
 *
 */
#include "idsec.h"
 __attribute__((section(".idsec"))) const IdSoft_t IDSoft={
	{
		'1' ^ SECKEY0,
		'4' ^ SECKEY1,
		'1' ^ SECKEY2,
		'2' ^ SECKEY3,
		'1' ^ SECKEY4,
		'5' ^ SECKEY5,
		'1' ^ SECKEY6,
		'9' ^ SECKEY7,
		'3' ^ SECKEY8,
		'7' ^ SECKEY9,
		'3' ^ SECKEY10,
		'5' ^ SECKEY11,
		0,
	},
	{
		'0' ^ SECKEY12,
		'0' ^ SECKEY13,
		'0' ^ SECKEY14,
		'1' ^ SECKEY15,
		'9' ^ SECKEY16,
		'7' ^ SECKEY17,
		0,
	},
	{
		SECKEY18,
		SECKEY19,
		SECKEY20,
		SECKEY21,
		SECKEY22,
		SECKEY23,
		SECKEY24,
		SECKEY25,
		SECKEY26,
		SECKEY27,
		SECKEY28,
		SECKEY29,
		SECKEY30,
		SECKEY31,
		SECKEY32,
		SECKEY33,
	},
};

void ReadProcessorID(unsigned long int *id){
	id[0]=*((unsigned long int *)(0x1FFFF7E8));
	id[1]=*((unsigned long int *)(0x1FFFF7E8+4));
	id[2]=*((unsigned long int *)(0x1FFFF7E8+8));
}




