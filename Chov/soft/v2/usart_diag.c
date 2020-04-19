/**
  ******************************************************************************
  * @file    usart_diag.c
  * @author  Miroslaw Lach
  * @version V2.0
  * @date    18.08.2011
  * @brief   procedury diagnostycznego portu szeregowego
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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "stm32f0xx.h"
#include "ascii.h"
#include "serialcomm.h"
#include "io.h"
#include "timers.h"
#include "baudrate.h"
//#include "usart_sens.h"
#include "usart_diag.h"

char                    UDiagTBuf[UDIAGTBUF];
fifobuf_t                sUDiagTBuf={
		  //char *BufferIn;
		.BufferIn=UDiagTBuf,
		  //unsigned int Count;
		.Count=0,
		  //unsigned int FirstItemPos;
		.FirstItemPos=0,
		  //unsigned int Length;
		.Length=UDIAGTBUF

};

char                    UDiagRBuf[UDIAGRBUF];
fifobuf_t                sUDiagRBuf={
		  //char *BufferIn;
		.BufferIn=UDiagRBuf,
		  //unsigned int Count;
		.Count=0,
		  //unsigned int FirstItemPos;
		.FirstItemPos=0,
		  //unsigned int Length;
		.Length=UDIAGRBUF

};

const serialcomm_t DiagComm={
		.usart=USARTdiag,
		.fifo_rx=&sUDiagRBuf,
		.fifo_tx=&sUDiagTBuf,
};




char ReadUDiagRBuffer(unsigned int Pos){
	return serialcomm_read_b((void *)&DiagComm,Pos);
}

/*char EnableRS485DE(void) {
	char tmp;
	REDETimer = SECONDS(1) / 100;
	tmp = GPIO_ReadOutputDataBit(REDE_GPIO, REDE_Pin);
	GPIO_SetBits(REDE_GPIO, REDE_Pin);
//	GPIO_ResetBits(LEDG_GPIO, LEDG_Pin);
	return tmp;
}*/

void ToUDiagTBuffer(char c)
{
	EnableRS485DE();
	serialcomm_sendt_b((void*)&DiagComm,c);
}

char FromUDiagRBuffer(void)
{
	return serialcomm_fromr_b((void *)&DiagComm);
}

void MsgToUDiag(char *Msg)
{
	EnableRS485DE();
	serialcomm_send_str((void *)&DiagComm,Msg);
}

void MsgToUDiagLn0(void)
{
	EnableRS485DE();
	serialcomm_send_strLn0((void *)&DiagComm);
}

void MsgToUDiagLn(char *Msg)
{
	EnableRS485DE();
	serialcomm_send_strLn((void *)&DiagComm,Msg);
}

void MsgToUDiagLen(char *Msg, uint32_t len)
{
	EnableRS485DE();
	serialcomm_send_len((void *)&DiagComm,Msg,len);
}

void USARTdiag_Configuration(void){
	GPIO_InitTypeDef GPIO_InitStructure;

	  /* Enable GPIO clock */

	  /* Enable USART clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	  /* Connect PXx to USARTx_Tx */
	GPIO_PinAFConfig(DIAG_TXD_GPIO, DIAG_TXD_PinSource, DIAG_TXD_GPIO_AF);

	  /* Connect PXx to USARTx_Rx */
	GPIO_PinAFConfig(DIAG_RXD_GPIO, DIAG_RXD_PinSource, DIAG_RXD_GPIO_AF);

	  /* Configure USART Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = DIAG_TXD_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(DIAG_TXD_GPIO, &GPIO_InitStructure);

	  /* Configure USART Rx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = DIAG_RXD_Pin;
	GPIO_Init(DIAG_RXD_GPIO, &GPIO_InitStructure);

	  /* USART configuration */
	USART_Init(USARTdiag, (USART_InitTypeDef *)&Usart96008N1Params);

	USART_ITConfig(USARTdiag,USART_IT_RXNE,ENABLE);
	  /* Enable USART */
	USART_Cmd(USARTdiag, ENABLE);
}

void DumpMemoryToUDiag(char *mem, int size){
	DumpMemory((serialcomm_t *)&DiagComm,mem,size);
}

/**
 * @brief wysylanie na port diagnostyczny ciagu znakow zakonczonych zerem zawierajacych znaki niedrukowalne
 * tlumaczone na znaczenie w kodzie ASCII
 * @par buf - wskaznik do bufora ze znakami
 */
void BufUnvisibleCharToDiag(char *buf){
	char tmp[8];
	for (; *buf!=0; buf++){
		ASCIIConvertUnVisibleChar(tmp,*buf);
		MsgToUDiag(tmp);
	}
}

/**
 * Parser ramek Modbus przychodzacych z U485
 */
