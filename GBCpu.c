#include "GBCpu.h"

void u8_Set_Bit(u8* wordToSet, u8 bitNumber)
{
	u8 bitmask = 0x01;
	bitmask = bitmask << bitNumber;

	*wordToSet = (*wordToSet | bitmask);
}


void u16_Set_Bit(u16* wordToSet, u8 bitNumber)
{
	u16 bitmask = 0x01;
	bitmask = bitmask << bitNumber;

	*wordToSet = (*wordToSet | bitmask);
}

void u8_Reset_Bit(u8* wordToReset, u8 bitNumber)
{
	u8 bitmask = 0x01;
	bitmask = bitmask << bitNumber;

	*wordToReset = (*wordToReset & ~bitmask);
}

void u16_Reset_Bit(u16* wordToReset, u8 bitNumber)
{
	u16 bitmask = 0x01;
	bitmask = bitmask << bitNumber;

	*wordToReset = (*wordToReset & ~bitmask);
}

void GB_CPU_Set_All_Flags()
{
	GB_CPU_Set_Flag_Z();
	GB_CPU_Set_Flag_N();
	GB_CPU_Set_Flag_H();
	GB_CPU_Set_Flag_C();
}

void GB_CPU_Reset_All_Flags()
{
	GB_CPU_Reset_Flag_Z();
	GB_CPU_Reset_Flag_N();
	GB_CPU_Reset_Flag_H();
	GB_CPU_Reset_Flag_C();
}


void GB_Increment_PC(u16 offset)
{
	if( ((u32) GB_CPU_reg_PC + (u32) offset) < 0x0000FFFF)
	{
		GB_CPU_reg_PC = GB_CPU_reg_PC + offset;
	}
	else
	{
		// Code a log system already !
		// printf("Warning CPU: Program Counter Overflow");
	}
}

u8 GB_Get_u8_PC()
{
    extern u8* GB_main_memory;
    
    return (u8) *(GB_main_memory + GB_CPU_reg_PC);
}

