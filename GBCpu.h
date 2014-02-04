/*

GBCpu: Here lies the Cpu interpreter. Command will be passed from memory

To the Cpu interpreter to be translated into actual "portable" architecture dynamically.

For info on supported commands see: z80 CPU documentation & 
http://gbdev.gg8.se/files/docs/mirrors/pandocs.html#cpucomparisionwithz80

*/

#include "GBCore.h"

// CPU state flags
u8 cpu_wait_for_interrupt;
u8 cpu_stop;
u8 cpu_interrupt_mode;


// Keeps a link to GB_main_memory
extern u8* GB_main_memory;

/*
Game boy Registers:
 
 The AF Register is very special,
 The High register is the accumulator, where operations are stored,
 
 The Low register is used for flags
 The Flag Register (lower 8bit of AF register)
 Bit  Name  Set Clr  Expl.
 7    zf    Z   NZ   Zero Flag
 6    n     -   -    Add/Sub-Flag (BCD)
 5    h     -   -    Half Carry Flag (BCD)
 4    cy    C   NC   Carry Flag
 3-0  -     -   -    Not used (always zero)
*/
u8 GB_CPU_reg_AF[2];
u8 GB_CPU_reg_BC[2];
u8 GB_CPU_reg_DE[2];
u8 GB_CPU_reg_HL[2];

u16 GB_CPU_reg_SP; 	// Stack Pointer
u16 GB_CPU_reg_PC; 	// Program Counter

void u8_Set_Bit(u8* wordToSet, u8 bitNumb);
void u16_Set_Bit(u16* wordToSet, u8 bitNumb);
void u8_Reset_Bit(u8* wordToReset, u8 bitNumb);
void u16_Reset_Bit(u16* wordToReset, u8 bitNumb);
u8 u8_Test_Bit(u8* wordToTest, u8 bitNumb);
u16 u16_Test_Bit(u16* wordToTest, u8 bitNumb);


void GB_CPU_Set_Flag_Z() { u8_Set_Bit(&GB_CPU_reg_AF[1],7); }
void GB_CPU_Set_Flag_N() { u8_Set_Bit(&GB_CPU_reg_AF[1],6); }
void GB_CPU_Set_Flag_H() { u8_Set_Bit(&GB_CPU_reg_AF[1],5); }
void GB_CPU_Set_Flag_C() { u8_Set_Bit(&GB_CPU_reg_AF[1],4); }

void GB_CPU_Reset_Flag_Z() { u8_Reset_Bit(&GB_CPU_reg_AF[1],7); }
void GB_CPU_Reset_Flag_N() { u8_Reset_Bit(&GB_CPU_reg_AF[1],6); }
void GB_CPU_Reset_Flag_H() { u8_Reset_Bit(&GB_CPU_reg_AF[1],5); }
void GB_CPU_Reset_Flag_C() { u8_Reset_Bit(&GB_CPU_reg_AF[1],4); }

void GB_CPU_Set_All_flags();
void GB_CPU_Reset_All_Flags();

u8 GB_CPU_Get_Flag_H()			{ return (GB_CPU_reg_AF[1] & 0x20);	}
u8 GB_CPU_Get_Flag_N()			{ return (GB_CPU_reg_AF[1] & 0x40);	}
u8 GB_CPU_Get_Flag_C()			{ return (GB_CPU_reg_AF[1] & 0x10); }
u8 GB_CPU_Get_Flag_Z()			{ return (GB_CPU_reg_AF[1] & 0x80);	}


// Process command
u8 GB_CPU_Process(u8 opcode);

// Increment Program Counter by "offset" bytes
void GB_Increment_PC(u16 offset);

// Get immediate values from main memory at wherer the program Counter points
u8 GB_Get_u8_PC();		// get immediate b8its value
u16 GB_Get_u16_PC();	// get immediate 16 bits value






/*
Game Boy CPU Instruction Set !

Thanks to this guy, it's all pretty much there:
http://nocash.emubase.de/pandocs.htm#cpuinstructionset
*/

// 8bit-Load Commands
void GB_CPU_LD_8(u8* loadTo, u8* from);
void GB_CPU_LDI_8(u8* reg1, u8* reg2);
void GB_CPU_LDD_8(u8* reg1, u8* reg2);

