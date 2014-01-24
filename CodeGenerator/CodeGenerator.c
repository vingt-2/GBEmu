#include <stdio.h>

int main()
{
	char first, second;

	int i,j;

	for(i = 0; i < 16; i++)
	{
		for(j = 0; j < 16; j++)
		{
			if(i < 10)
				first = '0' + i;
			else
				first = 'A' + (i - 10);

			if(j < 10)
				second = '0' + j;
			else
				second = 'A' + (j-10);

			//printf("void GB_CPU_OPCODE_0x%c%c();\n",first,second);
			//printf("&GB_CPU_OPCODE_0x%c%c,\n",first,second);
			printf("void GB_CPU_OPCODE_0x%c%c()\n{\n\n}\n",first,second);
		}
		printf("\n");
	}
}