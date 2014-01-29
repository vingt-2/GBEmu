#include "GBCpu_Opcodes.c"

int main()
{
	GB_CPU_reg_AF[0] = 0x18;
	GB_CPU_DEC_8(GB_CPU_reg_AF);

	printf("%i",(int) GB_CPU_reg_AF[0]);

	return 0;
}

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

u8 u8_Test_Bit(u8* wordToTest, u8 bitNumb)
{
	u8 test_mask = 0x01;
	test_mask = test_mask << bitNumb;

	return (*wordToTest & test_mask);
}

u16 u16_Test_Bit(u16* wordToTest, u8 bitNumb)
{
	u16 test_mask = 0x0001;
	test_mask = test_mask << bitNumb;

	return (*wordToTest & test_mask);
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
void GB_CPU_LD_8(u8* loadTo, u8* from)
{
	*loadTo = *from;
}

void GB_CPU_LDI_8(u8* loadTo, u8* from)
{
	*loadTo = *from;
	(*from)++;
}

void GB_CPU_LDD_8(u8* loadTo, u8* from)
{
	*loadTo = *from;
	(*from)--;
}

// 16bit-load Commands
void GB_CPU_LD_16(u16* loadTo, u16* from)
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

	result = *reg  +  0xFF;	// 0xFF = twos complement value of -1
	
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
|    ADD    |    0    |     0-8      |   0    |     A-F      |   06    |   0   |
|           |    0    |     0-9      |   1    |     0-3      |   06    |   0   |
|   (ADC)   |    0    |     A-F      |   0    |     0-9      |   60    |   1   |
|           |    0    |     9-F      |   0    |     A-F      |   66    |   1   |
|   (INC)   |    0    |     A-F      |   1    |     0-3      |   66    |   1   |
|           |    1    |     0-2      |   0    |     0-9      |   60    |   1   |
|           |    1    |     0-2      |   0    |     A-F      |   66    |   1   |
|           |    1    |     0-3      |   1    |     0-3      |   66    |   1   |
|------------------------------------------------------------------------------|
|    SUB    |    0    |     0-9      |   0    |     0-9      |   00    |   0   |
|   (SBC)   |    0    |     0-8      |   1    |     6-F      |   FA    |   0   |
|   (DEC)   |    1    |     7-F      |   0    |     0-9      |   A0    |   1   |
|   (NEG)   |    1    |     6-F      |   1    |     6-F      |   9A    |   1   |
|------------------------------------------------------------------------------|
*/

void GB_CPU_DAA_8()
{
	u8 half_carry_flag 	= GB_CPU_Get_Flag_H();
	u8 sub_op_flag 		= GB_CPU_Get_Flag_N();
	u8 full_carry_flag	= GB_CPU_Get_Flag_C();

	u8 accu_content 	= GB_CPU_reg_AF[0];
	u8 result 			= accu_content;

	// If previous operation was an addition
	if(sub_op_flag == 0x00)
	{
		if(full_carry_flag == 0x00)
		{
			// Previous operation was an addition
			if(half_carry_flag == 0x00)
			{
				// No carry out to upper nibble
				if( (accu_content & 0x0F) >= 0x0A )
				{
					if( (accu_content & 0xF0) > 0x80 )
					{
						result += 0x66;
						GB_CPU_Set_Flag_C();
					}
					else
					{
						result += 0x06;
						GB_CPU_Reset_Flag_C();
					}
				}
				else
				{
					if((accu_content & 0xF0) >= 0x90)
					{
						result += 0x60;
						GB_CPU_Set_Flag_C();
					}
					else
					{
						GB_CPU_Reset_Flag_C();
					}
				}
			}
			else
			{
				if( (accu_content & 0xF0) < 0xA0)
				{
					result += 0x06;
					GB_CPU_Reset_Flag_C();
				}
				else
				{
					result += 0x66;
					GB_CPU_Set_Flag_C();
				}
			}
		}
		else
		{
			// Previous operation was an addition
			if(half_carry_flag == 0x00)
			{
				// No carry out to upper nibble
				if( (accu_content & 0x0F) < 0x0A )
				{
					result += 0x60;
				}
				else
				{
					result += 0x66;
				}
			}
			else
			{
					result += 0x66;
			}
			GB_CPU_Set_Flag_C();
		}
	}
	else
	{
		if(full_carry_flag == 0x00)
		{
			// Previous operation was an addition
			if(half_carry_flag == 0x00)
			{
				// Add nothing
			}
			else
			{
				result += 0xFA;
			}
			GB_CPU_Reset_Flag_C();
		}
		else
		{
			if(half_carry_flag == 0x00)
			{
				result += 0xA0;
			}
			else
			{
				result += 0x9A;
			}
			GB_CPU_Set_Flag_C();
		}
	}
	if(result == 0x00)
	{
		GB_CPU_Set_Flag_Z();
	}
	GB_CPU_Reset_Flag_H();

	GB_CPU_reg_AF[0] = result;
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

void GB_CPU_CP(u8* reg)
{
	u8 accu_content = GB_CPU_reg_AF[0];

	GB_CPU_SUB_8(reg);

	GB_CPU_reg_AF[0] = accu_content;
}

void GB_CPU_CPL()
{
	u8 accu_content = GB_CPU_reg_AF[0];

	GB_CPU_reg_AF[0] = (accu_content ^ 0xFF);
}

void GB_CPU_ADD_16(u16* reg)
{
	u16 hl_reg_content, result;
	u32 carry, overflowTest;
	GB_CPU_Reset_Flag_N();

	hl_reg_content = *( (u16*) GB_CPU_reg_HL );

	overflowTest = (u32) hl_reg_content + (u32) *reg;

	carry = overflowTest ^ (u32) hl_reg_content ^ (u32) *reg;

	if( (carry & 0x00000100) != 0x00000000 )
	{
		GB_CPU_Set_Flag_H();
	}
	if( (carry & 0x00010000) != 0x00000000 )
	{
		GB_CPU_Set_Flag_C();
	}

	result = hl_reg_content + *reg;

	if(result == 0x0000)
	{
		GB_CPU_Set_Flag_Z();
	}
}

void GB_CPU_INC_16(u16* reg)
{
	(*reg) ++;
}

void GB_CPU_DEC_16(u16* reg)
{
	(*reg) --;
}

void GB_CPU_ADD_TO_SP(u8* reg)
{
	u16 add_value;
    u8 	hl_content = *((u16*) GB_CPU_reg_HL);
    
	if( (*reg & 0x10) != 0x00 ) // negative u8 value in reg
	{
		// absolute value of the negative u8
		u8 twos_complement = ~*reg + 0x01;


		// u16 converted negative
		add_value =  ~((u16) twos_complement) + 0x0001;
	}
	else
	{
		add_value =  (u16) *reg;
	}

	// Place stack Pointer into HL register for operation
	*((u16*) GB_CPU_reg_HL) = GB_CPU_reg_SP;
	GB_CPU_ADD_16(&add_value);

	// read added value from the HL register
	GB_CPU_reg_SP = *((u16*) GB_CPU_reg_HL);

	// Restore HL register 
	*((u16*) GB_CPU_reg_HL) = hl_content;

}

void GB_CPU_LD_OFFSET(u8* reg)
{
	u16 stack_pointer = GB_CPU_reg_SP;

	GB_CPU_ADD_TO_SP(reg);

	*((u16*) GB_CPU_reg_HL) = GB_CPU_reg_SP;

	GB_CPU_reg_SP = stack_pointer;
}

void GB_CPU_RL(u8* reg)
{
	u8 reg_content = *reg;
	u8 c_flag = GB_CPU_Get_Flag_C();

	GB_CPU_Reset_All_Flags();

	((reg_content & 0x80) != 0x00) ? GB_CPU_Set_Flag_C() : GB_CPU_Reset_Flag_C();

	if( c_flag != 0x00 )
	{
		reg_content = ( (reg_content << 1) | 0x01 );
	}
	else
	{
		reg_content = ( (reg_content << 1) & 0xFB );
	}

	(reg_content != 0x00) ? GB_CPU_Reset_Flag_Z() : GB_CPU_Set_Flag_Z();

	*reg = reg_content;
}

void GB_CPU_RR(u8* reg)
{
	u8 reg_content = *reg;
	u8 c_flag = GB_CPU_Get_Flag_C();

	GB_CPU_Reset_All_Flags();

	((reg_content & 0x01) != 0x00) ? GB_CPU_Set_Flag_C() : GB_CPU_Reset_Flag_C();

	if(c_flag != 0x00)
	{
		reg_content = ( (reg_content >> 1 ) | 0x80 );
	}
	else
	{
		reg_content = ( (reg_content >> 1) & 0x7F );
	}

	(reg_content != 0x00) ? GB_CPU_Reset_Flag_Z() : GB_CPU_Set_Flag_Z();

	*reg = reg_content;
}

void GB_CPU_RLC(u8* reg)
{
	GB_CPU_Reset_All_Flags();
	u8 reg_content = *reg;

	( (reg_content >> 7) != 0x00 ) ? GB_CPU_Set_Flag_C() : GB_CPU_Reset_Flag_C();

	*reg = ( (reg_content << 1) | (reg_content >> 7) );
}

void GB_CPU_RRC(u8* reg)
{
	GB_CPU_Reset_All_Flags();
	u8 reg_content = *reg;

	( (reg_content << 7) != 0x00 ) ? GB_CPU_Set_Flag_C() : GB_CPU_Reset_Flag_C();

	*reg = ( (reg_content >> 1) | (reg_content << 7) );
}

void GB_CPU_RLC_Accu()
{
	GB_CPU_RLC(GB_CPU_reg_AF);
	GB_CPU_Reset_Flag_Z();
}
void GB_CPU_RRC_Accu()
{
	GB_CPU_RRC(GB_CPU_reg_AF);
	GB_CPU_Reset_Flag_Z();
}
void GB_CPU_RL_Accu()
{
	GB_CPU_RL(GB_CPU_reg_AF);
	GB_CPU_Reset_Flag_Z();
}
void GB_CPU_RR_Accu()
{
	GB_CPU_RR(GB_CPU_reg_AF);
	GB_CPU_Reset_Flag_Z();
}

void GB_CPU_SLA(u8* reg)
{
	*reg = (u8) *((s8*) reg) << 1;
}

void GB_CPU_SRA(u8* reg)
{
	*reg = (u8) *((s8*) reg) >> 1;
}

void GB_CPU_SRL(u8* reg)
{
	*reg = *reg >> 1;
}

void GB_CPU_SWAP(u8* reg)
{
	u8 reg_content = *reg;

	u8 hi_nibble = (reg_content & 0xF0);
	u8 lo_nibble = (reg_content & 0x0F);

	*reg = ( (lo_nibble << 4) | (hi_nibble >> 4) );
}
void GB_CPU_BIT(u8* reg1, u8* reg2)
{
	GB_CPU_Reset_Flag_N();
	GB_CPU_Set_Flag_H();
	if(u8_Test_Bit(reg1,*reg2) != 0x00)
	{
		GB_CPU_Reset_Flag_Z();
	}
	else
	{
		GB_CPU_Set_Flag_Z();
	}
}

void GB_CPU_SET(u8* reg1,u8* reg2)
{
	u8_Set_Bit(reg1, *reg2);
}

void GB_CPU_RES(u8* reg1, u8* reg2)
{
	u8_Reset_Bit(reg1,*reg2);
}

void GB_CPU_CCF()
{
	GB_CPU_Reset_Flag_H();
	GB_CPU_Reset_Flag_N();

	(GB_CPU_Get_Flag_C() != 0) ? GB_CPU_Reset_Flag_C() : GB_CPU_Set_Flag_C();
}

void GB_CPU_SCF()
{
	GB_CPU_Reset_Flag_H();
	GB_CPU_Reset_Flag_N();
	GB_CPU_Set_Flag_C();
}

void GB_CPU_NOP()
{
	double penetration;
	// Damn
}