// 16bit-Load Commands
void GB_CPU_LD_16(u16* loadTo, u16* from);
void GB_CPU_PUSH_16(u16* reg);
void GB_CPU_POP_16(u16* reg);

// 8bit-Arithmetic
void GB_CPU_ADD_8(u8* reg);
void GB_CPU_ADC_8(u8* reg);
void GB_CPU_SUB_8(u8* reg);
void GB_CPU_SBC_8(u8* reg);
void GB_CPU_INC_8(u8* reg);
void GB_CPU_DEC_8(u8* reg);
void GB_CPU_DAA_8();

// 8bit-Logical
void GB_CPU_AND(u8* reg);
void GB_CPU_OR(u8* reg);
void GB_CPU_XOR(u8* reg);
void GB_CPU_CP(u8* reg);
void GB_CPU_CPL();

// 16bit-Arithmetic and Logic
void GB_CPU_ADD_16(u16* reg);
void GB_CPU_INC_16(u16* reg);
void GB_CPU_DEC_16(u16* reg);
void GB_CPU_ADD_TO_SP(u8* reg);
void GB_CPU_LD_OFFSET(u8* reg);

// Rotate and shift bit operations
void GB_CPU_RLC(u8* reg);
void GB_CPU_RRC(u8* reg);
void GB_CPU_RL(u8* reg);
void GB_CPU_RR(u8* reg);
void GB_CPU_RLC_Accu();
void GB_CPU_RRC_Accu();
void GB_CPU_RL_Accu();
void GB_CPU_RR_Accu();
void GB_CPU_SLA(u8* reg);
void GB_CPU_SWAP(u8* reg);
void GB_CPU_SRA(u8* reg);
void GB_CPU_SRL(u8* reg);

// Singlebit Operation Commands
void GB_CPU_BIT(u8* reg1,u8* reg2);
void GB_CPU_SET(u8* reg1,u8* reg2);
void GB_CPU_RES(u8* reg1,u8* reg2);

// CPU-Controlcommands
void GB_CPU_CCF();
void GB_CPU_SCF();
void GB_CPU_NOP();
void GB_CPU_Halt();
void GB_CPU_Stop();
void GB_CPU_DI();
void GB_CPU_EI();

/*
   CPU Control flow operations
 
 boolean_flag convention:
 0x01:c | 0x02:nc | 0x04:z | 0x08:nz
*/

u8 Helper_Flag_Test(u8 boolean_flag);
void GB_CPU_Jump(u16* reg);
void GB_CPU_Cond_Jump(u16* reg,u8 boolean_flag);
void GB_CPU_Call(u16* reg);
void GB_CPU_Cond_Call(u16* reg,u8 boolean_flag);
void GB_CPU_Return();
void GB_CPU_Cond_Return(u8 boolean_flag);






/*
Game Boy actual machine Opcodes: 

Defines opcode for the CPU, Please refer to the Gameboy CPU documentation to
find the table of instructions related to those opcodes
*/

void GB_CPU_OPCODE_0x00(void);
void GB_CPU_OPCODE_0x01(void);
void GB_CPU_OPCODE_0x02(void);
void GB_CPU_OPCODE_0x03(void);
void GB_CPU_OPCODE_0x04(void);
void GB_CPU_OPCODE_0x05(void);
void GB_CPU_OPCODE_0x06(void);
void GB_CPU_OPCODE_0x07(void);
void GB_CPU_OPCODE_0x08(void);
void GB_CPU_OPCODE_0x09(void);
void GB_CPU_OPCODE_0x0A(void);
void GB_CPU_OPCODE_0x0B(void);
void GB_CPU_OPCODE_0x0C(void);
void GB_CPU_OPCODE_0x0D(void);
void GB_CPU_OPCODE_0x0E(void);
void GB_CPU_OPCODE_0x0F(void);

void GB_CPU_OPCODE_0x10(void);
void GB_CPU_OPCODE_0x11(void);
void GB_CPU_OPCODE_0x12(void);
void GB_CPU_OPCODE_0x13(void);
void GB_CPU_OPCODE_0x14(void);
void GB_CPU_OPCODE_0x15(void);
void GB_CPU_OPCODE_0x16(void);
void GB_CPU_OPCODE_0x17(void);
void GB_CPU_OPCODE_0x18(void);
void GB_CPU_OPCODE_0x19(void);
void GB_CPU_OPCODE_0x1A(void);
void GB_CPU_OPCODE_0x1B(void);
void GB_CPU_OPCODE_0x1C(void);
void GB_CPU_OPCODE_0x1D(void);
void GB_CPU_OPCODE_0x1E(void);
void GB_CPU_OPCODE_0x1F(void);

