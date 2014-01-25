#include "GBCpu.h"

void u8_Set_Bit(u8* wordToSet, u8 bitNumber)
{
	u8 bitmask = 0x01;
	bitmask << bitNumber;

	*wordToSet = (*wordToSet | bitmask);
}


void u16_Set_Bit(u16* wordToSet, u8 bitNumber)
{
	u16 bitmask = 0x01;
	bitmask << bitNumber;

	*wordToSet = (*wordToSet | bitmask);
}

void u8_Reset_Bit(u8* wordToReset, u8 bitNumber)
{
	u8 bitmask = 0x01;
	bitmask << bitNumber;

	*wordToReset = (*wordToReset & ~bitmask);
}

void u8_Reset_Bit(u16* wordToReset, u8 bitNumber)
{
	u16 bitmask = 0x01;
	bitmask << bitNumber;

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
		printf("Warning CPU: Process Counter Overflow");
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

void GB_CPU_ADD_8(u8* reg1, u8* reg2)
{
	// Reseting all flags before any operation, also sets N flag to 0
	GB_CPU_Reset_All_Flags();

	u16 overFlowTest = (u16) *reg1 + (u16) *reg2;

	u16 carry = (u16) *reg1 ^ (u16) *reg2 ^ overFlowTest;

	// Half carry test
	if(carry & 0x0010 != 0x0000)
	{
		GB_CPU_Set_Flag_H();
	}
	if(carry & 0x0100 != 0x0000)
	{
		GB_CPU_Set_Flag_C();
	}

	u8 result = *reg1 + *reg2;

	*reg1 = result;

	if(result == 0x00)
	{
		GB_CPU_Set_Flag_Z();
	}
}
void GB_CPU_ADC_8(u8* reg1, u8* reg2)
{
	if( GB_CPU_reg_AF[1] & 0x10 != 0)
	{
		// Reseting all flags before any operation, also sets N flag to 0
		GB_CPU_Reset_All_Flags();

		u16 overFlowTest = (u16) *reg1 + (u16) *reg2 + 0x0001;

		u16 carry = (u16) *reg1 ^ (u16) *reg2 ^ overFlowTest;

		// Half carry test
		if(carry & 0x0010 != 0x0000)
		{
			GB_CPU_Set_Flag_H();
		}
		if(carry & 0x0100 != 0x0000)
		{
			GB_CPU_Set_Flag_C();
		}

		u8 result = *reg1 + *reg2 + 0x01;

		*reg1 = result;

		if(result == 0x00)
		{
			GB_CPU_Set_Flag_Z();
		}
	}
	else
	{
		GB_CPU_ADD_8(reg1,reg2);
	}
}

void GB_CPU_SUB_8(u8* reg1, u8* reg2)
{
	// Take reg2's value's two's complement
	u8 negInt = ~(*reg2) + 0x01;
	
	GB_CPU_ADD_8(reg1, &negInt);

	GB_CPU_Set_Flag_N();
}

void GB_CPU_SBC_8(u8* reg1, u8* reg2)
{
	if( GB_CPU_reg_AF[1] & 0x10 != 0)
	{
		u8 negInt = ~(*reg2) + 0x02;
	
		GB_CPU_ADD_8(reg1, &negInt);

		GB_CPU_Set_Flag_N();
	}
	else
	{
		GB_CPU_SUB_8(reg1,reg2);
	}

}
void GB_CPU_INC_8(u8* reg)
{
	// Reseting all flags before any operation, also sets N flag to 0
	
	GB_CPU_Reset_All_Flags();

	u8 result = *reg  +  0x01;
	
	u8 carry = *reg ^ 0x01 ^ result;
	
	// Half carry test
	if(carry & 0x10 != 0x00)
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
	// Reseting all flags before any operation, also sets N flag to 0
	
	GB_CPU_Reset_All_Flags();

	u8 result = *reg  +  0xFF;
	
	u8 carry = *reg ^ 0xFF ^ result;
	
	// Half carry test
	if(carry & 0x10 != 0x00)
	{
		GB_CPU_Set_Flag_H();
	}

	*reg = result;

	if(result == 0x00)
	{
		GB_CPU_Set_Flag_Z();
	}
}
void GB_CPU_DAA_8(u8* reg1, u8* reg2)
{
	
}

void GB_CPU_AND(u8* reg1,u8* reg2)
{
	*reg1 = *reg1 & *reg2;
}

void GB_CPU_OR(u8* reg1, u8* reg2)
{
	*reg1 = *reg1 | *reg2;
}

void GB_CPU_XOR(u8* reg1, u8* reg2)
{
	*reg1 = *reg1 ^ *reg2;
}