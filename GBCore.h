/*
GBCore: Is where the core functionality of The GB emulator reside,

Analogy with the actual hardware would be a motherboard

*/
#define GB_MAIN_MEMORY_SIZE 0xFFFF-1

#pragma once
#include <stdint.h>
#include <stdio.h>

typedef uint8_t u8;
typedef int8_t s8;
typedef uint16_t u16;
typedef int16_t s16;
typedef uint32_t u32;
typedef int32_t s32;
typedef uint64_t u64;
typedef int64_t s64;

typedef struct _GB_rom_descriptor
{
	char* rom_name;
	int   rom_type;
	int   rom_size;
	char* rom_content;
} GB_rom_descriptor;



//  Start of /!\
//  GB Core main memory
//  Adresses from 0000 - FFFF
//  Represented in Heap memory as a FFFF-1 byte array

u8* GB_main_memory;

u8	GB_Get_Main_Memory(u16* address_reg);
void GB_Set_Main_Memory(u16* address_reg,u8* value_reg);



int GB_boot();
int GB_place_rom_in_memory(GB_rom_descriptor* desired_rom);
int GB_dma_transfer();