void GB_CPU_OPCODE_0x20(void);
void GB_CPU_OPCODE_0x21(void);
void GB_CPU_OPCODE_0x22(void);
void GB_CPU_OPCODE_0x23(void);
void GB_CPU_OPCODE_0x24(void);
void GB_CPU_OPCODE_0x25(void);
void GB_CPU_OPCODE_0x26(void);
void GB_CPU_OPCODE_0x27(void);
void GB_CPU_OPCODE_0x28(void);
void GB_CPU_OPCODE_0x29(void);
void GB_CPU_OPCODE_0x2A(void);
void GB_CPU_OPCODE_0x2B(void);
void GB_CPU_OPCODE_0x2C(void);
void GB_CPU_OPCODE_0x2D(void);
void GB_CPU_OPCODE_0x2E(void);
void GB_CPU_OPCODE_0x2F(void);

void GB_CPU_OPCODE_0x30(void);
void GB_CPU_OPCODE_0x31(void);
void GB_CPU_OPCODE_0x32(void);
void GB_CPU_OPCODE_0x33(void);
void GB_CPU_OPCODE_0x34(void);
void GB_CPU_OPCODE_0x35(void);
void GB_CPU_OPCODE_0x36(void);
void GB_CPU_OPCODE_0x37(void);
void GB_CPU_OPCODE_0x38(void);
void GB_CPU_OPCODE_0x39(void);
void GB_CPU_OPCODE_0x3A(void);
void GB_CPU_OPCODE_0x3B(void);
void GB_CPU_OPCODE_0x3C(void);
void GB_CPU_OPCODE_0x3D(void);
void GB_CPU_OPCODE_0x3E(void);
void GB_CPU_OPCODE_0x3F(void);

void GB_CPU_OPCODE_0x40(void);
void GB_CPU_OPCODE_0x41(void);
void GB_CPU_OPCODE_0x42(void);
void GB_CPU_OPCODE_0x43(void);
void GB_CPU_OPCODE_0x44(void);
void GB_CPU_OPCODE_0x45(void);
void GB_CPU_OPCODE_0x46(void);
void GB_CPU_OPCODE_0x47(void);
void GB_CPU_OPCODE_0x48(void);
void GB_CPU_OPCODE_0x49(void);
void GB_CPU_OPCODE_0x4A(void);
void GB_CPU_OPCODE_0x4B(void);
void GB_CPU_OPCODE_0x4C(void);
void GB_CPU_OPCODE_0x4D(void);
void GB_CPU_OPCODE_0x4E(void);
void GB_CPU_OPCODE_0x4F(void);

void GB_CPU_OPCODE_0x50(void);
void GB_CPU_OPCODE_0x51(void);
void GB_CPU_OPCODE_0x52(void);
void GB_CPU_OPCODE_0x53(void);
void GB_CPU_OPCODE_0x54(void);
void GB_CPU_OPCODE_0x55(void);
void GB_CPU_OPCODE_0x56(void);
void GB_CPU_OPCODE_0x57(void);
void GB_CPU_OPCODE_0x58(void);
void GB_CPU_OPCODE_0x59(void);
void GB_CPU_OPCODE_0x5A(void);
void GB_CPU_OPCODE_0x5B(void);
void GB_CPU_OPCODE_0x5C(void);
void GB_CPU_OPCODE_0x5D(void);
void GB_CPU_OPCODE_0x5E(void);
void GB_CPU_OPCODE_0x5F(void);

void GB_CPU_OPCODE_0x60(void);
void GB_CPU_OPCODE_0x61(void);
void GB_CPU_OPCODE_0x62(void);
void GB_CPU_OPCODE_0x63(void);
void GB_CPU_OPCODE_0x64(void);
void GB_CPU_OPCODE_0x65(void);
void GB_CPU_OPCODE_0x66(void);
void GB_CPU_OPCODE_0x67(void);
void GB_CPU_OPCODE_0x68(void);
void GB_CPU_OPCODE_0x69(void);
void GB_CPU_OPCODE_0x6A(void);
void GB_CPU_OPCODE_0x6B(void);
void GB_CPU_OPCODE_0x6C(void);
void GB_CPU_OPCODE_0x6D(void);
void GB_CPU_OPCODE_0x6E(void);
void GB_CPU_OPCODE_0x6F(void);

