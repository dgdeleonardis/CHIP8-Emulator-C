#include "chip8.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	int res = 0;
	if (argc > 1)
	{
		printf("%s\n", argv[1]);
		Chip8* chip = chip8Init();
		printf("[INFO] - pc = 0x%.3x, I = 0x%.3x, sp = %d\n", chip->pc, chip->I, chip->sp); 
}
	else
	{
		printf("Usage: ./chip8 <ROM CHIP-8>\n");
		res = 1;
	}
	return res;
}
