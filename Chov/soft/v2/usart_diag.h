#ifndef _USART_DIAG_H__
#define _USART_DIAG_H__
#include "fifobuf.h"
#include "serialcomm.h"

#define USARTdiag USART1
#define USARTdiag_IRQn USART1_IRQn
#define RCC_APBPeriph_USARTDiag RCC_APB2Periph_USART1
#define USARTDiag_RCC_APBPeriphClockCmd RCC_APB2PeriphClockCmd

#define UDIAGTBUF 512
#define UDIAGRBUF 16


extern char                  UDiagTBuf[UDIAGTBUF];
extern fifobuf_t              sUDiagTBuf;
extern char                  UDiagRBuf[UDIAGRBUF];
extern fifobuf_t              sUDiagRBuf;
extern const serialcomm_t DiagComm;


void BufUnvisibleCharToDiag(char *buf);
char EnableRS485DE(void) ;
char FromUDiagRBuffer(void);
char IsPinValid(char *c);
void MsgToUDiag(char *Msg);
void MsgToUDiagLn(char *Msg);
void MsgToUDiagLn0(void);
void ToUDiagTBuffer(char c);
void USARTdiag_Configuration(void);
char ReadUDiagRBuffer(unsigned int Pos);
void DumpMemoryToUDiag(char *mem, int size);

#endif