void GB_CPU_OPCODE_0x70(void);
void GB_CPU_OPCODE_0x71(void);
void GB_CPU_OPCODE_0x72(void);
void GB_CPU_OPCODE_0x73(void);
void GB_CPU_OPCODE_0x74(void);
void GB_CPU_OPCODE_0x75(void);
void GB_CPU_OPCODE_0x76(void);
void GB_CPU_OPCODE_0x77(void);
void GB_CPU_OPCODE_0x78(void);
void GB_CPU_OPCODE_0x79(void);
void GB_CPU_OPCODE_0x7A(void);
void GB_CPU_OPCODE_0x7B(void);
void GB_CPU_OPCODE_0x7C(void);
void GB_CPU_OPCODE_0x7D(void);
void GB_CPU_OPCODE_0x7E(void);
void GB_CPU_OPCODE_0x7F(void);

void GB_CPU_OPCODE_0x80(void);
void GB_CPU_OPCODE_0x81(void);
void GB_CPU_OPCODE_0x82(void);
void GB_CPU_OPCODE_0x83(void);
void GB_CPU_OPCODE_0x84(void);
void GB_CPU_OPCODE_0x85(void);
void GB_CPU_OPCODE_0x86(void);
void GB_CPU_OPCODE_0x87(void);
void GB_CPU_OPCODE_0x88(void);
void GB_CPU_OPCODE_0x89(void);
void GB_CPU_OPCODE_0x8A(void);
void GB_CPU_OPCODE_0x8B(void);
void GB_CPU_OPCODE_0x8C(void);
void GB_CPU_OPCODE_0x8D(void);
void GB_CPU_OPCODE_0x8E(void);
void GB_CPU_OPCODE_0x8F(void);

void GB_CPU_OPCODE_0x90(void);
void GB_CPU_OPCODE_0x91(void);
void GB_CPU_OPCODE_0x92(void);
void GB_CPU_OPCODE_0x93(void);
void GB_CPU_OPCODE_0x94(void);
void GB_CPU_OPCODE_0x95(void);
void GB_CPU_OPCODE_0x96(void);
void GB_CPU_OPCODE_0x97(void);
void GB_CPU_OPCODE_0x98(void);
void GB_CPU_OPCODE_0x99(void);
void GB_CPU_OPCODE_0x9A(void);
void GB_CPU_OPCODE_0x9B(void);
void GB_CPU_OPCODE_0x9C(void);
void GB_CPU_OPCODE_0x9D(void);
void GB_CPU_OPCODE_0x9E(void);
void GB_CPU_OPCODE_0x9F(void);

void GB_CPU_OPCODE_0xA0(void);
void GB_CPU_OPCODE_0xA1(void);
void GB_CPU_OPCODE_0xA2(void);
void GB_CPU_OPCODE_0xA3(void);
void GB_CPU_OPCODE_0xA4(void);
void GB_CPU_OPCODE_0xA5(void);
void GB_CPU_OPCODE_0xA6(void);
void GB_CPU_OPCODE_0xA7(void);
void GB_CPU_OPCODE_0xA8(void);
void GB_CPU_OPCODE_0xA9(void);
void GB_CPU_OPCODE_0xAA(void);
void GB_CPU_OPCODE_0xAB(void);
void GB_CPU_OPCODE_0xAC(void);
void GB_CPU_OPCODE_0xAD(void);
void GB_CPU_OPCODE_0xAE(void);
void GB_CPU_OPCODE_0xAF(void);

void GB_CPU_OPCODE_0xB0(void);
void GB_CPU_OPCODE_0xB1(void);
void GB_CPU_OPCODE_0xB2(void);
void GB_CPU_OPCODE_0xB3(void);
void GB_CPU_OPCODE_0xB4(void);
void GB_CPU_OPCODE_0xB5(void);
void GB_CPU_OPCODE_0xB6(void);
void GB_CPU_OPCODE_0xB7(void);
void GB_CPU_OPCODE_0xB8(void);
void GB_CPU_OPCODE_0xB9(void);
void GB_CPU_OPCODE_0xBA(void);
void GB_CPU_OPCODE_0xBB(void);
void GB_CPU_OPCODE_0xBC(void);
void GB_CPU_OPCODE_0xBD(void);
void GB_CPU_OPCODE_0xBE(void);
void GB_CPU_OPCODE_0xBF(void);

