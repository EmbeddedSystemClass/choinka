/*
 * modbus.c
 *
 *  Created on: Jun 6, 2012
 *      Author: mirek
 *      Wszystkie rejestry tworz¹ ci¹g³¹ przestrzeñ adresow¹, zaczynaj¹c¹ siê od adresu 0 w swoim rodzaju rejestru
 */

#include <stdio.h>
#if defined (STM32F103)
#include "stm32f10x.h"
#endif
#if defined (STM32F051K8)
#include "stm32f0xx.h"
#endif
#include "usart_diag.h"
#include "bits.h"
#include "crc16.h"
#include "modbusreg.h"
#include "modbus.h"

volatile char ModbusOut[MODBUSOUT];

void ModbusExceptionCode(unsigned char FunctionCode, unsigned char ExCode, int *outlen){
	MsgToUDiagLn("Modbus exception");
	ModbusOut[1]=FunctionCode+0x80;
	ModbusOut[2]=ExCode;
	*outlen=2;
}

/**
 *
 */
void ModbusServerTransaction(char *in, int inlen, int *outlen){
	unsigned short StartAddr;
	unsigned short Quantity;
	unsigned short ByteCount;
	int i;
#if MDB_READCOILS_ENABLE || MDB_READDISCRETEINPUTS_ENABLE
	int bit;
#endif
#if _Modbus_Log_
	char buf[64];
#endif
	switch (in[0]){
#if MDB_READCOILS_ENABLE
	case ReadCoils_MBF:
		MsgToUU232Ln("Read Coils function");
		StartAddr=in[1]*256+in[2];
		sprintf(buf,"StartAddr=%04hX",StartAddr);
		MsgToUU232Ln(buf);
		Quantity=in[3]*256+in[4];
		if (Quantity<1 || Quantity >0x7d0){
			ModbusExceptionCode(in[0],3,outlen);
			return;
		}
		sprintf(buf,"Quantity=%04hX",Quantity);
		MsgToUU232Ln(buf);
		if (StartAddr >= MODBUSCOILS || (StartAddr+Quantity-1) >= MODBUSCOILS){
			ModbusExceptionCode(in[0],2,outlen);
			return;
		}
		ByteCount=1;
		ModbusOut[1]=ReadCoils_MBF;
		bit = 0;
		for (i=StartAddr ; i<StartAddr+Quantity ;){
			if (TESTBIT(*(ModbusCoils[i].Var),(ModbusCoils[i].Bit))){
				SETBIT(ModbusOut[ByteCount+2],(bit));
			}else{
				RESETBIT(ModbusOut[ByteCount+2],(bit));
			}
			//sprintf(buf,"out=%02X",(unsigned int)ModbusOut[ByteCount+2]);
			//MsgToUU232Ln(buf);
			i++;
			bit++;
			if (bit>7 && i<StartAddr+Quantity){
				bit=0;
				ByteCount++;
				ModbusOut[ByteCount+2]=0;
			}
		}
		ModbusOut[2]=ByteCount;
		*outlen=ByteCount+2;
		break;
#endif
#if MDB_READDISCRETEINPUTS_ENABLE
	case ReadDiscreteInputs_MBF:
		MsgToUU232Ln("Read discrete inputs");
		StartAddr=in[1]*256+in[2];
		sprintf(buf,"StartAddr=%04hX",StartAddr);
		MsgToUU232Ln(buf);
		Quantity=in[3]*256+in[4];
		if (Quantity<1 || Quantity >0x7d0){
			ModbusExceptionCode(in[0],3,outlen);
			return;
		}
		sprintf(buf,"Quantity=%04hX",Quantity);
		MsgToUU232Ln(buf);
		if ((StartAddr >= MODBUSDISCRETEINPUTS) || ((StartAddr+Quantity-1) >= MODBUSDISCRETEINPUTS)){
			ModbusExceptionCode(in[0],2,outlen);
			return;
		}
		ByteCount=1;
		ModbusOut[1]=ReadDiscreteInputs_MBF;
		bit = 0;
		for (i=StartAddr ; i<StartAddr+Quantity ;){
			if (TESTBIT(*(ModbusDiscreteInputs[i].Var),(ModbusDiscreteInputs[i].Bit))){
				SETBIT(ModbusOut[ByteCount+2],(bit));
			}else{
				RESETBIT(ModbusOut[ByteCount+2],(bit));
			}
			//sprintf(buf,"out=%02X",(unsigned int)ModbusOut[ByteCount+2]);
			//MsgToUU232Ln(buf);
			i++;
			bit++;
			if (bit>7 && i<StartAddr+Quantity){
				bit=0;
				ByteCount++;
				ModbusOut[ByteCount+2]=0;
			}
		}
		ModbusOut[2]=ByteCount;
		*outlen=ByteCount+2;
		break;
#endif
#if MDB_READHOLDINGREGISTER_ENABLE
	case ReadHoldingRegisters_MBF:
		StartAddr=in[1]*256+in[2];
#if _Modbus_Log_
		MsgToUDiagLn("Reading holding registers");
		sprintf(buf,"StartAddr=%04hX",StartAddr);
		MsgToUDiagLn(buf);
#endif
		Quantity=in[3]*256+in[4];
		if (Quantity<1 || Quantity >0x7d){
			ModbusExceptionCode(in[0],3,outlen);
			return;
		}
#if _Modbus_Log_
		sprintf(buf,"Quantity=%04hX",Quantity);
		MsgToUDiagLn(buf);
#endif
		if ((StartAddr >= MODBUSHOLDINGREGISTERS) || ((StartAddr+Quantity-1) >= MODBUSHOLDINGREGISTERS)){
			ModbusExceptionCode(in[0],2,outlen);
			return;
		}
		ByteCount=0;
		ModbusOut[1]=ReadHoldingRegisters_MBF;
		for (i=StartAddr ; i<StartAddr+Quantity ;i++){
			ModbusOut[ByteCount+3]=ModbusHoldingRegisters[i]>>8;
			ByteCount++;
			ModbusOut[ByteCount+3]=ModbusHoldingRegisters[i] & 0xff;
			ByteCount++;
		}
		ModbusOut[2]=ByteCount;
		*outlen=ByteCount+2;
		break;
#endif
#if MDB_READINPUTREGISTERS_ENABLE
	case ReadInputRegisters_MBF:
		StartAddr=in[1]*256+in[2];
#if _Modbus_Log_
		MsgToDiagLn("Read input registers");
		sprintf(buf,"StartAddr=%04hX",StartAddr);
		MsgToDiagLn(buf);
#endif
		Quantity=in[3]*256+in[4];
		if (Quantity<1 || Quantity >0x7d){
			ModbusExceptionCode(in[0],3,outlen);
			return;
		}
		sprintf(buf,"Quantity=%04hX",Quantity);
		MsgToDiagLn(buf);
		if ((StartAddr >= MODBUSINPUTREGISTERS) || ((StartAddr+Quantity-1) >= MODBUSINPUTREGISTERS)){
			ModbusExceptionCode(in[0],2,outlen);
			return;
		}
		ByteCount=0;
		ModbusOut[1]=ReadInputRegisters_MBF;
		for (i=StartAddr ; i<StartAddr+Quantity ;i++){
			ModbusOut[ByteCount+3]=ModbusInputRegisters[i]>>8;
			ByteCount++;
			ModbusOut[ByteCount+3]=ModbusInputRegisters[i] & 0xff;
			ByteCount++;
		}
		ModbusOut[2]=ByteCount;
		*outlen=ByteCount+2;
		break;
#endif
#if MDB_WRITESINGLECOIL_ENABLE
	case WriteSingleCoil_MBF:
		MsgToDiagLn("Write single coil");
		StartAddr=in[1]*256+in[2];
		sprintf(buf,"OutputAddr=%04hX",StartAddr);
		MsgToDiagLn(buf);
		Quantity=in[3]*256+in[4];
		if (Quantity!=0 && Quantity != 0xff00){
			ModbusExceptionCode(in[0],3,outlen);
			return;
		}
		sprintf(buf,"Value=%04hX",Quantity);
		MsgToDiagLn(buf);
		if (StartAddr >= 8*MODBUSCOILS){
			ModbusExceptionCode(in[0],2,outlen);
			return;
		}
		if (Quantity == 0){
			RESETBIT(*(ModbusCoils[StartAddr].Var),ModbusCoils[StartAddr].Bit);
		}else{
			SETBIT(*(ModbusCoils[StartAddr].Var),ModbusCoils[StartAddr].Bit);
		}
		ModbusOut[1]=WriteSingleCoil_MBF;
		ModbusOut[2]=in[1];
		ModbusOut[3]=in[2];
		ModbusOut[4]=in[3];
		ModbusOut[5]=in[4];
		*outlen=5;
		break;
#endif
#if MDB_WRITESINGLEREGISTER_ENABLE
	case WriteSingleRegister_MBF:
		MsgToUDiagLn("Write single register");
		StartAddr=in[1]*256+in[2];
		sprintf(buf,"RegisterAddr=%04hX",StartAddr);
		MsgToUDiagLn(buf);
		Quantity=in[3]*256+in[4];
		if (Quantity!=0 && Quantity != 0xff00){
			ModbusExceptionCode(in[0],3,outlen);
			return;
		}
		sprintf(buf,"Value=%04hX",Quantity);
		MsgToUDiagLn(buf);
		if (StartAddr >= MODBUSHOLDINGREGISTERS){
			ModbusExceptionCode(in[0],2,outlen);
			return;
		}
		ModbusHoldingRegisters[StartAddr]=Quantity;
		ModbusOut[1]=WriteSingleRegister_MBF;
		ModbusOut[2]=in[1];
		ModbusOut[3]=in[2];
		ModbusOut[4]=in[3];
		ModbusOut[5]=in[4];
		*outlen=5;
		break;
#endif
#if MDB_WRITEMULTIPLECOILS_ENABLE
	case WriteMultipleCoils_MBF:
		MsgToDiagLn("Write Multiple Coils function");
		StartAddr=in[1]*256+in[2];
		sprintf(buf,"StartAddr=%04hX",StartAddr);
		MsgToDiagLn(buf);
		Quantity=in[3]*256+in[4];
		if (Quantity<1 || Quantity >0x7b0){
			ModbusExceptionCode(in[0],3,outlen);
			return;
		}
		sprintf(buf,"Quantity of outputs=%04hX",Quantity);
		MsgToDiagLn(buf);
		if (StartAddr >= MODBUSCOILS || (StartAddr+Quantity-1) >= MODBUSCOILS){
			ModbusExceptionCode(in[0],2,outlen);
			return;
		}
		ByteCount=6;
		bit = 0;
		for (i=StartAddr ; i<StartAddr+Quantity ;){
			if (TESTBIT(in[ByteCount],bit)){
				SETBIT(*(ModbusCoils[i].Var),(ModbusCoils[i].Bit));
			}else{
				RESETBIT(*(ModbusCoils[i].Var),(ModbusCoils[i].Bit));
			}
			//sprintf(buf,"out=%02X",(unsigned int)ModbusOut[ByteCount+2]);
			//MsgToUU232Ln(buf);
			i++;
			bit++;
			if (bit>7 && i<StartAddr+Quantity){
				bit=0;
				ByteCount++;
			}
		}
		ModbusOut[1]=WriteMultipleCoils_MBF;
		ModbusOut[2]=in[1];
		ModbusOut[3]=in[2];
		ModbusOut[4]=in[3];
		ModbusOut[5]=in[4];
		*outlen=5;
		break;
#endif
#if MDB_WRITEMULTIPLEREGISTERS_ENABLE
	case WriteMultipleRegisters_MBF:
		MsgToDiagLn("Write Multiple registers function");
		StartAddr=in[1]*256+in[2];
		sprintf(buf,"StartAddr=%04hX",StartAddr);
		MsgToDiagLn(buf);
		Quantity=in[3]*256+in[4];
		if (Quantity<1 || Quantity >0x7b){
			ModbusExceptionCode(in[0],3,outlen);
			return;
		}
		sprintf(buf,"Quantity of registers=%04hX",Quantity);
		MsgToDiagLn(buf);
		if (StartAddr >= MODBUSHOLDINGREGISTERS|| (StartAddr+Quantity-1) >= MODBUSHOLDINGREGISTERS){
			ModbusExceptionCode(in[0],2,outlen);
			return;
		}
		ByteCount=6;
		for (i=StartAddr ; i<StartAddr+Quantity ;i++){
			ModbusHoldingRegisters[i]= (in[ByteCount++]<<8);
			ModbusHoldingRegisters[i]+= in[ByteCount++];
		}
		ModbusOut[1]=WriteMultipleRegisters_MBF;
		ModbusOut[2]=in[1];
		ModbusOut[3]=in[2];
		ModbusOut[4]=in[3];
		ModbusOut[5]=in[4];
		*outlen=5;
		break;
#endif
	default:
		ModbusExceptionCode(in[0],1,outlen);
		break;
	}
}

