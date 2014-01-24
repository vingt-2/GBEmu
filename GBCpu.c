#include "GBCpu.h"

void u8_Set_Bit(u8* wordToSet, u8 bitNumber)
{
	u8 bitMask = 0x01;
	bitmask << bitNumber;

	*wordToSet = (*wordToSet | bitMask);
}


void u16_Set_Bit(u16* wordToSet, u8 bitNumber)
{
	u16 bitMask = 0x01;
	bitmask << bitNumber;

	*wordToSet = (*wordToSet | bitMask);
}

void u8_Set_Bit(u8* wordToReset, u8 bitNumber)
{
	u8 bitmask = 0x01;
	bitmask << bitNumber;

	*wordToReset = (*wordToReset & ~bitmask));
}

void u8_Set_Bit(u16* wordToReset, u8 bitNumber)
{
	u16 bitmask = 0x01;
	bitmask << bitNumber;

	*wordToReset = (*wordToReset & ~bitmask));
}

void GB_Increment_PC(u16 offset)
{
	if( ((u32) GB_CPU_PC + (u32) offset) < 0x0000FFFF)
	{
		GB_CPU_PC = GB_CPU_PC + offset;
	}
	else
	{
		printf("Warning CPU: Process Counter Overflow")
	}
}

u8 GB_Get_u8_PC()
{
    extern u8* GB_main_memory;
    
    return (u8) *(GB_main_memory + GB_CPU_PC);
}

u16 GB_Get_u16_PC()
{
    extern u16* GB_main_memory;
    
    return (u16) *(GB_main_memory + GB_CPU_PC);
}


/*
	GB CPU Instruction Set
*/

// 8bit-Load Commands
void GB_CPU_LD_8(u8* from, u8* loadTo)
{
	*loadTo = *from;
}

void GB_CPU_LDI_8(u8* from, u8* loadTo)
{
	*loadTo = *from;
	*from++;
}

void GB_CPU_LDD_8(u8* from, u8* loadTo)
{
	*loadTo = *from;
	*from--;
}

// 16bit-load Commands
void GB_CPU_LD_16(u16* from, u16* loadTo);
{
	*from = *loadTo;
}

void GB_CPU_PUSH_16(u16* reg)
{
	GB_CPU_reg_SP = GB_CPU_reg_SP - 2;
	*((u16*) (GB_main_memory + GB_CPU_reg_SP)) = *reg;
}

void GB_CPU_POP_16(u16* reg)
{
	*reg = *((u16*) (GB_main_memory + GB_CPU_reg_SP))
	GB_CPU_reg_SP = GB_CPU_reg_SP + 2;
}

void GB_CPU_ADD_8(u8* reg1, u8* reg2)
{

}
void GB_CPU_SUB_8(u8* reg1, u8* reg2)
{

}
void GB_CPU_SBC_8(u8* reg1, u8* reg2)
{

}
void GB_CPU_INC_8(u8* reg)
{

}
void GB_CPU_DEC_8(u8* reg)
{

}
void GB_CPU_DAA_8(u8* reg1, u8* reg2)
{
	
}