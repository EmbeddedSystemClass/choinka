#ifndef __CRC16_H__
#define __CRC16_H__

unsigned short CalcCrc16Fast(unsigned char *Buffer,unsigned short Length,unsigned short CRCInit);
unsigned short CalcCrc16Fast_b(unsigned char *Buffer,unsigned short Length);

#endif
