void GB_CPU_OPCODE_0x00()
{
    // Do nothing
}

void GB_CPU_OPCODE_0x01() // load 16bit value into
{
	GB_Increment_PC(1);

	*((u16*) GB_CPU_BC) = GB_Get_u16_PC();

	GB_Increment_PC(2);   
}

void GB_CPU_OPCODE_0x02() // 8bit load A to (BC)
{
	GB_Increment_PC(1);

	GB_CPU_BC[0] = 0x00;
	GB_CPU_BC[1] = GB_CPU_AF[0]; // C = A
}

void GB_CPU_OPCODE_0x03() // Increment BC
{
	GB_Increment_PC(1);

	&((u16*) GB_CPU_BC) += 1;
}

void GB_CPU_OPCODE_0x04() // Increment B
{
	GB_Increment_PC(1);

	GB_CPU_BC[0] += 0x01;

	if(GB_CPU_BC[0] == 0x00)
	{
		// Set Z flag to 1
		GB_CPU_Set_Flag_Z();
	}

	GB_CPU_Reset_Flag_N();

void GB_CPU_OPCODE_0x06()
{

}
void GB_CPU_OPCODE_0x07()
{

}
void GB_CPU_OPCODE_0x08()
{

}
void GB_CPU_OPCODE_0x09()
{

}
void GB_CPU_OPCODE_0x0A()
{

}
void GB_CPU_OPCODE_0x0B()
{

}
void GB_CPU_OPCODE_0x0C()
{

}
void GB_CPU_OPCODE_0x0D()
{

}
void GB_CPU_OPCODE_0x0E()
{

}
void GB_CPU_OPCODE_0x0F()
{

}

void GB_CPU_OPCODE_0x10()
{

}
void GB_CPU_OPCODE_0x11()
{

}
void GB_CPU_OPCODE_0x12()
{

}
void GB_CPU_OPCODE_0x13()
{

}
void GB_CPU_OPCODE_0x14()
{

}
void GB_CPU_OPCODE_0x15()
{

}
void GB_CPU_OPCODE_0x16()
{

}
void GB_CPU_OPCODE_0x17()
{

}
void GB_CPU_OPCODE_0x18()
{

}
void GB_CPU_OPCODE_0x19()
{

}
void GB_CPU_OPCODE_0x1A()
{

}
void GB_CPU_OPCODE_0x1B()
{

}
void GB_CPU_OPCODE_0x1C()
{

}
void GB_CPU_OPCODE_0x1D()
{

}
void GB_CPU_OPCODE_0x1E()
{

}
void GB_CPU_OPCODE_0x1F()
{

}

void GB_CPU_OPCODE_0x20()
{

}
void GB_CPU_OPCODE_0x21()
{

}
void GB_CPU_OPCODE_0x22()
{

}
void GB_CPU_OPCODE_0x23()
{

}
void GB_CPU_OPCODE_0x24()
{

}
void GB_CPU_OPCODE_0x25()
{

}
void GB_CPU_OPCODE_0x26()
{

}
void GB_CPU_OPCODE_0x27()
{

}
void GB_CPU_OPCODE_0x28()
{

}
void GB_CPU_OPCODE_0x29()
{

}
void GB_CPU_OPCODE_0x2A()
{

}
void GB_CPU_OPCODE_0x2B()
{

}
void GB_CPU_OPCODE_0x2C()
{

}
void GB_CPU_OPCODE_0x2D()
{

}
void GB_CPU_OPCODE_0x2E()
{

}
void GB_CPU_OPCODE_0x2F()
{

}

void GB_CPU_OPCODE_0x30()
{

}
void GB_CPU_OPCODE_0x31()
{

}
void GB_CPU_OPCODE_0x32()
{

}
void GB_CPU_OPCODE_0x33()
{

}
void GB_CPU_OPCODE_0x34()
{

}
void GB_CPU_OPCODE_0x35()
{

}
void GB_CPU_OPCODE_0x36()
{

}
void GB_CPU_OPCODE_0x37()
{

}
void GB_CPU_OPCODE_0x38()
{

}
void GB_CPU_OPCODE_0x39()
{

}
void GB_CPU_OPCODE_0x3A()
{

}
void GB_CPU_OPCODE_0x3B()
{

}
void GB_CPU_OPCODE_0x3C()
{

}
void GB_CPU_OPCODE_0x3D()
{

}
void GB_CPU_OPCODE_0x3E()
{

}
void GB_CPU_OPCODE_0x3F()
{

}

void GB_CPU_OPCODE_0x40()
{

}
void GB_CPU_OPCODE_0x41()
{

}
void GB_CPU_OPCODE_0x42()
{

}
void GB_CPU_OPCODE_0x43()
{

}
void GB_CPU_OPCODE_0x44()
{

}
void GB_CPU_OPCODE_0x45()
{

}
void GB_CPU_OPCODE_0x46()
{

}
void GB_CPU_OPCODE_0x47()
{

}
void GB_CPU_OPCODE_0x48()
{

}
void GB_CPU_OPCODE_0x49()
{

}
void GB_CPU_OPCODE_0x4A()
{

}
void GB_CPU_OPCODE_0x4B()
{

}
void GB_CPU_OPCODE_0x4C()
{

}
void GB_CPU_OPCODE_0x4D()
{

}
void GB_CPU_OPCODE_0x4E()
{

}
void GB_CPU_OPCODE_0x4F()
{

}

void GB_CPU_OPCODE_0x50()
{

}
void GB_CPU_OPCODE_0x51()
{

}
void GB_CPU_OPCODE_0x52()
{

}
void GB_CPU_OPCODE_0x53()
{

}
void GB_CPU_OPCODE_0x54()
{

}
void GB_CPU_OPCODE_0x55()
{

}
void GB_CPU_OPCODE_0x56()
{

}
void GB_CPU_OPCODE_0x57()
{

}
void GB_CPU_OPCODE_0x58()
{

}
void GB_CPU_OPCODE_0x59()
{

}
void GB_CPU_OPCODE_0x5A()
{

}
void GB_CPU_OPCODE_0x5B()
{

}
void GB_CPU_OPCODE_0x5C()
{

}
void GB_CPU_OPCODE_0x5D()
{

}
void GB_CPU_OPCODE_0x5E()
{

}
void GB_CPU_OPCODE_0x5F()
{

}

void GB_CPU_OPCODE_0x60()
{

}
void GB_CPU_OPCODE_0x61()
{

}
void GB_CPU_OPCODE_0x62()
{

}
void GB_CPU_OPCODE_0x63()
{

}
void GB_CPU_OPCODE_0x64()
{

}
void GB_CPU_OPCODE_0x65()
{

}
void GB_CPU_OPCODE_0x66()
{

}
void GB_CPU_OPCODE_0x67()
{

}
void GB_CPU_OPCODE_0x68()
{

}
void GB_CPU_OPCODE_0x69()
{

}
void GB_CPU_OPCODE_0x6A()
{

}
void GB_CPU_OPCODE_0x6B()
{

}
void GB_CPU_OPCODE_0x6C()
{

}
void GB_CPU_OPCODE_0x6D()
{

}
void GB_CPU_OPCODE_0x6E()
{

}
void GB_CPU_OPCODE_0x6F()
{

}

void GB_CPU_OPCODE_0x70()
{

}
void GB_CPU_OPCODE_0x71()
{

}
void GB_CPU_OPCODE_0x72()
{

}
void GB_CPU_OPCODE_0x73()
{

}
void GB_CPU_OPCODE_0x74()
{

}
void GB_CPU_OPCODE_0x75()
{

}
void GB_CPU_OPCODE_0x76()
{

}
void GB_CPU_OPCODE_0x77()
{

}
void GB_CPU_OPCODE_0x78()
{

}
void GB_CPU_OPCODE_0x79()
{

}
void GB_CPU_OPCODE_0x7A()
{

}
void GB_CPU_OPCODE_0x7B()
{

}
void GB_CPU_OPCODE_0x7C()
{

}
void GB_CPU_OPCODE_0x7D()
{

}
void GB_CPU_OPCODE_0x7E()
{

}
void GB_CPU_OPCODE_0x7F()
{

}

void GB_CPU_OPCODE_0x80()
{

}
void GB_CPU_OPCODE_0x81()
{

}
void GB_CPU_OPCODE_0x82()
{

}
void GB_CPU_OPCODE_0x83()
{

}
void GB_CPU_OPCODE_0x84()
{

}
void GB_CPU_OPCODE_0x85()
{

}
void GB_CPU_OPCODE_0x86()
{

}
void GB_CPU_OPCODE_0x87()
{

}
void GB_CPU_OPCODE_0x88()
{

}
void GB_CPU_OPCODE_0x89()
{

}
void GB_CPU_OPCODE_0x8A()
{

}
void GB_CPU_OPCODE_0x8B()
{

}
void GB_CPU_OPCODE_0x8C()
{

}
void GB_CPU_OPCODE_0x8D()
{

}
void GB_CPU_OPCODE_0x8E()
{

}
void GB_CPU_OPCODE_0x8F()
{

}

void GB_CPU_OPCODE_0x90()
{

}
void GB_CPU_OPCODE_0x91()
{

}
void GB_CPU_OPCODE_0x92()
{

}
void GB_CPU_OPCODE_0x93()
{

}
void GB_CPU_OPCODE_0x94()
{

}
void GB_CPU_OPCODE_0x95()
{

}
void GB_CPU_OPCODE_0x96()
{

}
void GB_CPU_OPCODE_0x97()
{

}
void GB_CPU_OPCODE_0x98()
{

}
void GB_CPU_OPCODE_0x99()
{

}
void GB_CPU_OPCODE_0x9A()
{

}
void GB_CPU_OPCODE_0x9B()
{

}
void GB_CPU_OPCODE_0x9C()
{

}
void GB_CPU_OPCODE_0x9D()
{

}
void GB_CPU_OPCODE_0x9E()
{

}
void GB_CPU_OPCODE_0x9F()
{

}

void GB_CPU_OPCODE_0xA0()
{

}
void GB_CPU_OPCODE_0xA1()
{

}
void GB_CPU_OPCODE_0xA2()
{

}
void GB_CPU_OPCODE_0xA3()
{

}
void GB_CPU_OPCODE_0xA4()
{

}
void GB_CPU_OPCODE_0xA5()
{

}
void GB_CPU_OPCODE_0xA6()
{

}
void GB_CPU_OPCODE_0xA7()
{

}
void GB_CPU_OPCODE_0xA8()
{

}
void GB_CPU_OPCODE_0xA9()
{

}
void GB_CPU_OPCODE_0xAA()
{

}
void GB_CPU_OPCODE_0xAB()
{

}
void GB_CPU_OPCODE_0xAC()
{

}
void GB_CPU_OPCODE_0xAD()
{

}
void GB_CPU_OPCODE_0xAE()
{

}
void GB_CPU_OPCODE_0xAF()
{

}

void GB_CPU_OPCODE_0xB0()
{

}
void GB_CPU_OPCODE_0xB1()
{

}
void GB_CPU_OPCODE_0xB2()
{

}
void GB_CPU_OPCODE_0xB3()
{

}
void GB_CPU_OPCODE_0xB4()
{

}
void GB_CPU_OPCODE_0xB5()
{

}
void GB_CPU_OPCODE_0xB6()
{

}
void GB_CPU_OPCODE_0xB7()
{

}
void GB_CPU_OPCODE_0xB8()
{

}
void GB_CPU_OPCODE_0xB9()
{

}
void GB_CPU_OPCODE_0xBA()
{

}
void GB_CPU_OPCODE_0xBB()
{

}
void GB_CPU_OPCODE_0xBC()
{

}
void GB_CPU_OPCODE_0xBD()
{

}
void GB_CPU_OPCODE_0xBE()
{

}
void GB_CPU_OPCODE_0xBF()
{

}

void GB_CPU_OPCODE_0xC0()
{

}
void GB_CPU_OPCODE_0xC1()
{

}
void GB_CPU_OPCODE_0xC2()
{

}
void GB_CPU_OPCODE_0xC3()
{

}
void GB_CPU_OPCODE_0xC4()
{

}
void GB_CPU_OPCODE_0xC5()
{

}
void GB_CPU_OPCODE_0xC6()
{

}
void GB_CPU_OPCODE_0xC7()
{

}
void GB_CPU_OPCODE_0xC8()
{

}
void GB_CPU_OPCODE_0xC9()
{

}
void GB_CPU_OPCODE_0xCA()
{

}
void GB_CPU_OPCODE_0xCB()
{

}
void GB_CPU_OPCODE_0xCC()
{

}
void GB_CPU_OPCODE_0xCD()
{

}
void GB_CPU_OPCODE_0xCE()
{

}
void GB_CPU_OPCODE_0xCF()
{

}

void GB_CPU_OPCODE_0xD0()
{

}
void GB_CPU_OPCODE_0xD1()
{

}
void GB_CPU_OPCODE_0xD2()
{

}
void GB_CPU_OPCODE_0xD3()
{

}
void GB_CPU_OPCODE_0xD4()
{

}
void GB_CPU_OPCODE_0xD5()
{

}
void GB_CPU_OPCODE_0xD6()
{

}
void GB_CPU_OPCODE_0xD7()
{

}
void GB_CPU_OPCODE_0xD8()
{

}
void GB_CPU_OPCODE_0xD9()
{

}
void GB_CPU_OPCODE_0xDA()
{

}
void GB_CPU_OPCODE_0xDB()
{

}
void GB_CPU_OPCODE_0xDC()
{

}
void GB_CPU_OPCODE_0xDD()
{

}
void GB_CPU_OPCODE_0xDE()
{

}
void GB_CPU_OPCODE_0xDF()
{

}

void GB_CPU_OPCODE_0xE0()
{

}
void GB_CPU_OPCODE_0xE1()
{

}
void GB_CPU_OPCODE_0xE2()
{

}
void GB_CPU_OPCODE_0xE3()
{

}
void GB_CPU_OPCODE_0xE4()
{

}
void GB_CPU_OPCODE_0xE5()
{

}
void GB_CPU_OPCODE_0xE6()
{

}
void GB_CPU_OPCODE_0xE7()
{

}
void GB_CPU_OPCODE_0xE8()
{

}
void GB_CPU_OPCODE_0xE9()
{

}
void GB_CPU_OPCODE_0xEA()
{

}
void GB_CPU_OPCODE_0xEB()
{

}
void GB_CPU_OPCODE_0xEC()
{

}
void GB_CPU_OPCODE_0xED()
{

}
void GB_CPU_OPCODE_0xEE()
{

}
void GB_CPU_OPCODE_0xEF()
{

}

void GB_CPU_OPCODE_0xF0()
{

}
void GB_CPU_OPCODE_0xF1()
{

}
void GB_CPU_OPCODE_0xF2()
{

}
void GB_CPU_OPCODE_0xF3()
{

}
void GB_CPU_OPCODE_0xF4()
{

}
void GB_CPU_OPCODE_0xF5()
{

}
void GB_CPU_OPCODE_0xF6()
{

}
void GB_CPU_OPCODE_0xF7()
{

}
void GB_CPU_OPCODE_0xF8()
{

}
void GB_CPU_OPCODE_0xF9()
{

}
void GB_CPU_OPCODE_0xFA()
{

}
void GB_CPU_OPCODE_0xFB()
{

}
void GB_CPU_OPCODE_0xFC()
{

}
void GB_CPU_OPCODE_0xFD()
{

}
void GB_CPU_OPCODE_0xFE()
{

}
void GB_CPU_OPCODE_0xFF()
{

}