/*

    GBCpu: Here lies the Cpu interpreter. Command will be passed from memory
    
    To the Cpu interpreter to be translated into actual "portable" architecture dynamically.
 
    For info on supported commands see: z80 CPU documentation & 
        http://gbdev.gg8.se/files/docs/mirrors/pandocs.html#cpucomparisionwithz80

*/
 
#include "GBCore.h"

//  Registers
//  Each 16 bit Hi/Lo



u8 GB_CPU_reg_AF[2];  
/*
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

u8 GB_CPU_reg_BC[2];
u8 GB_CPU_reg_DE[2];
u8 GB_CPU_reg_HL[2];
u16 GB_CPU_reg_SP; 	// Stack Pointer
u16 GB_CPU_reg_PC; 	// Program Counter

extern u8* GB_main_memory;

void u8_Set_Bit(u8* wordToSet, u8 bitNumb);
void u16_Set_Bit(u16* wordToSet, u8 bitNumb);
void u8_Reset_Bit(u8* wordToReset, u8 bitNumb);
void u16_Reset_Bit(u16* wordToReset, u8 bitNumb);


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


// Process command
u8 GB_CPU_Process(u8 opcode);

// Increment Program Counter by "offset" bytes
void GB_Increment_PC(u16 offset);

// Get immediate values from main memory at wherer the program Counter points
u8 GB_Get_u8_PC();	// get immediate 8bits value
u16 GB_Get_u16_PC(); // get immediate 16 bits value

/*
	GB CPU Instruction Set
*/

// 8bit-Load Commands
void GB_CPU_LDI_8(u8* from,u8* loadTo);
void GB_CPU_LDI_8(u8* reg1, u8* reg2);
void GB_CPU_LDD_8(u8* reg1, u8* reg2);

// 16bit-Load Commands
void GB_CPU_LD_16(u16* from, u16* loadTo);
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
void GB_CPU_ADD_TO_SP(u16* reg);
void GB_CPU_LD_OFFSET_16(u16* reg);

// Rotate and shift bit operations