void GB_CPU_OPCODE_0xC0(void);
void GB_CPU_OPCODE_0xC1(void);
void GB_CPU_OPCODE_0xC2(void);
void GB_CPU_OPCODE_0xC3(void);
void GB_CPU_OPCODE_0xC4(void);
void GB_CPU_OPCODE_0xC5(void);
void GB_CPU_OPCODE_0xC6(void);
void GB_CPU_OPCODE_0xC7(void);
void GB_CPU_OPCODE_0xC8(void);
void GB_CPU_OPCODE_0xC9(void);
void GB_CPU_OPCODE_0xCA(void);
void GB_CPU_OPCODE_0xCB(void);
void GB_CPU_OPCODE_0xCC(void);
void GB_CPU_OPCODE_0xCD(void);
void GB_CPU_OPCODE_0xCE(void);
void GB_CPU_OPCODE_0xCF(void);

void GB_CPU_OPCODE_0xD0(void);
void GB_CPU_OPCODE_0xD1(void);
void GB_CPU_OPCODE_0xD2(void);
void GB_CPU_OPCODE_0xD3(void);
void GB_CPU_OPCODE_0xD4(void);
void GB_CPU_OPCODE_0xD5(void);
void GB_CPU_OPCODE_0xD6(void);
void GB_CPU_OPCODE_0xD7(void);
void GB_CPU_OPCODE_0xD8(void);
void GB_CPU_OPCODE_0xD9(void);
void GB_CPU_OPCODE_0xDA(void);
void GB_CPU_OPCODE_0xDB(void);
void GB_CPU_OPCODE_0xDC(void);
void GB_CPU_OPCODE_0xDD(void);
void GB_CPU_OPCODE_0xDE(void);
void GB_CPU_OPCODE_0xDF(void);

void GB_CPU_OPCODE_0xE0(void);
void GB_CPU_OPCODE_0xE1(void);
void GB_CPU_OPCODE_0xE2(void);
void GB_CPU_OPCODE_0xE3(void);
void GB_CPU_OPCODE_0xE4(void);
void GB_CPU_OPCODE_0xE5(void);
void GB_CPU_OPCODE_0xE6(void);
void GB_CPU_OPCODE_0xE7(void);
void GB_CPU_OPCODE_0xE8(void);
void GB_CPU_OPCODE_0xE9(void);
void GB_CPU_OPCODE_0xEA(void);
void GB_CPU_OPCODE_0xEB(void);
void GB_CPU_OPCODE_0xEC(void);
void GB_CPU_OPCODE_0xED(void);
void GB_CPU_OPCODE_0xEE(void);
void GB_CPU_OPCODE_0xEF(void);

void GB_CPU_OPCODE_0xF0(void);
void GB_CPU_OPCODE_0xF1(void);
void GB_CPU_OPCODE_0xF2(void);
void GB_CPU_OPCODE_0xF3(void);
void GB_CPU_OPCODE_0xF4(void);
void GB_CPU_OPCODE_0xF5(void);
void GB_CPU_OPCODE_0xF6(void);
void GB_CPU_OPCODE_0xF7(void);
void GB_CPU_OPCODE_0xF8(void);
void GB_CPU_OPCODE_0xF9(void);
void GB_CPU_OPCODE_0xFA(void);
void GB_CPU_OPCODE_0xFB(void);
void GB_CPU_OPCODE_0xFC(void);
void GB_CPU_OPCODE_0xFD(void);
void GB_CPU_OPCODE_0xFE(void);
void GB_CPU_OPCODE_0xFF(void);


// Opcode function type
typedef void (*Opcode_Func_CallBack) (void);

// Opcode Function calls table 
// One calls instruction 0xXY using functions[0xXY]

