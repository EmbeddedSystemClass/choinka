/*
 * modbus.h
 *
 *  Created on: Jun 6, 2012
 *      Author: mirek
 */

#ifndef MODBUS_H_
#define MODBUS_H_
#include "modbusreg.h"


/**
 * @brief funkcji ramki Modbus
 */
enum ModbusFunctionCodes_e{
#if MDB_READCOILS_ENABLE
	ReadCoils_MBF=0x01, //!< odczyt bitów read-write
#endif
#if MDB_READDISCRETEINPUTS_ENABLE
	ReadDiscreteInputs_MBF=0x02,//!< odczyt bitów read-only
#endif
#if MDB_READHOLDINGREGISTER_ENABLE
	ReadHoldingRegisters_MBF=0x03,//!< odczyt rejestrów 16-bit rw
#endif
#if MDB_READINPUTREGISTERS_ENABLE
	ReadInputRegisters_MBF=0x04,//!< odczyt rejestrów wejsciowych ro
#endif
#if MDB_WRITESINGLECOIL_ENABLE
	WriteSingleCoil_MBF=0x05,//!< zapis pojedynczego bitu rw
#endif
#if MDB_WRITESINGLEREGISTER_ENABLE || MDB_READHOLDINGREGISTER_ENABLE
	WriteSingleRegister_MBF=0x06,//!< zapis do rejestru 16-bit rw
#endif
#if MDB_WRITEMULTIPLECOILS_ENABLE
	WriteMultipleCoils_MBF=0x0f,//!< zapis wielu bitów rw
#endif
#if MDB_WRITEMULTIPLEREGISTERS_ENABLE
	WriteMultipleRegisters_MBF=0x10,//!< zapis do wielu rejestrów 16-bit rw
#endif
};

//#define MODBUSCOILS 32
//#define MODBUSDISCRETEINPUTS 32
#define MODBUSOUT 256
//#define MODBUSINPUTS 1
void ModbusServerTransaction(char *in, int inlen, int *outlen);
int PrepareModbusClientFrame(int reg, char addr, char *buf, char rw, short val);

extern volatile char ModbusOut[MODBUSOUT];

#endif /* MODBUS_H_ */