u16 GB_Get_u16_PC()
{
    extern u8* GB_main_memory;
   
    return (u16) *(GB_main_memory + GB_CPU_reg_PC);
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
void GB_CPU_LD_16(u16* from, u16* loadTo)
{
	*from = *loadTo;
}

void GB_CPU_PUSH_16(u16* reg)
{
	*((u16*) (GB_main_memory + GB_CPU_reg_SP)) = *reg;
	GB_CPU_reg_SP = GB_CPU_reg_SP - 2;
}

void GB_CPU_POP_16(u16* reg)
{
	*reg = *((u16*) (GB_main_memory + GB_CPU_reg_SP));
	GB_CPU_reg_SP = GB_CPU_reg_SP + 2;
}

void GB_CPU_ADD_8(u8* reg)
{
	u16 overflowTest, carry;
	u8 result;

	// Reseting all flags before any operation, also sets N flag to 0
	GB_CPU_Reset_All_Flags();

	overflowTest = (u16) GB_CPU_reg_AF[0] + (u16) *reg;

	carry = (u16) GB_CPU_reg_AF[0] ^ (u16) *reg ^ overflowTest;

	// Half carry test
	if( (carry & 0x0010) != 0x0000)
	{
		GB_CPU_Set_Flag_H();
	}
	if( (carry & 0x0100) != 0x0000)
	{
		GB_CPU_Set_Flag_C();
	}

	result = GB_CPU_reg_AF[0] + *reg;

	GB_CPU_reg_AF[0] = result;

	if(result == 0x00)
	{
		GB_CPU_Set_Flag_Z();
	}
}
void GB_CPU_ADC_8(u8* reg)
{
	if( (GB_CPU_reg_AF[1] & 0x10) != 0)
	{
		u16 overflowTest, carry;

		u8 result;

		// Reseting all flags before any operation, also sets N flag to 0
		GB_CPU_Reset_All_Flags();

		overflowTest = (u16) GB_CPU_reg_AF[0] + (u16) *reg + 0x0001;
		carry = (u16) GB_CPU_reg_AF[0] ^ (u16) *reg ^ overflowTest;

		// Half carry test
		if( (carry & 0x0010) != 0x0000 )
		{
			GB_CPU_Set_Flag_H();
		}
		if( (carry & 0x0100) != 0x0000 )
		{
			GB_CPU_Set_Flag_C();
		}

		result = GB_CPU_reg_AF[0] + *reg + 0x01;

		GB_CPU_reg_AF[0] = result;

		if(result == 0x00)
		{
			GB_CPU_Set_Flag_Z();
		}
	}
	else
	{
		GB_CPU_ADD_8(reg);
	}
}

void GB_CPU_SUB_8(u8* reg)
{
	// Take reg2's value's two's complement
	u8 negInt = ~(*reg) + 0x01;
	
	GB_CPU_ADD_8(&negInt);

	GB_CPU_Set_Flag_N();
}

void GB_CPU_SBC_8(u8* reg)
{
	if( (GB_CPU_reg_AF[1] & 0x10) != 0)
	{
		u8 negInt = ~(*reg) + 0x02;
	
		GB_CPU_ADD_8(&negInt);

		GB_CPU_Set_Flag_N();
	}
	else
	{
		GB_CPU_SUB_8(reg);
	}

}
void GB_CPU_INC_8(u8* reg)
{
	u8 result, carry;

	GB_CPU_Reset_All_Flags();

	result = *reg  +  0x01;

	carry = *reg ^ 0x01 ^ result;
	
	// Half carry test
	if( (carry & 0x10) != 0x00)
	{
		GB_CPU_Set_Flag_H();
	}

	*reg = result;

	if(result == 0x00)
	{
		GB_CPU_Set_Flag_Z();
	}
}
void GB_CPU_DEC_8(u8* reg)
{
	u8 result, carry;

	GB_CPU_Reset_All_Flags();

	result = *reg  +  0xFF;
	
	carry = *reg ^ 0xFF ^ result;
	
	// Half carry test
	if( (carry & 0x10) != 0x00)
	{
		GB_CPU_Set_Flag_H();
	}

	*reg = result;

	if(result == 0x00)
	{
		GB_CPU_Set_Flag_Z();
	}
}


/*

DAA Decimal Adjust After Addition:

--------------------------------------------------------------------------------
|           | C Flag  | HEX value in | H Flag | HEX value in | Number  | C flag|
| Operation | Before  | upper digit  | Before | lower digit  | added   | After |
|           | DAA     | (bit 7-4)    | DAA    | (bit 3-0)    | to byte | DAA   |
|------------------------------------------------------------------------------|
|           |    0    |     0-9      |   0    |     0-9      |   00    |   0   |
|   ADD     |    0    |     0-8      |   0    |     A-F      |   06    |   0   |
|           |    0    |     0-9      |   1    |     0-3      |   06    |   0   |
|   ADC     |    0    |     A-F      |   0    |     0-9      |   60    |   1   |
|           |    0    |     9-F      |   0    |     A-F      |   66    |   1   |
|   INC     |    0    |     A-F      |   1    |     0-3      |   66    |   1   |
|           |    1    |     0-2      |   0    |     0-9      |   60    |   1   |
|           |    1    |     0-2      |   0    |     A-F      |   66    |   1   |
|           |    1    |     0-3      |   1    |     0-3      |   66    |   1   |
|------------------------------------------------------------------------------|
|   SUB     |    0    |     0-9      |   0    |     0-9      |   00    |   0   |
|   SBC     |    0    |     0-8      |   1    |     6-F      |   FA    |   0   |
|   DEC     |    1    |     7-F      |   0    |     0-9      |   A0    |   1   |
|   NEG     |    1    |     6-F      |   1    |     6-F      |   9A    |   1   |
|------------------------------------------------------------------------------|
*/
void GB_CPU_DAA_8()
{
	
}

void GB_CPU_AND(u8* reg)
{
	GB_CPU_Reset_All_Flags();

	GB_CPU_reg_AF[0] = GB_CPU_reg_AF[0] & *reg;

	if(GB_CPU_reg_AF[0] == 0x00)
	{
		GB_CPU_Set_Flag_Z();
	}

	GB_CPU_Set_Flag_H();

}

void GB_CPU_OR(u8* reg)
{
	GB_CPU_Reset_All_Flags();

	GB_CPU_reg_AF[0] = GB_CPU_reg_AF[0] | *reg;

	if(GB_CPU_reg_AF[0] == 0x00)
	{
		GB_CPU_Set_Flag_Z();
	}
}

void GB_CPU_XOR(u8* reg)
{
	GB_CPU_Reset_All_Flags();

	GB_CPU_reg_AF[0] = GB_CPU_reg_AF[0] ^ *reg;

	if(GB_CPU_reg_AF[0] == 0x00)
	{
		GB_CPU_Set_Flag_Z();
	}
}