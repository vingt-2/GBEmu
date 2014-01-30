#include "GBCore.h"

u8 GB_Get_Main_Memory(u16* address_reg)
{
    return *(GB_main_memory + *(address_reg));
}

void GB_Set_Main_Memory(u16* address_reg,u8* value_reg)
{
    *(GB_main_memory + *(address_reg)) = *value_reg;
}