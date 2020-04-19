#include "modbusreg.h"

#if MDB_READDISCRETEINPUTS_ENABLE
int ModbusInputs[MODBUSINPUTS];
#endif
#if MDB_READCOILS_ENABLE || MDB_WRITEMULTIPLECOILS_ENABLE || MDB_WRITESINGLECOIL_ENABLE
int ModbusCoilsRegister;
#endif

#if MDB_READINPUTREGISTERS_ENABLE
short int ModbusInputRegisters[MODBUSINPUTREGISTERS];
#endif

#if MDB_READHOLDINGREGISTER_ENABLE || MDB_WRITEMULTIPLEREGISTERS_ENABLE || MDB_WRITESINGLEREGISTER_ENABLE
short int ModbusHoldingRegisters[MODBUSHOLDINGREGISTERS];
#endif

#if MDB_READCOILS_ENABLE || MDB_WRITEMULTIPLECOILS_ENABLE || MDB_WRITESINGLECOIL_ENABLE
/**
 * @brief bity rw
 */
const ModbusCoil_t ModbusCoils[MODBUSCOILS]={
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 0
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 1
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 2
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 3
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 4
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 5
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 6
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 7
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 8
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 9
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 10
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 11
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 12
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 13
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 14
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 15
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 16
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 17
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 18
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 19
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 20
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 21
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 22
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 23
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 24
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 25
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 26
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 27
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 28
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 29
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 30
		},
		{
			.Var = &ModbusCoilsRegister,
			.Bit = 31
		},
};
#endif

#if MDB_READDISCRETEINPUTS_ENABLE
const ModbusDiscreteInput_t ModbusDiscreteInputs[MODBUSDISCRETEINPUTS]={
		{
			.Var = &ModbusInputs[0],
			.Bit = 0
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 1
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 2
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 3
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 4
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 5
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 6
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 7
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 8
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 9
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 10
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 11
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 12
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 13
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 14
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 15
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 16
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 17
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 18
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 19
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 20
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 21
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 22
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 23
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 24
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 25
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 26
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 27
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 28
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 29
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 30
		},
		{
			.Var = &ModbusInputs[0],
			.Bit = 31
		},
};
#endif