/*void U485_RProcess(void) {
#if _Modbus_Log_
	char buf[64];
#endif
	static char frame[64];
	static unsigned int Pos;
	unsigned short crc;
	ModbClientRequest_t ModbClientRequest;
	int i;
	switch (psMdbR) {
	case None_MdbR:
		if (ModbComm.fifo_rx->Count > 0){
			FromUModbRBuffer();
		}
		break;
	case Start_MdbR:
		if (ModbComm.fifo_rx->Count > 0) {
#if (_Modbus_Log_)
			MsgToUDiagLn("Modbus frame?");
#endif
			ModbusServerTimer = SECONDS(1)/10;
			Pos = 0;
			psMdbR = GathBytes_MdbR;
			break;
		}
		break;
	case GathBytes_MdbR:
		if (ModbComm.fifo_rx->Count > 0) {
			frame[Pos] = FromUModbRBuffer();
			Pos++;
			if (ModbusServerTimer < SECONDS(1) / 10)
				ModbusServerTimer = SECONDS(1) / 10;
		}
		if (Pos > sizeof(frame) - 1) {
			psMdbR = Start_MdbR;
		}
		if (ModbusServerTimer == 0) {
			psMdbR = AnalFrame_MdbR;
		}
		break;
	case AnalFrame_MdbR:
		if (Pos > 3) {
			crc = CalcCrc16Fast_b((unsigned char*) frame, Pos - 2);
			if (crc == (frame[Pos - 2] * 256 + frame[Pos - 1])) {
				if (frame[0] == AppConfig.ModbAddress) {
#if _Modbus_Log_
					MsgToUDiag("Frame: ");
					for (i=0; i<Pos; i++) {
						sprintf(buf,"[%02X]",(int)frame[i]);
						MsgToUDiag(buf);
					}
					sprintf(buf,"\r\nCrc ok. DevAddr=%u",(unsigned int)frame[0]);
					MsgToUDiagLn(buf);
#endif
					switch (frame[1]) {
#if MDB_READHOLDINGREGISTER_ENABLE
					case ReadHoldingRegisters_MBF:
						ModbClientRequest.Code = ReadHoldingRegisters_MBF;
						i = frame[2] * 256 + frame[3];
						ModbClientRequest.pars[0] = i;
#if _Modbus_Log_
						MsgToUDiagLn("Read holding registers");
						sprintf(buf,"Starting Addr=%u",i);
						MsgToUDiagLn(buf);
#endif
						i = frame[4] * 256 + frame[5];
						ModbClientRequest.pars[1] = i;
#if _Modbus_Log_
						sprintf(buf,"RegistersCount=%u",i);
						MsgToUDiagLn(buf);
#endif
						afifo_to_update(&ModbClientRequestesFifo,
								(void *) &ModbClientRequest);
						break;
#endif
#if MDB_READINPUTREGISTERS_ENABLE
						case ReadInputRegisters_MBF:
						i=frame[2]/2;
#if _Modbus_Log_
						MsgToDiagLn("Read input registers");
						sprintf(buf,"RegistersCount=%u",i);
						MsgToDiagLn(buf);
#endif
						for (i=0; i<frame[2]/2; i++) {
							ServerFrame.val=frame[i*2+3]<<8;
							ServerFrame.frame[0]=frame[i*2+3];
							ServerFrame.frame[1]=frame[i*2+4];
							ServerFrame.val|=frame[i*2+4];
#if _Modbus_Log_
							sprintf(buf,"val=0x%04hX",ServerFrame.val);
							MsgToDiagLn(buf);
							sprintf(buf,"val(int)=%d",ServerFrame.val);
							MsgToDiagLn(buf);
							sprintf(buf,"val(uint)=%u",(unsigned int)ServerFrame.val);
							MsgToDiagLn(buf);
#endif
							afifo_to_update(&ModbusServerFramesFifo,(void*)&ServerFrame);
						}
						break;
#endif
					default:
#if _Modbus_Log_
						MsgToUDiagLn("Unknown Modbus code");
#endif
						break;
					}
				}
			} else {
#if _Modbus_Log_
				MsgToUDiagLn("Modbus frame incorrect");
#endif
			}
		} else {
		}
		psMdbR = Start_MdbR;
		break;
	default:
		break;
	}
}

void U485_ServerProcess(void) {
	char buf[64];
	int len;
#if _Modbus_Log_
	int i;
#endif
	uint16_t crc;
	ModbClientRequest_t ModbClientRequest;
	switch (psMdb) {
	case None_Mdb:
		if (ModbClientRequestesFifo.count>0){
			afifo_from(&ModbClientRequestesFifo, (void *) &ModbClientRequest);
		}
		break;
	case Start_Mdb:
		psMdb = Send_Mdb;
		break;
	case Send_Mdb:
		if (ModbClientRequestesFifo.count == 0)
			break;
		afifo_from(&ModbClientRequestesFifo, (void *) &ModbClientRequest);
		buf[0] = ModbClientRequest.Code;
		buf[1] = (ModbClientRequest.pars[0]) >> 8; //StartAddress
		buf[2] = (ModbClientRequest.pars[0]) & 0xff; //StartAddress
		buf[3] = (ModbClientRequest.pars[1] >> 8); //Bytes count
		buf[4] = (ModbClientRequest.pars[1]);
		ModbusServerTransaction(buf, 5, &len);
		ModbusOut[0] = AppConfig.ModbAddress;
		len++;
		crc = CalcCrc16Fast_b((unsigned char*) ModbusOut, len);
		ModbusOut[len++] = crc >> 8;
		ModbusOut[len++] = crc;
#if _Modbus_Log_
		MsgToUDiag("Frame: ");
		for (i=0; i<len; i++) {
			sprintf(buf,"[%02X]",(int)ModbusOut[i]);
			MsgToUDiag(buf);
		}
#endif
		MsgToUDiagLen(ModbusOut, len);
		psMdb = Start_Mdb;
		break;
	default:
		break;
	}
}
*/
