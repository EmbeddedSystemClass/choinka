#ifndef _MODBUSREG_H_
#define _MODBUSREG_H_

#ifdef DEBUG
#define _Modbus_Log_ 0
#endif
#define MDB_READDISCRETEINPUTS_ENABLE 0
#define MDB_READCOILS_ENABLE 0
#define MDB_WRITEMULTIPLECOILS_ENABLE 0
#define MDB_WRITESINGLECOIL_ENABLE 0
#define MDB_READINPUTREGISTERS_ENABLE 0
#define MDB_READHOLDINGREGISTER_ENABLE 1
#define MDB_WRITEMULTIPLEREGISTERS_ENABLE 0
#define MDB_WRITESINGLEREGISTER_ENABLE 0


/**
 * @brief struktura opisuj¹ca jedno wyjscie bitowe (odczyt,zapis)
 * @param Var - wskaznik do zmiennej zawierajacej ten bit
 * @param Bit - numer bitu
 */
typedef struct ModbusCoil_s{
	short int *Var;
	int Bit;
}ModbusCoil_t;


/**
 * @brief struktura opisujaca jedno wejscie bitowe (tylko do odczytu)
 */
typedef struct ModbusDiscreteInput_s{
	int *Var;
	int Bit;
}ModbusDiscreteInput_t;

/**
 * @brief Lista rejestrów
 */
enum ModbusInputRegisters_e{
	MBReg30001,
	MBReg30002,
	MBReg30003,
	MBReg30004,
	MBReg30005,
	MBReg30006,
	MBReg30007,
	MBReg30008,
	MBReg30009,
	MBReg30010,
	MBReg30011,
	MODBUSINPUTREGISTERS
};

enum ModbusHoldingRegisters_e{
	MBReg40001,
	MBReg40002,
	MBReg40003,
	MBReg40004,
	MBReg40005,
	MBReg40006,
	MBReg40007,
	MBReg40008,
	MBReg40009,
	MBReg40010,
	MODBUSHOLDINGREGISTERS
};

#if MDB_READDISCRETEINPUTS_ENABLE
extern int ModbusInputs[MODBUSINPUTS];
#endif
#if MDB_READCOILS_ENABLE || MDB_WRITEMULTIPLECOILS_ENABLE || MDB_WRITESINGLECOIL_ENABLE
extern int ModbusCoilsRegister;
#endif

#if MDB_READINPUTREGISTERS_ENABLE
extern short int ModbusInputRegisters[MODBUSINPUTREGISTERS];
#endif
#if MDB_READHOLDINGREGISTER_ENABLE || MDB_WRITEMULTIPLEREGISTERS_ENABLE || MDB_WRITESINGLEREGISTER_ENABLE
extern short int ModbusHoldingRegisters[MODBUSHOLDINGREGISTERS];
#endif


#endif