/**
 * @brief przygotowuje ramkê klienta Modbusa, zapis zawsze dotyczy pojedynczego rejestru, odczyt mo¿e byæ
 * o wiêcej rejestrów, oblicza crc ramki
 * @param reg - numer rejestru wg standardowej nomenklatury
 * @param addr - adres klienta
 * @param buf - wskaŸnik do bufora z przygotowan¹ ramk¹
 * @param rw - odczyt (==0), zapis (!=0)
 * @param val - przy zapisie wartosæ zapisywana, przy odczycie ilosæ rejesrów
 * @return zwraca d³ugoœæ ramki
 */
int PrepareModbusClientFrame(int reg, char addr, char *buf, char rw, short val){
	int Pos=0;
	unsigned short crc;
	buf[0]=0;
#if MDB_WRITESINGLECOIL_ENABLE || MDB_READCOILS_ENABLE
	if (reg>0 && reg <1000){
		//coils
		reg--;
		if (rw){
			buf[Pos++]=addr;
			buf[Pos++]=WriteSingleCoil_MBF;
			buf[Pos++]=reg>>8;
			buf[Pos++]=reg;
			buf[Pos++]=0;
			if (val){
				buf[Pos++]=0xff;
			}else{
				buf[Pos++]=0;
			}
		}else{
			buf[Pos++]=addr;
			buf[Pos++]=ReadCoils_MBF;
			buf[Pos++]=reg>>8;
			buf[Pos++]=reg;
			buf[Pos++]=1>>8;
			buf[Pos++]=1;
		}
	}
#endif
#if MDB_READDISCRETEINPUTS_ENABLE
	if (reg >10000 && reg <=11000){
		//inputs
		reg-=10001;
		buf[Pos++]=addr;
		buf[Pos++]=ReadDiscreteInputs_MBF;
		buf[Pos++]=reg>>8;
		buf[Pos++]=reg;
		buf[Pos++]=0;
		buf[Pos++]=16;
	}
#endif
#if MDB_READINPUTREGISTERS_ENABLE
	if (reg > 30000 && reg <= 31000){
		//inputs registers
		reg-=30001;
		buf[Pos++]=addr;
		buf[Pos++]=ReadInputRegisters_MBF;
		buf[Pos++]=reg>>8;
		buf[Pos++]=reg;
		buf[Pos++]=0;
		buf[Pos++]=val;
	}
#endif
#if MDB_WRITESINGLEREGISTER_ENABLE || MDB_READHOLDINGREGISTER_ENABLE
	if (reg > 40000 && reg <= 44000){
		//holding register
		reg-=40001;
		buf[Pos++]=addr;
		if (rw){
			buf[Pos++]=WriteSingleRegister_MBF;
			buf[Pos++]=reg>>8;
			buf[Pos++]=reg;
			buf[Pos++]=val>>8;
			buf[Pos++]=val;
		}else{
			buf[Pos++]=ReadHoldingRegisters_MBF;
			buf[Pos++]=reg>>8;
			buf[Pos++]=reg;
			buf[Pos++]=0;
			buf[Pos++]=val;
		}
	}
#endif
	crc=CalcCrc16Fast_b((unsigned char*)buf,Pos);
	buf[Pos++]=crc>>8;
	buf[Pos++]=crc;
	return Pos;
}
