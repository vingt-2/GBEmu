#include "GBCpu.h"

void GB_CPU_OPCODE_0x00()
{
    GB_CPU_NOP();
}
void GB_CPU_OPCODE_0x10()
{
    GB_CPU_Stop();
}
void GB_CPU_OPCODE_0x20() // Relative JP
{
    u8 8_bit_value = GB_Get_u8_PC();
    GB_CPU_Cond_Relative_Jump(&8_bit_value,0x08);   
}
void GB_CPU_OPCODE_0x30()
{
    u8 8_bit_value = GB_Get_u8_PC();
    GB_CPU_Cond_Relative_Jump(&8_bit_value,0x02);   
}
void GB_CPU_OPCODE_0x40()
{
    GB_CPU_LD_8(GB_CPU_reg_BC, &(GB_CPU_reg_BC[0]));
}
void GB_CPU_OPCODE_0x50()
{
    GB_CPU_LD_8(GB_CPU_reg_DE, &(GB_CPU_reg_BC[0]));
}
void GB_CPU_OPCODE_0x60()
{
    GB_CPU_LD_8(GB_CPU_reg_HL, &(GB_CPU_reg_BC[0]));
}
void GB_CPU_OPCODE_0x70()
{
    GB_Set_Main_Memory((u16*)GB_CPU_reg_HL,&(GB_CPU_reg_BC[0]));
}
void GB_CPU_OPCODE_0x80()
{
    GB_CPU_ADD_8(GB_CPU_reg_BC);
}
void GB_CPU_OPCODE_0x90()
{
    GB_CPU_SUB_8(GB_CPU_reg_BC);
}
void GB_CPU_OPCODE_0xA0()
{
    GB_CPU_AND(GB_CPU_reg_BC);
}
void GB_CPU_OPCODE_0xB0()
{
    GB_CPU_OR(GB_CPU_reg_BC);
}
void GB_CPU_OPCODE_0xC0()
{
    GB_CPU_Cond_Return(0x08);
}
void GB_CPU_OPCODE_0xD0()
{
    GB_CPU_Cond_Return(0x02);
}
void GB_CPU_OPCODE_0xE0()
{
    
}
void GB_CPU_OPCODE_0xF0()
{
    
}
void GB_CPU_OPCODE_0x01
{
    u16 word_to_load = GB_Get_u16_PC();
    GB_CPU_LD_16((u16*) GB_CPU_reg_BC,&word_to_load);
    GB_Increment_PC(2);
}
void GB_CPU_OPCODE_0x11()
{
    u16 word_to_load = GB_Get_u16_PC();
    GB_CPU_LD_16((u16*) GB_CPU_reg_DE,&word_to_load);
    GB_Increment_PC(2);
}
void GB_CPU_OPCODE_0x21()
{
    u16 word_to_load = GB_Get_u16_PC();
    GB_CPU_LD_16((u16*) GB_CPU_reg_HL,&word_to_load);
    GB_Increment_PC(2);
}
void GB_CPU_OPCODE_0x31()
{
    u16 word_to_load = GB_Get_u16_PC();
    GB_CPU_LD_16(&GB_CPU_reg_SP,&word_to_load);
    GB_Increment_PC(2);
}
void GB_CPU_OPCODE_0x41()
{
    GB_CPU_LD_8(GB_CPU_reg_BC, &(GB_CPU_reg_BC[1]));
}
void GB_CPU_OPCODE_0x51()
{
    GB_CPU_LD_8(GB_CPU_reg_DE, &(GB_CPU_reg_BC[1]));
}
void GB_CPU_OPCODE_0x61()
{
    GB_CPU_LD_8(GB_CPU_reg_HL, &(GB_CPU_reg_BC[1]));
}
void GB_CPU_OPCODE_0x71()
{
    GB_Set_Main_Memory((u16*)GB_CPU_reg_HL,&(GB_CPU_reg_BC[1]));
}
void GB_CPU_OPCODE_0x81()
{
    GB_CPU_ADD_8(&(GB_CPU_reg_BC[1]));
}
void GB_CPU_OPCODE_0x91()
{
   GB_CPU_SUB_8(&(GB_CPU_reg_BC[1]));
}
void GB_CPU_OPCODE_0xA1()
{
    GB_CPU_AND(&(GB_CPU_reg_BC[1]));
}
void GB_CPU_OPCODE_0xB1()
{
    GB_CPU_OR(&(GB_CPU_reg_BC[1]));
}
void GB_CPU_OPCODE_0xC1()
{
    GB_CPU_POP_16((u16*)GB_CPU_reg_BC);
}
void GB_CPU_OPCODE_0xD1()
{
    GB_CPU_POP_16((u16*)GB_CPU_reg_DE);
}
void GB_CPU_OPCODE_0xE1()
{
    GB_CPU_POP_16((u16*)GB_CPU_reg_HL);
}
void GB_CPU_OPCODE_0xF1()
{
    GB_CPU_POP_16((u16*)GB_CPU_reg_AF);
}
void GB_CPU_OPCODE_0x02()
{
    GB_Set_Main_Memory((u16*)(GB_CPU_reg_BC), GB_CPU_reg_AF);
}
void GB_CPU_OPCODE_0x12()
{
    GB_Set_Main_Memory((u16*)(GB_CPU_reg_DE), GB_CPU_reg_AF);
}
void GB_CPU_OPCODE_0x22()
{
    
}
void GB_CPU_OPCODE_0x32()
{
    
}
void GB_CPU_OPCODE_0x42()
{
    GB_CPU_LD_8(GB_CPU_reg_BC, &(GB_CPU_reg_DE[0]));
}
void GB_CPU_OPCODE_0x52()
{
    GB_CPU_LD_8(GB_CPU_reg_DE, &(GB_CPU_reg_DE[0]));
}
void GB_CPU_OPCODE_0x62()
{
    GB_CPU_LD_8(GB_CPU_reg_HL, &(GB_CPU_reg_DE[0]));
}
void GB_CPU_OPCODE_0x72()
{
    GB_Set_Main_Memory((u16*)GB_CPU_reg_HL, GB_CPU_reg_DE);
}
void GB_CPU_OPCODE_0x82()
{
    GB_CPU_ADD_8(&(GB_CPU_reg_DE[0]));
}
void GB_CPU_OPCODE_0x92()
{
    GB_CPU_SUB_8(&(GB_CPU_reg_DE[0]));
}
void GB_CPU_OPCODE_0xA2()
{
    GB_CPU_AND(&(GB_CPU_reg_DE[0]));
}
void GB_CPU_OPCODE_0xB2()
{
    GB_CPU_OR(&(GB_CPU_reg_DE[0]));
}
void GB_CPU_OPCODE_0xC2()
{
    u16 new_address = GB_Get_u16_PC();
    GB_CPU_Cond_Jump(&new_address,GB_FLAG_NOT_Z);
}
void GB_CPU_OPCODE_0xD2()
{
    u16 new_address = GB_Get_u16_PC();
    GB_CPU_Cond_Jump(&new_address,GB_FLAG_NOT_C);
}
void GB_CPU_OPCODE_0xE2()
{
    u16 reg_location = 0xFF00 + ((u16) GB_CPU_reg_BC[1]);
    GB_Set_Main_Memory(&reg_location, GB_CPU_reg_AF);
}
void GB_CPU_OPCODE_0xF2()
{
    u16 reg_location = 0xFF00 + ((u16) GB_CPU_reg_BC[1]);
    u8 memory_content = GB_Get_Main_Memory(&reg_location);
    GB_CPU_LD_8(&(GB_CPU_reg_AF[0]),&memory_content);
}
void GB_CPU_OPCODE_0x03(void) // Increment BC
{
    GB_CPU_INC_16((u16*)GB_CPU_reg_BC);
}
void GB_CPU_OPCODE_0x13()
{
    GB_CPU_INC_16((u16*)GB_CPU_reg_DE);
}
void GB_CPU_OPCODE_0x23()
{
    GB_CPU_INC_16((u16*)GB_CPU_reg_HL);
}
void GB_CPU_OPCODE_0x33()
{
    GB_CPU_INC_16(&GB_CPU_reg_SP);
}
void GB_CPU_OPCODE_0x43()
{
    GB_CPU_LD_8(GB_CPU_reg_BC, &(GB_CPU_reg_DE[1]));
}
void GB_CPU_OPCODE_0x53()
{
    GB_CPU_LD_8(GB_CPU_reg_DE, &(GB_CPU_reg_DE[1]));
}
void GB_CPU_OPCODE_0x63()
{
    GB_CPU_LD_8(GB_CPU_reg_HL, &(GB_CPU_reg_DE[1]));
}
void GB_CPU_OPCODE_0x73()
{
    GB_Set_Main_Memory((u16*)GB_CPU_reg_HL, &(GB_CPU_reg_DE[1]));
}
void GB_CPU_OPCODE_0x83()
{
    GB_CPU_ADD_8(&(GB_CPU_reg_DE[1]));
}
void GB_CPU_OPCODE_0x93()
{
    GB_CPU_SUB_8(&(GB_CPU_reg_DE[1]));
}
void GB_CPU_OPCODE_0xA3()
{
    GB_CPU_AND(&(GB_CPU_reg_DE[1]));
}
void GB_CPU_OPCODE_0xB3()
{
    GB_CPU_OR(&(GB_CPU_reg_DE[1]));
}
void GB_CPU_OPCODE_0xC3()
{
    u16 new_address = GB_Get_u16_PC();
    GB_CPU_Jump(&new_address);
}
void GB_CPU_OPCODE_0xD3()
{
    
}
void GB_CPU_OPCODE_0xE3()
{
    
}
void GB_CPU_OPCODE_0xF3()
{
    
}
void GB_CPU_OPCODE_0x04()
{
    GB_CPU_INC_8(GB_CPU_reg_BC);
}
void GB_CPU_OPCODE_0x14()
{
    GB_CPU_INC_8(GB_CPU_reg_DE);
}
void GB_CPU_OPCODE_0x24()
{
    GB_CPU_INC_8(GB_CPU_reg_HL);
}
void GB_CPU_OPCODE_0x34()
{
    GB_CPU_INC_8(GB_main_memory + *((u16*)GB_CPU_reg_HL));
}
void GB_CPU_OPCODE_0x44()
{
    GB_CPU_LD_8(GB_CPU_reg_BC, &(GB_CPU_reg_HL[0]));
}
void GB_CPU_OPCODE_0x54()
{
   GB_CPU_LD_8(GB_CPU_reg_DE, &(GB_CPU_reg_HL[0]));
}
void GB_CPU_OPCODE_0x64()
{
    GB_CPU_LD_8(GB_CPU_reg_HL, &(GB_CPU_reg_HL[0]));
}
void GB_CPU_OPCODE_0x74()
{
    GB_Set_Main_Memory((u16*)GB_CPU_reg_HL, &(GB_CPU_reg_HL[0]));
}
void GB_CPU_OPCODE_0x84()
{
    GB_CPU_ADD_8(&(GB_CPU_reg_HL[0]));
}
void GB_CPU_OPCODE_0x94()
{
    GB_CPU_SUB_8(&(GB_CPU_reg_HL[0]));
}
void GB_CPU_OPCODE_0xA4()
{
    GB_CPU_AND(&(GB_CPU_reg_HL[0]));
}
void GB_CPU_OPCODE_0xB4()
{
    GB_CPU_OR(&(GB_CPU_reg_HL[0]));
}
void GB_CPU_OPCODE_0xC4()
{
    u16 new_address = GB_Get_u16_PC();
    GB_CPU_Cond_Call(&new_address,GB_FLAG_NOT_Z);
}
void GB_CPU_OPCODE_0xD4()
{
    u16 new_address = GB_Get_u16_PC();
    GB_CPU_Cond_Call(&new_address,GB_FLAG_NOT_C);
}
void GB_CPU_OPCODE_0xE4()
{
    // SIGNAL FAULT
}
void GB_CPU_OPCODE_0xF4()
{
    // SIGNAL FAULT
}
void GB_CPU_OPCODE_0x05()
{
    GB_CPU_DEC_8(GB_CPU_reg_BC);
}
void GB_CPU_OPCODE_0x15()
{
    GB_CPU_DEC_8(GB_CPU_reg_DE);
}
void GB_CPU_OPCODE_0x25()
{
    GB_CPU_DEC_8(GB_CPU_reg_HL);
}
void GB_CPU_OPCODE_0x35()
{
    GB_CPU_DEC_8(GB_main_memory + *((u16*)GB_CPU_reg_HL));
}
void GB_CPU_OPCODE_0x45()
{
    GB_CPU_LD_8(GB_CPU_reg_BC, &(GB_CPU_reg_HL[1]));
}
void GB_CPU_OPCODE_0x55()
{
    GB_CPU_LD_8(GB_CPU_reg_DE, &(GB_CPU_reg_HL[1]));
}
void GB_CPU_OPCODE_0x65()
{
    GB_CPU_LD_8(GB_CPU_reg_HL, &(GB_CPU_reg_HL[1]));
}
void GB_CPU_OPCODE_0x75()
{
    GB_Set_Main_Memory((u16*)GB_CPU_reg_HL, &(GB_CPU_reg_HL[1]));
}
void GB_CPU_OPCODE_0x85()
{
    GB_CPU_ADD_8(&(GB_CPU_reg_HL[1]));
}
void GB_CPU_OPCODE_0x95()
{
    GB_CPU_SUB_8(&(GB_CPU_reg_HL[1]));
}
void GB_CPU_OPCODE_0xA5()
{
    GB_CPU_AND(&(GB_CPU_reg_HL[1]));
}
void GB_CPU_OPCODE_0xB5()
{
    GB_CPU_OR(&(GB_CPU_reg_HL[1]));
}
void GB_CPU_OPCODE_0xC5()
{
    GB_CPU_PUSH_16((u16*)GB_CPU_reg_BC);
}
void GB_CPU_OPCODE_0xD5()
{
    GB_CPU_PUSH_16((u16*)GB_CPU_reg_DE);
}
void GB_CPU_OPCODE_0xE5()
{
    GB_CPU_PUSH_16((u16*)GB_CPU_reg_HL);
}
void GB_CPU_OPCODE_0xF5()
{
    GB_CPU_PUSH_16((u16*)GB_CPU_reg_AF);
}
void GB_CPU_OPCODE_0x06()
{
    u8 word_to_load = GB_Get_u8_PC();
    GB_CPU_LD_8(GB_CPU_reg_BC,&word_to_load);
    GB_Increment_PC(1);
}
void GB_CPU_OPCODE_0x16()
{
    u8 word_to_load = GB_Get_u8_PC();
    GB_CPU_LD_8(GB_CPU_reg_DE,&word_to_load);
    GB_Increment_PC(1);
}
void GB_CPU_OPCODE_0x26()
{
    u8 word_to_load = GB_Get_u8_PC();
    GB_CPU_LD_8(GB_CPU_reg_HL,&word_to_load);
    GB_Increment_PC(1);
}
void GB_CPU_OPCODE_0x36()
{
    u8 word_to_load = GB_Get_u8_PC();
    GB_Set_Main_Memory((u16*)GB_CPU_reg_HL,&word_to_load);
    GB_Increment_PC(1);
}
void GB_CPU_OPCODE_0x46()
{
    u16* address_to_load = (u16*)GB_CPU_reg_HL;
    u8 word_to_load = GB_Get_Main_Memory(address_to_load);
    GB_CPU_LD_8(GB_CPU_reg_BC, &word_to_load);
}
void GB_CPU_OPCODE_0x56()
{
    u16* address_to_load = (u16*)GB_CPU_reg_HL;
    u8 word_to_load = GB_Get_Main_Memory(address_to_load);
    GB_CPU_LD_8(GB_CPU_reg_DE, &word_to_load);
}
void GB_CPU_OPCODE_0x66()
{
    u16* address_to_load = (u16*)GB_CPU_reg_HL;
    u8 word_to_load = GB_Get_Main_Memory(address_to_load);
    GB_CPU_LD_8(GB_CPU_reg_HL, &word_to_load);
}
void GB_CPU_OPCODE_0x76()
{
    GB_CPU_Halt();
}
void GB_CPU_OPCODE_0x86()
{
    u8 word_to_add = GB_Get_Main_Memory((u16*)GB_CPU_reg_HL);
    GB_CPU_ADD_8(&word_to_add);
}
void GB_CPU_OPCODE_0x96()
{
    u8 word_to_add = GB_Get_Main_Memory((u16*)GB_CPU_reg_HL);
    GB_CPU_SUB_8(&word_to_add);
}
void GB_CPU_OPCODE_0xA6()
{
    u8 word_to_add = GB_Get_Main_Memory((u16*)GB_CPU_reg_HL);
    GB_CPU_AND(&word_to_add);
}
void GB_CPU_OPCODE_0xB6()
{
    u8 word_to_add = GB_Get_Main_Memory((u16*)GB_CPU_reg_HL);
    GB_CPU_OR(&word_to_add);
}
void GB_CPU_OPCODE_0xC6()
{
    u8 word_to_add = GB_Get_u8_PC();
    GB_CPU_ADD_8(&word_to_add);
    GB_Increment_PC(1);
}
void GB_CPU_OPCODE_0xD6()
{
    u8 word_to_add = GB_Get_u8_PC();
    GB_CPU_SUB_8(&word_to_add);
    GB_Increment_PC(1);
}
void GB_CPU_OPCODE_0xE6()
{
    u8 word_to_add = GB_Get_u8_PC();
    GB_CPU_AND(&word_to_add);
    GB_Increment_PC(1);
}
void GB_CPU_OPCODE_0xF6()
{
    u8 word_to_add = GB_Get_u8_PC();
    GB_CPU_OR(&word_to_add);
    GB_Increment_PC(1);
}
void GB_CPU_OPCODE_0x07()
{
    GB_CPU_RLC_Accu();
}
void GB_CPU_OPCODE_0x17()
{
    GB_CPU_RL_Accu();
}
void GB_CPU_OPCODE_0x27()
{
    GB_CPU_DAA_8();
}
void GB_CPU_OPCODE_0x37()
{
    GB_CPU_SCF();
}
void GB_CPU_OPCODE_0x47()
{
    GB_CPU_LD_8(GB_CPU_reg_BC, &(GB_CPU_reg_AF[0]));
}
void GB_CPU_OPCODE_0x57()
{
    GB_CPU_LD_8(GB_CPU_reg_DE, &(GB_CPU_reg_AF[0]));
}
void GB_CPU_OPCODE_0x67()
{
     GB_CPU_LD_8(GB_CPU_reg_HL, &(GB_CPU_reg_AF[0]));
}
void GB_CPU_OPCODE_0x77()
{
    // TO DO 
}
void GB_CPU_OPCODE_0x87()
{
    GB_CPU_ADD_8(GB_CPU_reg_AF);
}
void GB_CPU_OPCODE_0x97()
{
    GB_CPU_SUB_8(GB_CPU_reg_AF);
}
void GB_CPU_OPCODE_0xA7()
{
    GB_CPU_AND(GB_CPU_reg_AF);
}
void GB_CPU_OPCODE_0xB7()
{
    GB_CPU_OR(GB_CPU_reg_AF);
}
void GB_CPU_OPCODE_0xC7()
{
    
}
void GB_CPU_OPCODE_0xD7()
{
    
}
void GB_CPU_OPCODE_0xE7()
{
    
}
void GB_CPU_OPCODE_0xF7()
{
    
}
void GB_CPU_OPCODE_0x08()
{
    
}
void GB_CPU_OPCODE_0x18()
{
    u8 u8_bit_value = GB_Get_u8_PC();
    GB_CPU_Relative_Jump(&u8_bit_value);
}
void GB_CPU_OPCODE_0x28()
{
    u8 u8_bit_value = GB_Get_u8_PC();
    GB_CPU_Cond_Relative_Jump(&u8_bit_value,GB_FLAG_Z);   
}
void GB_CPU_OPCODE_0x38()
{
    u8 u8_bit_value = GB_Get_u8_PC();
    GB_CPU_Cond_Relative_Jump(&u8_bit_value,GB_FLAG_C);   
}
void GB_CPU_OPCODE_0x48()
{
    GB_CPU_LD_8(&(GB_CPU_reg_BC[1]),GB_CPU_reg_BC);
}
void GB_CPU_OPCODE_0x58()
{
    GB_CPU_LD_8(&(GB_CPU_reg_DE[1]),GB_CPU_reg_BC);    
}
void GB_CPU_OPCODE_0x68()
{
    GB_CPU_LD_8(&(GB_CPU_reg_HL[1]),GB_CPU_reg_BC);
}
void GB_CPU_OPCODE_0x78()
{
    GB_CPU_LD_8(&(GB_CPU_reg_AF[0]),GB_CPU_reg_BC);
}
void GB_CPU_OPCODE_0x88()
{
    GB_CPU_ADC_8(GB_CPU_reg_BC);
}
void GB_CPU_OPCODE_0x98()
{
    GB_CPU_SBC_8(GB_CPU_reg_BC);
}
void GB_CPU_OPCODE_0xA8()
{
    GB_CPU_XOR(GB_CPU_reg_BC);
}
void GB_CPU_OPCODE_0xB8()
{
    GB_CPU_CP(GB_CPU_reg_BC);
}
void GB_CPU_OPCODE_0xC8()
{
    GB_CPU_Cond_Return(GB_FLAG_Z);
}
void GB_CPU_OPCODE_0xD8()
{
    GB_CPU_Cond_Return(GB_FLAG_C);   
}
void GB_CPU_OPCODE_0xE8()
{
    
}
void GB_CPU_OPCODE_0xF8()
{
    
}
void GB_CPU_OPCODE_0x09()
{
    GB_CPU_ADD_16((u16*) GB_CPU_reg_BC);
}
void GB_CPU_OPCODE_0x19()
{
    GB_CPU_ADD_16((u16*) GB_CPU_reg_DE);   
}
void GB_CPU_OPCODE_0x29()
{
    GB_CPU_ADD_16((u16*) GB_CPU_reg_HL);
}
void GB_CPU_OPCODE_0x39()
{
    GB_CPU_ADD_16((u16*) GB_CPU_reg_SP);
}
void GB_CPU_OPCODE_0x49()
{
    GB_CPU_LD_8(&(GB_CPU_reg_BC[1]),&(GB_CPU_reg_BC[1]));
}
void GB_CPU_OPCODE_0x59()
{
    GB_CPU_LD_8(&(GB_CPU_reg_DE[1]),&(GB_CPU_reg_BC[1]));    
}
void GB_CPU_OPCODE_0x69()
{
    GB_CPU_LD_8(&(GB_CPU_reg_HL[1]),&(GB_CPU_reg_BC[1]));
}
void GB_CPU_OPCODE_0x79()
{
    GB_CPU_LD_8(&(GB_CPU_reg_AF[0]),&(GB_CPU_reg_BC[1]));
}
void GB_CPU_OPCODE_0x89()
{
    GB_CPU_ADC_8(&(GB_CPU_reg_BC[1]));
}
void GB_CPU_OPCODE_0x99()
{
    GB_CPU_SBC_8(&(GB_CPU_reg_BC[1]));
}
void GB_CPU_OPCODE_0xA9()
{
    GB_CPU_XOR(&(GB_CPU_reg_BC[1]));
}
void GB_CPU_OPCODE_0xB9()
{
    GB_CPU_CP(&(GB_CPU_reg_BC[1]));
}
void GB_CPU_OPCODE_0xC9()
{
    GB_CPU_Return();
}
void GB_CPU_OPCODE_0xD9()
{
    GB_CPU_Return();
    GB_CPU_EI();
}
void GB_CPU_OPCODE_0xE9()
{
    u8 offset_reg = GB_Get_Main_Memory((u16*)GB_Get_reg_HL);
}
void GB_CPU_OPCODE_0xF9()
{
    
}
void GB_CPU_OPCODE_0x0A()
{
    
}
void GB_CPU_OPCODE_0x1A()
{
    
}
void GB_CPU_OPCODE_0x2A()
{
    
}
void GB_CPU_OPCODE_0x3A()
{
    
}
void GB_CPU_OPCODE_0x4A()
{
    GB_CPU_LD_8(&(GB_CPU_reg_BC[1]),GB_CPU_reg_DE);
}
void GB_CPU_OPCODE_0x5A()
{
    GB_CPU_LD_8(&(GB_CPU_reg_DE[1]),GB_CPU_reg_DE);    
}
void GB_CPU_OPCODE_0x6A()
{
    GB_CPU_LD_8(&(GB_CPU_reg_HL[1]),GB_CPU_reg_DE);
}
void GB_CPU_OPCODE_0x7A()
{
    GB_CPU_LD_8(&(GB_CPU_reg_AF[0]),GB_CPU_reg_DE);
}
void GB_CPU_OPCODE_0x8A()
{
    GB_CPU_ADC_8(GB_CPU_reg_DE);
}
void GB_CPU_OPCODE_0x9A()
{
    GB_CPU_SBC_8(GB_CPU_reg_DE);
}
void GB_CPU_OPCODE_0xAA()
{
    GB_CPU_XOR(GB_CPU_reg_DE);
}
void GB_CPU_OPCODE_0xBA()
{
    GB_CPU_CP(GB_CPU_reg_DE);
}
void GB_CPU_OPCODE_0xCA()
{
    u16 new_address = GB_Get_u16_PC();
    GB_CPU_Cond_Jump(&new_address,GB_FLAG_Z);
}
void GB_CPU_OPCODE_0xDA()
{
    u16 new_address = GB_Get_u16_PC();
    GB_CPU_Cond_Jump(&new_address,GB_FLAG_C);   
}
void GB_CPU_OPCODE_0xEA()
{
    
}
void GB_CPU_OPCODE_0xFA()
{
    
}
void GB_CPU_OPCODE_0x0B()
{
    GB_CPU_DEC_16((u16*)GB_CPU_reg_BC);
}
void GB_CPU_OPCODE_0x1B()
{
    GB_CPU_DEC_16((u16*)GB_CPU_reg_DE);    
}
void GB_CPU_OPCODE_0x2B()
{
    GB_CPU_DEC_16((u16*)GB_CPU_reg_HL);
}
void GB_CPU_OPCODE_0x3B()
{
    GB_CPU_DEC_16((u16*)GB_CPU_reg_SP);
}
void GB_CPU_OPCODE_0x4B()
{
    GB_CPU_LD_8(&(GB_CPU_reg_BC[1]),&(GB_CPU_reg_DE[1]));
}
void GB_CPU_OPCODE_0x5B()
{
    GB_CPU_LD_8(&(GB_CPU_reg_DE[1]),&(GB_CPU_reg_DE[1]));    
}
void GB_CPU_OPCODE_0x6B()
{
    GB_CPU_LD_8(&(GB_CPU_reg_HL[1]),&(GB_CPU_reg_DE[1]));
}
void GB_CPU_OPCODE_0x7B()
{
    GB_CPU_LD_8(&(GB_CPU_reg_AF[0]),&(GB_CPU_reg_DE[1]));
}
void GB_CPU_OPCODE_0x8B()
{
    GB_CPU_ADC_8(&(GB_CPU_reg_DE[1]));
}
void GB_CPU_OPCODE_0x9B()
{
    GB_CPU_SBC_8(&(GB_CPU_reg_DE[1]));
}
void GB_CPU_OPCODE_0xAB()
{
    GB_CPU_XOR(&(GB_CPU_reg_DE[1]));
}
void GB_CPU_OPCODE_0xBB()
{
    GB_CPU_CP(&(GB_CPU_reg_DE[1]));
}
void GB_CPU_OPCODE_0xCB()
{
    
}
void GB_CPU_OPCODE_0xDB()
{
    // SIGNAL FAULT
}
void GB_CPU_OPCODE_0xEB()
{
    // SIGNAL FAULT
}
void GB_CPU_OPCODE_0xFB()
{
    GB_CPU_EI();
}
void GB_CPU_OPCODE_0x0C()
{
    GB_CPU_INC_8(&(GB_CPU_reg_BC[1]);
}
void GB_CPU_OPCODE_0x1C()
{
    GB_CPU_INC_8(&(GB_CPU_reg_DE[1]);   
}
void GB_CPU_OPCODE_0x2C()
{
    GB_CPU_INC_8(&(GB_CPU_reg_HL[1]);   
}
void GB_CPU_OPCODE_0x3C()
{
    GB_CPU_INC_8(&(GB_CPU_reg_AF[0]);   
}
void GB_CPU_OPCODE_0x4C()
{
    GB_CPU_LD_8(&(GB_CPU_reg_BC[1]),&(GB_CPU_reg_HL[0]));
}
void GB_CPU_OPCODE_0x5C()
{
    GB_CPU_LD_8(&(GB_CPU_reg_DE[1]),&(GB_CPU_reg_HL[0]));    
}
void GB_CPU_OPCODE_0x6C()
{
    GB_CPU_LD_8(&(GB_CPU_reg_HL[1]),&(GB_CPU_reg_HL[0]));
}
void GB_CPU_OPCODE_0x7C()
{
    GB_CPU_LD_8(&(GB_CPU_reg_AF[0]),&(GB_CPU_reg_HL[0]));
}
void GB_CPU_OPCODE_0x8C()
{
    GB_CPU_ADC_8(&(GB_CPU_reg_HL[0]));
}
void GB_CPU_OPCODE_0x9C()
{
    GB_CPU_SBC_8(&(GB_CPU_reg_HL[0]));
}
void GB_CPU_OPCODE_0xAC()
{
    GB_CPU_XOR(&(GB_CPU_reg_HL[0]));
}
void GB_CPU_OPCODE_0xBC()
{
    GB_CPU_CP(&(GB_CPU_reg_HL[0]));
}
void GB_CPU_OPCODE_0xCC()
{
    u16 new_address = GB_Get_u16_PC();
    GB_CPU_Cond_Call(&new_address,GB_FLAG_Z);
}
void GB_CPU_OPCODE_0xDC()
{
    u16 new_address = GB_Get_u16_PC();
    GB_CPU_Cond_Call(&new_address,GB_FLAG_C);   
}
void GB_CPU_OPCODE_0xEC()
{
    // SIGNAL FAULT
}
void GB_CPU_OPCODE_0xFC()
{
    // SIGNAL FAULT   
}
void GB_CPU_OPCODE_0x0D()
{
    GB_CPU_INC_8(&(GB_CPU_reg_BC[1]));
}
void GB_CPU_OPCODE_0x1D()
{
    GB_CPU_INC_8(&(GB_CPU_reg_DE[1]));   
}
void GB_CPU_OPCODE_0x2D()
{
    GB_CPU_INC_8(&(GB_CPU_reg_HL[1]));
}
void GB_CPU_OPCODE_0x3D()
{
    GB_CPU_INC_8(&(GB_CPU_reg_AF[0]));
}
void GB_CPU_OPCODE_0x4D()
{
    GB_CPU_LD_8(&(GB_CPU_reg_BC[1]),&(GB_CPU_reg_HL[1]));
}
void GB_CPU_OPCODE_0x5D()
{
    GB_CPU_LD_8(&(GB_CPU_reg_DE[1]),&(GB_CPU_reg_HL[1]));    
}
void GB_CPU_OPCODE_0x6D()
{
    GB_CPU_LD_8(&(GB_CPU_reg_HL[1]),&(GB_CPU_reg_HL[1]));
}
void GB_CPU_OPCODE_0x7D()
{
    GB_CPU_LD_8(&(GB_CPU_reg_AF[0]),&(GB_CPU_reg_HL[1]));
}
void GB_CPU_OPCODE_0x8D()
{
    GB_CPU_ADC_8(&(GB_CPU_reg_HL[1]));
}
void GB_CPU_OPCODE_0x9D()
{
    GB_CPU_SBC_8(&(GB_CPU_reg_HL[1]));
}
void GB_CPU_OPCODE_0xAD()
{
    GB_CPU_XOR(&(GB_CPU_reg_HL[1]));
}
void GB_CPU_OPCODE_0xBD()
{
    GB_CPU_CP(&(GB_CPU_reg_HL[1]));
}
void GB_CPU_OPCODE_0xCD()
{
    
}
void GB_CPU_OPCODE_0xDD()
{
    
}
void GB_CPU_OPCODE_0xED()
{
    
}
void GB_CPU_OPCODE_0xFD()
{
    
}
void GB_CPU_OPCODE_0x0E()
{
    
}
void GB_CPU_OPCODE_0x1E()
{
    
}
void GB_CPU_OPCODE_0x2E()
{
    
}
void GB_CPU_OPCODE_0x3E()
{
    
}
void GB_CPU_OPCODE_0x4E()
{
    u8 memory_content = GB_Get_Main_Memory((u16*)GB_CPU_reg_HL);
    GB_CPU_LD_8(&(GB_CPU_reg_BC[1]),&memory_content);
}
void GB_CPU_OPCODE_0x5E()
{
    u8 memory_content = GB_Get_Main_Memory((u16*)GB_CPU_reg_HL);
    GB_CPU_LD_8(&(GB_CPU_reg_DE[1]),&memory_content);
}
void GB_CPU_OPCODE_0x6E()
{
    u8 memory_content = GB_Get_Main_Memory((u16*)GB_CPU_reg_HL);
    GB_CPU_LD_8(&(GB_CPU_reg_HL[1]),&memory_content);
}
void GB_CPU_OPCODE_0x7E()
{
    u8 memory_content = GB_Get_Main_Memory((u16*)GB_CPU_reg_HL);
    GB_CPU_LD_8(&(GB_CPU_reg_AF[0]),&memory_content);
}
void GB_CPU_OPCODE_0x8E()
{
    u8 memory_content = GB_Get_Main_Memory((u16*)GB_CPU_reg_HL);
    GB_CPU_ADC_8(&memory_content);
}
void GB_CPU_OPCODE_0x9E()
{
    u8 memory_content = GB_Get_Main_Memory((u16*)GB_CPU_reg_HL);
    GB_CPU_SBC_8(&memory_content);
}
void GB_CPU_OPCODE_0xAE()
{
    u8 memory_content = GB_Get_Main_Memory((u16*)GB_CPU_reg_HL);
    GB_CPU_XOR(&memory_content);
}
void GB_CPU_OPCODE_0xBE()
{
    u8 memory_content = GB_Get_Main_Memory((u16*)GB_CPU_reg_HL);
    GB_CPU_CP(&memory_content);
}
void GB_CPU_OPCODE_0xCE()
{
    
}
void GB_CPU_OPCODE_0xDE()
{
    
}
void GB_CPU_OPCODE_0xEE()
{
    
}
void GB_CPU_OPCODE_0xFE()
{
    
}
void GB_CPU_OPCODE_0x0F()
{
    
}
void GB_CPU_OPCODE_0x1F()
{
    
}
void GB_CPU_OPCODE_0x2F()
{
    
}
void GB_CPU_OPCODE_0x3F()
{
    
}
void GB_CPU_OPCODE_0x4F()
{
    GB_CPU_LD_8(&(GB_CPU_reg_BC[1]),&(GB_CPU_reg_AF[0]));
}
void GB_CPU_OPCODE_0x5F()
{
    GB_CPU_LD_8(&(GB_CPU_reg_DE[1]),&(GB_CPU_reg_AF[0]));    
}
void GB_CPU_OPCODE_0x6F()
{
    GB_CPU_LD_8(&(GB_CPU_reg_HL[1]),&(GB_CPU_reg_AF[0]));
}
void GB_CPU_OPCODE_0x7F()
{
    GB_CPU_LD_8(&(GB_CPU_reg_AF[0]),&(GB_CPU_reg_AF[0]));
}
void GB_CPU_OPCODE_0x8F()
{
    GB_CPU_ADC_8(&(GB_CPU_reg_HL[1]));
}
void GB_CPU_OPCODE_0x9F()
{
    GB_CPU_SBC_8(&(GB_CPU_reg_HL[1]));
}
void GB_CPU_OPCODE_0xAF()
{
    GB_CPU_XOR(&(GB_CPU_reg_HL[1]));
}
void GB_CPU_OPCODE_0xBF()
{
    GB_CPU_CP(&(GB_CPU_reg_HL[1]));
}
void GB_CPU_OPCODE_0xCF()
{
    
}
void GB_CPU_OPCODE_0xDF()
{
    
}
void GB_CPU_OPCODE_0xEF()
{
    
}
void GB_CPU_OPCODE_0xFF()
{
    
}