Opcode_Func_CallBack opcode_function_callbacks[] = 
{
	&GB_CPU_OPCODE_0x00,
	&GB_CPU_OPCODE_0x01,
	&GB_CPU_OPCODE_0x02,
	&GB_CPU_OPCODE_0x03,
	&GB_CPU_OPCODE_0x04,
	&GB_CPU_OPCODE_0x05,
	&GB_CPU_OPCODE_0x06,
	&GB_CPU_OPCODE_0x07,
	&GB_CPU_OPCODE_0x08,
	&GB_CPU_OPCODE_0x09,
	&GB_CPU_OPCODE_0x0A,
	&GB_CPU_OPCODE_0x0B,
	&GB_CPU_OPCODE_0x0C,
	&GB_CPU_OPCODE_0x0D,
	&GB_CPU_OPCODE_0x0E,
	&GB_CPU_OPCODE_0x0F,

	&GB_CPU_OPCODE_0x10,
	&GB_CPU_OPCODE_0x11,
	&GB_CPU_OPCODE_0x12,
	&GB_CPU_OPCODE_0x13,
	&GB_CPU_OPCODE_0x14,
	&GB_CPU_OPCODE_0x15,
	&GB_CPU_OPCODE_0x16,
	&GB_CPU_OPCODE_0x17,
	&GB_CPU_OPCODE_0x18,
	&GB_CPU_OPCODE_0x19,
	&GB_CPU_OPCODE_0x1A,
	&GB_CPU_OPCODE_0x1B,
	&GB_CPU_OPCODE_0x1C,
	&GB_CPU_OPCODE_0x1D,
	&GB_CPU_OPCODE_0x1E,
	&GB_CPU_OPCODE_0x1F,

	&GB_CPU_OPCODE_0x20,
	&GB_CPU_OPCODE_0x21,
	&GB_CPU_OPCODE_0x22,
	&GB_CPU_OPCODE_0x23,
	&GB_CPU_OPCODE_0x24,
	&GB_CPU_OPCODE_0x25,
	&GB_CPU_OPCODE_0x26,
	&GB_CPU_OPCODE_0x27,
	&GB_CPU_OPCODE_0x28,
	&GB_CPU_OPCODE_0x29,
	&GB_CPU_OPCODE_0x2A,
	&GB_CPU_OPCODE_0x2B,
	&GB_CPU_OPCODE_0x2C,
	&GB_CPU_OPCODE_0x2D,
	&GB_CPU_OPCODE_0x2E,
	&GB_CPU_OPCODE_0x2F,

	&GB_CPU_OPCODE_0x30,
	&GB_CPU_OPCODE_0x31,
	&GB_CPU_OPCODE_0x32,
	&GB_CPU_OPCODE_0x33,
	&GB_CPU_OPCODE_0x34,
	&GB_CPU_OPCODE_0x35,
	&GB_CPU_OPCODE_0x36,
	&GB_CPU_OPCODE_0x37,
	&GB_CPU_OPCODE_0x38,
	&GB_CPU_OPCODE_0x39,
	&GB_CPU_OPCODE_0x3A,
	&GB_CPU_OPCODE_0x3B,
	&GB_CPU_OPCODE_0x3C,
	&GB_CPU_OPCODE_0x3D,
	&GB_CPU_OPCODE_0x3E,
	&GB_CPU_OPCODE_0x3F,

	&GB_CPU_OPCODE_0x40,
	&GB_CPU_OPCODE_0x41,
	&GB_CPU_OPCODE_0x42,
	&GB_CPU_OPCODE_0x43,
	&GB_CPU_OPCODE_0x44,
	&GB_CPU_OPCODE_0x45,
	&GB_CPU_OPCODE_0x46,
	&GB_CPU_OPCODE_0x47,
	&GB_CPU_OPCODE_0x48,
	&GB_CPU_OPCODE_0x49,
	&GB_CPU_OPCODE_0x4A,
	&GB_CPU_OPCODE_0x4B,
	&GB_CPU_OPCODE_0x4C,
	&GB_CPU_OPCODE_0x4D,
	&GB_CPU_OPCODE_0x4E,
	&GB_CPU_OPCODE_0x4F,

	&GB_CPU_OPCODE_0x50,
	&GB_CPU_OPCODE_0x51,
	&GB_CPU_OPCODE_0x52,
	&GB_CPU_OPCODE_0x53,
	&GB_CPU_OPCODE_0x54,
	&GB_CPU_OPCODE_0x55,
	&GB_CPU_OPCODE_0x56,
	&GB_CPU_OPCODE_0x57,
	&GB_CPU_OPCODE_0x58,
	&GB_CPU_OPCODE_0x59,
	&GB_CPU_OPCODE_0x5A,
	&GB_CPU_OPCODE_0x5B,
	&GB_CPU_OPCODE_0x5C,
	&GB_CPU_OPCODE_0x5D,
	&GB_CPU_OPCODE_0x5E,
	&GB_CPU_OPCODE_0x5F,

	&GB_CPU_OPCODE_0x60,
	&GB_CPU_OPCODE_0x61,
	&GB_CPU_OPCODE_0x62,
	&GB_CPU_OPCODE_0x63,
	&GB_CPU_OPCODE_0x64,
	&GB_CPU_OPCODE_0x65,
	&GB_CPU_OPCODE_0x66,
	&GB_CPU_OPCODE_0x67,
	&GB_CPU_OPCODE_0x68,
	&GB_CPU_OPCODE_0x69,
	&GB_CPU_OPCODE_0x6A,
	&GB_CPU_OPCODE_0x6B,
	&GB_CPU_OPCODE_0x6C,
	&GB_CPU_OPCODE_0x6D,
	&GB_CPU_OPCODE_0x6E,
	&GB_CPU_OPCODE_0x6F,

	&GB_CPU_OPCODE_0x70,
	&GB_CPU_OPCODE_0x71,
	&GB_CPU_OPCODE_0x72,
	&GB_CPU_OPCODE_0x73,
	&GB_CPU_OPCODE_0x74,
	&GB_CPU_OPCODE_0x75,
	&GB_CPU_OPCODE_0x76,
	&GB_CPU_OPCODE_0x77,
	&GB_CPU_OPCODE_0x78,
	&GB_CPU_OPCODE_0x79,
	&GB_CPU_OPCODE_0x7A,
	&GB_CPU_OPCODE_0x7B,
	&GB_CPU_OPCODE_0x7C,
	&GB_CPU_OPCODE_0x7D,
	&GB_CPU_OPCODE_0x7E,
	&GB_CPU_OPCODE_0x7F,

	&GB_CPU_OPCODE_0x80,
	&GB_CPU_OPCODE_0x81,
	&GB_CPU_OPCODE_0x82,
	&GB_CPU_OPCODE_0x83,
	&GB_CPU_OPCODE_0x84,
	&GB_CPU_OPCODE_0x85,
	&GB_CPU_OPCODE_0x86,
	&GB_CPU_OPCODE_0x87,
	&GB_CPU_OPCODE_0x88,
	&GB_CPU_OPCODE_0x89,
	&GB_CPU_OPCODE_0x8A,
	&GB_CPU_OPCODE_0x8B,
	&GB_CPU_OPCODE_0x8C,
	&GB_CPU_OPCODE_0x8D,
	&GB_CPU_OPCODE_0x8E,
	&GB_CPU_OPCODE_0x8F,

	&GB_CPU_OPCODE_0x90,
	&GB_CPU_OPCODE_0x91,
	&GB_CPU_OPCODE_0x92,
	&GB_CPU_OPCODE_0x93,
	&GB_CPU_OPCODE_0x94,
	&GB_CPU_OPCODE_0x95,
	&GB_CPU_OPCODE_0x96,
	&GB_CPU_OPCODE_0x97,
	&GB_CPU_OPCODE_0x98,
	&GB_CPU_OPCODE_0x99,
	&GB_CPU_OPCODE_0x9A,
	&GB_CPU_OPCODE_0x9B,
	&GB_CPU_OPCODE_0x9C,
	&GB_CPU_OPCODE_0x9D,
	&GB_CPU_OPCODE_0x9E,
	&GB_CPU_OPCODE_0x9F,

	&GB_CPU_OPCODE_0xA0,
	&GB_CPU_OPCODE_0xA1,
	&GB_CPU_OPCODE_0xA2,
	&GB_CPU_OPCODE_0xA3,
	&GB_CPU_OPCODE_0xA4,
	&GB_CPU_OPCODE_0xA5,
	&GB_CPU_OPCODE_0xA6,
	&GB_CPU_OPCODE_0xA7,
	&GB_CPU_OPCODE_0xA8,
	&GB_CPU_OPCODE_0xA9,
	&GB_CPU_OPCODE_0xAA,
	&GB_CPU_OPCODE_0xAB,
	&GB_CPU_OPCODE_0xAC,
	&GB_CPU_OPCODE_0xAD,
	&GB_CPU_OPCODE_0xAE,
	&GB_CPU_OPCODE_0xAF,

	&GB_CPU_OPCODE_0xB0,
	&GB_CPU_OPCODE_0xB1,
	&GB_CPU_OPCODE_0xB2,
	&GB_CPU_OPCODE_0xB3,
	&GB_CPU_OPCODE_0xB4,
	&GB_CPU_OPCODE_0xB5,
	&GB_CPU_OPCODE_0xB6,
	&GB_CPU_OPCODE_0xB7,
	&GB_CPU_OPCODE_0xB8,
	&GB_CPU_OPCODE_0xB9,
	&GB_CPU_OPCODE_0xBA,
	&GB_CPU_OPCODE_0xBB,
	&GB_CPU_OPCODE_0xBC,
	&GB_CPU_OPCODE_0xBD,
	&GB_CPU_OPCODE_0xBE,
	&GB_CPU_OPCODE_0xBF,

	&GB_CPU_OPCODE_0xC0,
	&GB_CPU_OPCODE_0xC1,
	&GB_CPU_OPCODE_0xC2,
	&GB_CPU_OPCODE_0xC3,
	&GB_CPU_OPCODE_0xC4,
	&GB_CPU_OPCODE_0xC5,
	&GB_CPU_OPCODE_0xC6,
	&GB_CPU_OPCODE_0xC7,
	&GB_CPU_OPCODE_0xC8,
	&GB_CPU_OPCODE_0xC9,
	&GB_CPU_OPCODE_0xCA,
	&GB_CPU_OPCODE_0xCB,
	&GB_CPU_OPCODE_0xCC,
	&GB_CPU_OPCODE_0xCD,
	&GB_CPU_OPCODE_0xCE,
	&GB_CPU_OPCODE_0xCF,

	&GB_CPU_OPCODE_0xD0,
	&GB_CPU_OPCODE_0xD1,
	&GB_CPU_OPCODE_0xD2,
	&GB_CPU_OPCODE_0xD3,
	&GB_CPU_OPCODE_0xD4,
	&GB_CPU_OPCODE_0xD5,
	&GB_CPU_OPCODE_0xD6,
	&GB_CPU_OPCODE_0xD7,
	&GB_CPU_OPCODE_0xD8,
	&GB_CPU_OPCODE_0xD9,
	&GB_CPU_OPCODE_0xDA,
	&GB_CPU_OPCODE_0xDB,
	&GB_CPU_OPCODE_0xDC,
	&GB_CPU_OPCODE_0xDD,
	&GB_CPU_OPCODE_0xDE,
	&GB_CPU_OPCODE_0xDF,

	&GB_CPU_OPCODE_0xE0,
	&GB_CPU_OPCODE_0xE1,
	&GB_CPU_OPCODE_0xE2,
	&GB_CPU_OPCODE_0xE3,
	&GB_CPU_OPCODE_0xE4,
	&GB_CPU_OPCODE_0xE5,
	&GB_CPU_OPCODE_0xE6,
	&GB_CPU_OPCODE_0xE7,
	&GB_CPU_OPCODE_0xE8,
	&GB_CPU_OPCODE_0xE9,
	&GB_CPU_OPCODE_0xEA,
	&GB_CPU_OPCODE_0xEB,
	&GB_CPU_OPCODE_0xEC,
	&GB_CPU_OPCODE_0xED,
	&GB_CPU_OPCODE_0xEE,
	&GB_CPU_OPCODE_0xEF,

	&GB_CPU_OPCODE_0xF0,
	&GB_CPU_OPCODE_0xF1,
	&GB_CPU_OPCODE_0xF2,
	&GB_CPU_OPCODE_0xF3,
	&GB_CPU_OPCODE_0xF4,
	&GB_CPU_OPCODE_0xF5,
	&GB_CPU_OPCODE_0xF6,
	&GB_CPU_OPCODE_0xF7,
	&GB_CPU_OPCODE_0xF8,
	&GB_CPU_OPCODE_0xF9,
	&GB_CPU_OPCODE_0xFA,
	&GB_CPU_OPCODE_0xFB,
	&GB_CPU_OPCODE_0xFC,
	&GB_CPU_OPCODE_0xFD,
	&GB_CPU_OPCODE_0xFE,
	&GB_CPU_OPCODE_0xFF
};
